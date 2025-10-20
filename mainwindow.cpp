#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPixmap>
#include <QPalette>
#include <QDir>
#include <QFileInfo>
#include <QMessageBox>
#include <QRandomGenerator>
#include <QTime>
#include <QDebug>

// 播放模式枚举
enum PlayMode {
    ORDER_PLAY,
    SINGLE_LOOP,
    RANDOM_PLAY
};

static QStringList g_musiclist;
static int g_index = 0;
static PlayMode g_mode = ORDER_PLAY;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);

    setWindowIcon(QIcon(":/icon/logo.png"));
    setWindowTitle("随心音乐播放器");
    setFixedSize(960, 600);
    setBackGround(":/images/bg.png");

    initbtn();
    loadappointmusicdir("E:\\music");

    m_player = new QMediaPlayer(this);
    m_output = new QAudioOutput(this);
    m_player->setAudioOutput(m_output);
    m_output->setVolume(0.5);

    // 默认加载第一首
    if (!g_musiclist.isEmpty()) {
        m_player->setSource(QUrl::fromLocalFile(g_musiclist[g_index]));
    }

    // 自动播放下一首
    connect(m_player, &QMediaPlayer::mediaStatusChanged, this, [=](QMediaPlayer::MediaStatus s) {
        if (s == QMediaPlayer::EndOfMedia) {
            handlenext();
        }
    });

    // 播放进度更新
    connect(m_player, &QMediaPlayer::positionChanged, this, [=](qint64 pos) {
        ui->progressSlider->setValue(pos);
        ui->nowtimelbl->setText(QTime(0, 0, 0).addMSecs(pos).toString("mm:ss"));
    });

    // 音乐加载完毕后设置进度条范围
    connect(m_player, &QMediaPlayer::durationChanged, this, [=](qint64 dur) {
        ui->progressSlider->setRange(0, dur);
        ui->totaltimelbl->setText(QTime(0, 0, 0).addMSecs(dur).toString("mm:ss"));
    });

    // 拖动进度条控制播放
    connect(ui->progressSlider, &QSlider::sliderMoved, this, [=](int val) {
        m_player->setPosition(val);
    });

    // 初始隐藏音乐列表
    ui->mclist->hide();
}

void MainWindow::setBackGround(const QString &filename) {
    QPixmap pixmap(filename);
    QSize windowSize = this->size();
    QPixmap scalePixmap = pixmap.scaled(windowSize, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
    QPalette palette = this->palette();
    palette.setBrush(QPalette::Window, QBrush(scalePixmap));
    this->setPalette(palette);
}

void MainWindow::setbtnstyle(QPushButton *button, const QString &filename) {
    button->setFixedSize(50, 50);
    button->setIcon(QIcon(filename));
    button->setIconSize(QSize(button->width(), button->height()));
    button->setStyleSheet("background-color: transparent; border: none;");
}

void MainWindow::initbtn() {
    setbtnstyle(ui->prebtn, ":/icon/pre.png");
    setbtnstyle(ui->stopandbfbtn, ":/icon/stop.png");
    setbtnstyle(ui->netbtn, ":/icon/nxt.png");
    setbtnstyle(ui->moshibtn, ":/icon/order.png");
    setbtnstyle(ui->musiclistbtn, ":/icon/music.png");

    // 进度条样式
    ui->progressSlider->setStyleSheet(
        "QSlider::groove:horizontal {height:6px;background:#ccc;border-radius:3px;}"
        "QSlider::handle:horizontal {background:#ff4081;width:12px;margin:-3px 0;border-radius:6px;}"
        "QSlider::sub-page:horizontal {background:#ff4081;border-radius:3px;}"
        );

    connect(ui->stopandbfbtn, &QPushButton::clicked, this, &MainWindow::handlestopandbf);
    connect(ui->prebtn, &QPushButton::clicked, this, &MainWindow::handleprev);
    connect(ui->netbtn, &QPushButton::clicked, this, &MainWindow::handlenext);
    connect(ui->moshibtn, &QPushButton::clicked, this, &MainWindow::handlemodou);
    connect(ui->musiclistbtn, &QPushButton::clicked, this, &MainWindow::handleshowmusiclist);
}

void MainWindow::handlestopandbf() {
    if (m_player->playbackState() == QMediaPlayer::PlayingState) {
        m_player->pause();
        ui->stopandbfbtn->setIcon(QIcon(":/icon/stop.png"));
    } else {
        m_player->play();
        ui->stopandbfbtn->setIcon(QIcon(":/icon/bf.png"));
    }
}

void MainWindow::handleprev() {
    if (g_musiclist.isEmpty()) return;
    if (g_mode == RANDOM_PLAY)
        g_index = QRandomGenerator::global()->bounded(g_musiclist.size());
    else
        g_index = (g_index - 1 + g_musiclist.size()) % g_musiclist.size();

    m_player->setSource(QUrl::fromLocalFile(g_musiclist[g_index]));
    m_player->play();
    ui->stopandbfbtn->setIcon(QIcon(":/icon/bf.png"));
}

void MainWindow::handlenext() {
    if (g_musiclist.isEmpty()) return;
    if (g_mode == RANDOM_PLAY)
        g_index = QRandomGenerator::global()->bounded(g_musiclist.size());
    else if (g_mode != SINGLE_LOOP)
        g_index = (g_index + 1) % g_musiclist.size();

    m_player->setSource(QUrl::fromLocalFile(g_musiclist[g_index]));
    m_player->play();
    ui->stopandbfbtn->setIcon(QIcon(":/icon/bf.png"));
}

void MainWindow::handlemodou() {
    g_mode = static_cast<PlayMode>((g_mode + 1) % 3);
    QString iconPath;
    switch (g_mode) {
    case ORDER_PLAY:
        iconPath = ":/icon/order.png";
        ui->moshibtn->setToolTip("顺序播放");
        break;
    case SINGLE_LOOP:
        iconPath = ":/icon/danqu.png";
        ui->moshibtn->setToolTip("单曲循环");
        break;
    case RANDOM_PLAY:
        iconPath = ":/icon/random.png";
        ui->moshibtn->setToolTip("随机播放");
        break;
    }
    ui->moshibtn->setIcon(QIcon(iconPath));
}

void MainWindow::handleshowmusiclist() {
    musiclistVisible = !musiclistVisible;
    if (musiclistVisible) {
        ui->mclist->show();
        ui->musiclistbtn->setIcon(QIcon(":/icon/down.png")); // 下拉图标
    } else {
        ui->mclist->hide();
        ui->musiclistbtn->setIcon(QIcon(":/icon/music.png"));
    }
}

void MainWindow::loadappointmusicdir(const QString &filename) {
    QDir dir(filename);
    if (!dir.exists()) {
        QMessageBox::warning(this, "警告", "文件夹不存在");
        return;
    }

    QFileInfoList filelist = dir.entryInfoList(QDir::Files);
    for (auto x : filelist) {
        if (x.suffix() == "mp3") {
            g_musiclist << x.absoluteFilePath();
            ui->mclist->addItem(x.baseName());
        }
    }
}

MainWindow::~MainWindow() {
    delete ui;
}
