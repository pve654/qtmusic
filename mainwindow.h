#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QString>
#include <QPushButton>
#include <QMediaPlayer>
#include <QAudioOutput>
#include <QTimer>
#include <QMap>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

struct LyricLine {
    qint64 time;   // 毫秒
    QString text;  // 歌词
};

class MainWindow : public QMainWindow {
    Q_OBJECT
public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void loadMusicAndLyrics(const QString &musicDir, const QString &lyricDir); // 加载音乐和歌词
    void loadLyrics(const QString &musicPath);        // 加载歌词

public slots:
    void handlestopandbf();          // 播放/暂停
    void handleprev();               // 上一首
    void handlenext();               // 下一首
    void handlemodou();              // 播放模式
    void handleshowmusiclist();      // 显示/隐藏音乐列表
    void updateCurrentMusicLabel();  // 当前播放歌曲
    void updateLyric();              // 更新歌词

private:
    void setBackGround(const QString &filename);
    void setbtnstyle(QPushButton *button, const QString &filename);
    void initbtn();

private:
    Ui::MainWindow *ui;
    QMediaPlayer *m_player;
    QAudioOutput *m_output;
    QTimer *lyricTimer;

    bool musiclistVisible = false;   // 音乐列表显示状态
    int g_index;
    enum PlayMode { ORDER_PLAY, SINGLE_LOOP, RANDOM_PLAY } g_mode;

    QStringList g_musiclist;
    QMap<QString, QString> musicLyrics; // key=mp3路径, value=lrc路径
    QMap<qint64, QString> lyrics;       // key=时间毫秒，value=歌词文本
};

#endif // MAINWINDOW_H
