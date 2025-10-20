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
#include <QTextStream>
#include <QGraphicsBlurEffect>
#include <QRegularExpression>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , m_player(nullptr)
    , m_output(nullptr)
    , lyricTimer(nullptr)
    , musiclistVisible(false)
    , g_index(0)
    , g_mode(ORDER_PLAY)
{
    ui->setupUi(this);

    setWindowIcon(QIcon(":/icon/logo.png"));
    setWindowTitle("随心音乐播放器");
    setFixedSize(960, 600);
    setBackGround(":/images/bg.png");

    initbtn();

    // 加载音乐和歌词
    loadMusicAndLyrics("E:\\music\\mp3", "E:\\music\\lrc");

    m_player = new QMediaPlayer(this);
    m_output = new QAudioOutput(this);
    m_player->setAudioOutput(m_output);
    m_output->setVolume(0.5);

    lyricTimer = new QTimer(this);
    connect(lyricTimer, &QTimer::timeout, this, &MainWindow::updateLyric);
    lyricTimer->start(100); // 每100ms更新一次歌词

    if(!g_musiclist.isEmpty()) {
        m_player->setSource(QUrl::fromLocalFile(g_musiclist[g_index]));
        loadLyrics(g_musiclist[g_index]);
        updateCurrentMusicLabel();
    }

    // 自动播放下一首
    connect(m_player, &QMediaPlayer::mediaStatusChanged, this, [=](QMediaPlayer::MediaStatus s){
        if(s == QMediaPlayer::EndOfMedia) handlenext();
    });

    // 播放进度更新
    connect(m_player, &QMediaPlayer::positionChanged, this, [=](qint64 pos){
        ui->progressSlider->setValue(pos);
        ui->nowtimelbl->setText(QTime(0,0,0).addMSecs(pos).toString("mm:ss"));
    });

    // 音乐总时长
    connect(m_player, &QMediaPlayer::durationChanged, this, [=](qint64 dur){
        ui->progressSlider->setRange(0,dur);
        ui->totaltimelbl->setText(QTime(0,0,0).addMSecs(dur).toString("mm:ss"));
    });

    // 拖动进度条
    connect(ui->progressSlider, &QSlider::sliderMoved, this, [=](int val){
        m_player->setPosition(val);
    });

    // 初始隐藏音乐列表
    ui->mclist->hide();

    // lyricWidget 仅显示背景并模糊
    ui->lyricWidget->setStyleSheet("background: rgba(160, 200, 255, 0.3); border-radius: 10px;");
    QGraphicsBlurEffect *blur = new QGraphicsBlurEffect(this);
    blur->setBlurRadius(10);
    ui->lyricWidget->setGraphicsEffect(blur);

    // lyricLabel 放在 lyricWidget 上，但不要被 blur 覆盖
    ui->lyricLabel->setParent(ui->centralwidget); // 或直接 MainWindow
    ui->lyricLabel->raise();                      // 保证在最上层
    ui->lyricLabel->setGeometry(ui->lyricWidget->geometry()); // 与背景对齐
    ui->lyricLabel->setAlignment(Qt::AlignCenter);
    ui->lyricLabel->setStyleSheet(
        "color: #1e3a8a;"
        "background: transparent;"
        "font-size: 20px;"
        "font-weight: bold;"
        );
    ui->lyricLabel->setText("等待播放歌词...");
}

