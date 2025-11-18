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
    void on_openButton_clicked();
    void on_playButton_clicked();
    void on_pauseButton_clicked();
    void on_prevButton_clicked();
    void on_nextButton_clicked();

    void onPlaylistItemDoubleClicked(QListWidgetItem *item);
};