#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "Qstring"
#include "QPushButton"

#include "QMediaPlayer" //音视频解码器
#include <QAudioOutput>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void loadappointmusicdir(const QString & filename); //加载指定文件夹下的音乐资源


public slots:
    void handlestopandbf();        //播放暂停


private:

    /*设置背景图片*/
    void setBackGround(const QString & filename);

    /*设置按钮风格*/
    void setbtnstyle(QPushButton * button,const QString & filename);

    /*调用按钮风格进行初始化*/
    void initbtn();

private:
    Ui::MainWindow *ui;
    QMediaPlayer * m_player;         // 音乐播放器
    QAudioOutput * m_output;         // 音频输出
};
#endif // MAINWINDOW_H