// -------------------- UI --------------------
void MainWindow::setBackGround(const QString &filename){
    QPixmap pixmap(filename);
    QSize windowSize = this->size();
    QPixmap scalePixmap = pixmap.scaled(windowSize, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
    QPalette palette = this->palette();
    palette.setBrush(QPalette::Window, QBrush(scalePixmap));
    this->setPalette(palette);
}

void MainWindow::setbtnstyle(QPushButton *button, const QString &filename){
    button->setFixedSize(50,50);
    button->setIcon(QIcon(filename));
    button->setIconSize(QSize(button->width(), button->height()));
    button->setStyleSheet("background-color: transparent; border: none;");
}

void MainWindow::initbtn(){
    setbtnstyle(ui->prebtn, ":/icon/pre.png");
    setbtnstyle(ui->stopandbfbtn, ":/icon/stop.png");
    setbtnstyle(ui->netbtn, ":/icon/nxt.png");
    setbtnstyle(ui->moshibtn, ":/icon/order.png");
    setbtnstyle(ui->musiclistbtn, ":/icon/music.png");

    // 音乐列表样式
    ui->mclist->setStyleSheet(
        "QListWidget {"
        " background: rgba(255, 255, 255, 0.1);"
        " color:#1e3a8a;"
        " border: 1px solid rgba(255, 255, 255, 0.2);"
        " border-radius: 8px;"
        " font-size: 14px;} "
        "QListWidget::item:selected {"
        " background: rgba(160, 200, 255, 0.3);"
        " color: white;}");

    connect(ui->stopandbfbtn, &QPushButton::clicked, this, &MainWindow::handlestopandbf);
    connect(ui->prebtn, &QPushButton::clicked, this, &MainWindow::handleprev);
    connect(ui->netbtn, &QPushButton::clicked, this, &MainWindow::handlenext);
    connect(ui->moshibtn, &QPushButton::clicked, this, &MainWindow::handlemodou);
    connect(ui->musiclistbtn, &QPushButton::clicked, this, &MainWindow::handleshowmusiclist);
}

// -------------------- 音乐操作 --------------------
void MainWindow::handlestopandbf(){
    if(m_player->playbackState() == QMediaPlayer::PlayingState){
        m_player->pause();
        ui->stopandbfbtn->setIcon(QIcon(":/icon/stop.png"));
    } else {
        m_player->play();
        ui->stopandbfbtn->setIcon(QIcon(":/icon/bf.png"));
    }
}

void MainWindow::updateCurrentMusicLabel(){
    if(!g_musiclist.isEmpty()){
        QFileInfo fi(g_musiclist[g_index]);
        ui->currentMusicLbl->setText(fi.completeBaseName());
    } else {
        ui->currentMusicLbl->setText("未播放");
    }
}

void MainWindow::handleprev(){
    if(g_musiclist.isEmpty()) return;
    if(g_mode == RANDOM_PLAY){
        g_index = QRandomGenerator::global()->bounded(g_musiclist.size());
    } else {
        g_index = (g_index - 1 + g_musiclist.size()) % g_musiclist.size();
    }
    m_player->setSource(QUrl::fromLocalFile(g_musiclist[g_index]));
    m_player->play();
    ui->stopandbfbtn->setIcon(QIcon(":/icon/bf.png"));
    updateCurrentMusicLabel();
    loadLyrics(g_musiclist[g_index]);
}

void MainWindow::handlenext(){
    if(g_musiclist.isEmpty()) return;
    if(g_mode == RANDOM_PLAY){
        g_index = QRandomGenerator::global()->bounded(g_musiclist.size());
    } else if(g_mode == SINGLE_LOOP){
        // 单曲循环，不改变索引
    } else {
        g_index = (g_index + 1) % g_musiclist.size();
    }
    m_player->setSource(QUrl::fromLocalFile(g_musiclist[g_index]));
    m_player->play();
    ui->stopandbfbtn->setIcon(QIcon(":/icon/bf.png"));
    updateCurrentMusicLabel();
    loadLyrics(g_musiclist[g_index]);
}

void MainWindow::handlemodou(){
    g_mode = static_cast<PlayMode>((g_mode + 1) % 3);
    QString iconPath;
    switch(g_mode){
    case ORDER_PLAY: iconPath=":/icon/order.png"; break;
    case SINGLE_LOOP: iconPath=":/icon/danqu.png"; break;
    case RANDOM_PLAY: iconPath=":/icon/random.png"; break;
    }
    ui->moshibtn->setIcon(QIcon(iconPath));
}

void MainWindow::handleshowmusiclist(){
    musiclistVisible = !musiclistVisible;
    ui->mclist->setVisible(musiclistVisible);
}

// -------------------- 音乐列表和歌词 --------------------
void MainWindow::loadMusicAndLyrics(const QString &musicDir, const QString &lyricDir){
    QDir mDir(musicDir);
    QDir lDir(lyricDir);

    if(!mDir.exists() || !lDir.exists()){
        QMessageBox::warning(this, "警告", "音乐或歌词文件夹不存在");
        return;
    }

    QFileInfoList musicFiles = mDir.entryInfoList(QStringList() << "*.mp3", QDir::Files);
    for(auto &musicFile : musicFiles){
        QString musicPath = musicFile.absoluteFilePath();
        QString baseName = musicFile.completeBaseName();
        g_musiclist << musicPath;
        ui->mclist->addItem(baseName);

        QString lrcPath = lDir.filePath(baseName + ".lrc");
        if(QFile::exists(lrcPath)){
            musicLyrics[musicPath] = lrcPath;
        } else {
            musicLyrics[musicPath] = "";
        }
    }
}

void MainWindow::loadLyrics(const QString &musicPath){
    lyrics.clear();
    QString baseName = QFileInfo(musicPath).completeBaseName();
    QString lrcPath = "E:\\music\\lrc\\" + baseName + ".lrc";

    QFile file(lrcPath);
    if(!file.open(QIODevice::ReadOnly | QIODevice::Text)) return;

    QTextStream in(&file);
    QRegularExpression re(R"(\[(\d{1,2}):(\d{2})\.(\d{2,3})\](.*))");

    while(!in.atEnd()){
        QString line = in.readLine();
        QRegularExpressionMatch match = re.match(line);
        if(match.hasMatch()){
            int m = match.captured(1).toInt();
            int s = match.captured(2).toInt();
            int ms = match.captured(3).toInt();
            if(ms < 100) ms *= 10; // 两位毫秒
            QString text = match.captured(4).trimmed();
            qint64 time = (m*60 + s)*1000 + ms;
            lyrics[time] = text;
        }
    }
    ui->lyricLabel->setText("歌词加载完成");
}

void MainWindow::updateLyric(){
    if(lyrics.isEmpty()) return;
    qint64 pos = m_player->position();
    auto it = lyrics.lowerBound(pos); // 找第一个 >= pos 的时间
    QString text;
    if(it == lyrics.constEnd() || it.key() > pos){
        if(it != lyrics.constBegin()) --it;
        text = it.value();
    } else {
        text = it.value();
    }
    ui->lyricLabel->setText(text);
}


MainWindow::~MainWindow(){
    delete ui;
}
