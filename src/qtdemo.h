#pragma once
#include "ui_qtdemo.h"
#include <QMainWindow>
#include<QMediaPlayer>
#include<QAudioOutput>

class qtdemo : public QMainWindow {
    Q_OBJECT
    
public:
    qtdemo(QWidget* parent = nullptr);
    ~qtdemo();

private:
    Ui_qtdemo* ui;
    QMediaPlayer *player;
    QAudioOutput *audioOutput;

    void loadTrackByIndex(int index);
    //当前曲目索引
    int currentTrackIndex;
private slots:
    //打开按钮
    void on_openButton_clicked();
    //播放按钮
    void on_playButton_clicked();
    //暂停按钮
    void on_pauseButton_clicked();
    //上一首按钮
    void on_prevButton_clicked();
    //下一首按钮
    void on_nextButton_clicked();

    //播放列表双击
    void onPlaylistItemDoubleClicked(QListWidgetItem *item);
    //播放进度控制
    void onPositionChanged(qint64 position);
    void onDurationChanged(qint64 duration);
    void onMediaSliderMoved(int position);
    void onVolumeSliderMoved(int position);
};