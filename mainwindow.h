#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QString>
#include <QPushButton>
#include <QMediaPlayer>
#include <QAudioOutput>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
    Q_OBJECT
public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void loadappointmusicdir(const QString &filename); // 加载指定文件夹音乐

public slots:
    void handlestopandbf();        // 播放/暂停
    void handleprev();             // 上一首
    void handlenext();             // 下一首
    void handlemodou();            // 播放模式
    void handleshowmusiclist();    // 显示/隐藏音乐列表

private:
    void setBackGround(const QString &filename);
    void setbtnstyle(QPushButton *button, const QString &filename);
    void initbtn();

private:
    Ui::MainWindow *ui;
    QMediaPlayer *m_player;
    QAudioOutput *m_output;
    bool musiclistVisible = false; // 音乐列表显示状态
};

#endif // MAINWINDOW_H
