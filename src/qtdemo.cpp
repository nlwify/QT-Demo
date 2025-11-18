#include "qtdemo.h"
#include<QFileDialog>
#include<QFileInfo>

qtdemo::qtdemo(QWidget* parent)
    : QMainWindow(parent)
    , ui(new Ui_qtdemo), currentTrackIndex(-1)
{
    ui->setupUi(this);

    // 初始化媒体播放器和音频输出
    player = new QMediaPlayer(this);
    audioOutput = new QAudioOutput(this);
    player->setAudioOutput(audioOutput);

    //设置初始音量50%
    audioOutput->setVolume(0.75);
    ui->volumeSlider->setRange(0, 100);
    ui->volumeSlider->setValue(75);
    ui->volumeValueLabel->setText("75%");
    //连接播放列表双击信号
    connect(ui->playlist, &QListWidget::itemDoubleClicked, this, &qtdemo::onPlaylistItemDoubleClicked);

    //连接播放器位置变化信号
    connect(player, &QMediaPlayer::positionChanged, this, &qtdemo::onPositionChanged);
    connect(player, &QMediaPlayer::durationChanged, this, &qtdemo::onDurationChanged);
    connect(ui->positionSlider, &QSlider::sliderMoved, this, &qtdemo::onMediaSliderMoved);

    //连接音量滑动变化
    connect(ui->volumeSlider, &QSlider::sliderMoved, this, &qtdemo::onVolumeSliderMoved);
}

qtdemo::~qtdemo()
{
    delete ui; 
}

void qtdemo::on_openButton_clicked(){
    //打开文件对话框
    QStringList fileNames = QFileDialog::getOpenFileNames(this, "选择音频文件", "", "音频文件 (*.mp3 *.wav *.ogg);;所有文件 (*.*)");
    
    for(auto &filename : fileNames){
        QFileInfo fileInfo(filename);
        QListWidgetItem *item = new QListWidgetItem(fileInfo.fileName());
        item->setData(Qt::UserRole, filename);
        ui->playlist->addItem(item);
    }

    if(!fileNames.empty()){
        if(currentTrackIndex == -1){
            currentTrackIndex = 0;
            ui->playlist->setCurrentRow(0);
        }
        ui->statusBar->showMessage(QString("已添加 %1 首歌曲到播放列表").arg(fileNames.size()), 5000);
    }
}

void qtdemo::on_playButton_clicked(){
    if(player->source().isEmpty()){
        //如果没有设置播放源，则从播放列表获取第一首歌
        if(ui->playlist->count() == 0){
            ui->statusBar->showMessage("播放列表为空，请先添加歌曲", 5000);
            return;
        }
        loadTrackByIndex(currentTrackIndex == -1 ? 0 : currentTrackIndex);
    }
    player->play();
}

void qtdemo::on_pauseButton_clicked(){
    player->pause();
}

void qtdemo::on_prevButton_clicked(){
    if(ui->playlist->count() == 0){
        ui->statusBar->showMessage("播放列表为空，请先添加歌曲", 5000);
        return;
    } 
    int newIndex;
    if(currentTrackIndex <= 0){
        //如果是第一首，循环到最后一首
        newIndex = ui->playlist->count() -1;
    }
    else{
        newIndex = currentTrackIndex -1; 
    }

    loadTrackByIndex(newIndex);
    player->play();
}

void qtdemo::on_nextButton_clicked(){
    if(ui->playlist->count() == 0){
        ui->statusBar->showMessage("播放列表为空，请先添加歌曲", 5000);
        return;
    }
    int newIndex;
    if(currentTrackIndex >= ui->playlist->count() -1){
        //如果是最后一首，循环到第一首
        newIndex = 0;
    }
    else{
        newIndex = currentTrackIndex + 1;
    }
    loadTrackByIndex(newIndex);
    player->play();
}

void qtdemo::loadTrackByIndex(int index){
    if(index <0 || index >= ui->playlist->count()){
        return;
    }

    currentTrackIndex = index;

    QListWidgetItem *item = ui->playlist->item(index);
    if(!item) return;

    QString filePath = item->data(Qt::UserRole).toString();
    if(filePath.isEmpty()) return;

    player->setSource(QUrl::fromLocalFile(filePath));

    ui->playlist->setCurrentRow(index);
    ui->nowPlayingLabel->setText(item->text());
}

void qtdemo::onPlaylistItemDoubleClicked(QListWidgetItem *item){
    int index = ui->playlist->row(item);
    loadTrackByIndex(index);
    player->play();
}

void qtdemo::onPositionChanged(qint64 position){
    if(!ui->positionSlider->isSliderDown()){
        ui->positionSlider->setValue(position);
    }
    ui->currentTimeLabel->setText(QString("%1:%2")
        .arg(position / 60000, 2, 10, QChar('0'))
        .arg((position / 1000) % 60, 2, 10, QChar('0')));
}

void qtdemo::onMediaSliderMoved(int position){
    player->setPosition(position);
}

void qtdemo::onDurationChanged(qint64 duration){
    ui->positionSlider->setRange(0, duration);
    ui->totalTimeLabel->setText(QString("%1:%2")
        .arg(duration / 60000, 2, 10, QChar('0'))
        .arg((duration / 1000) % 60, 2, 10, QChar('0')));
}

void qtdemo::onVolumeSliderMoved(int position){
    qreal volume = static_cast<qreal>(position) / 100.0;
    audioOutput->setVolume(volume);
    ui->volumeValueLabel->setText(QString("%1%").arg(position));
}
