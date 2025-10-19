#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QIcon"
#include "Qstring"
#include "QPushButton"
#include "QList"
#include "QDebug"

//图片类
#include <QPixmap>
#include "QPalette"

#include <QMediaPlayer>
#include <QAudioOutput>
#include <QUrl>

/*文件系统*/
#include "QDir"      // 目录
#include "QFile"     // 文件
#include "QFileInfo" // 文件信息


#include "QMessageBox" //对话框

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    /*设置文本框标题*/
    setWindowIcon(QIcon(":/icon/logo.png"));
    setWindowTitle("随心音乐播放器");
    setFixedSize(960,600);
    setBackGround(":/images/bg.png");

    /*初始化按钮*/
    initbtn();
    loadappointmusicdir("E:\\music");


    m_player = new QMediaPlayer(this);

    m_output = new QAudioOutput(this);
    m_player->setAudioOutput(m_output);
    m_output->setVolume(0.5); // 0~1
    m_player->setSource(QUrl::fromLocalFile(R"(E:\music\不凡2024 (Live)-王铮亮.mp3)"));
}

void MainWindow::setBackGround(const QString & filename){

    /*创建照片*/
    QPixmap pixmap(filename);

    /*设置窗口大小*/
    QSize windowSize = this->size();

    // 知道窗口大小，我们只需要将图片放到或者缩小即可
    QPixmap scalePixmap = pixmap.scaled(windowSize, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);

    //创建QPalette对象并设置背景图片 -调色版
    QPalette palette = this->palette();
    palette.setBrush(QPalette::Window, QBrush(scalePixmap));

    // 将调色版应用到窗口上
    this->setPalette(palette);
}

void MainWindow::setbtnstyle(QPushButton * button,const QString & filename){
    button->setFixedSize(50,50);
    button->setIcon(QIcon(filename));
    button->setIconSize(QSize(button->width(),button->height()));
    button->setStyleSheet(
        "background-color: transparent;"   // 背景透明
        "border: none;"                    // 去掉边框
    );
}

void MainWindow::initbtn() {
    setbtnstyle(ui->prebtn,":/icon/pre.png");
    setbtnstyle(ui->stopandbfbtn,":/icon/stop.png");
    setbtnstyle(ui->netbtn,":/icon/nxt.png");
    setbtnstyle(ui->moshibtn,":/icon/order.png");
    setbtnstyle(ui->musiclistbtn,":/icon/music.png");

    connect(ui->stopandbfbtn, &QPushButton::clicked, this, &MainWindow::handlestopandbf);
}


void MainWindow::handlestopandbf(){        //播放暂停
    if(m_player->playbackState() == QMediaPlayer::PlayingState){
        m_player->pause();
        ui->stopandbfbtn->setIcon(QIcon(":/icon/stop.png"));
    }
    else{
        m_player->play();
        ui->stopandbfbtn->setIcon(QIcon(":/icon/bf.png"));
    }
}

void MainWindow::loadappointmusicdir(const QString & filename){ //加载指定文件夹下的音乐资源
    QDir dir(filename);
    if(!dir.exists()){
        QMessageBox::warning(this, "警告", "文件夹不存在");
        return;
    }

    QFileInfoList filelist = dir.entryInfoList(QDir::Files);
    for(auto x : filelist){
        if(x.suffix() == "mp3"){
            ui->mclist->addItem(x.baseName());
            qDebug() << x.baseName() << '\n';
        }
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}
