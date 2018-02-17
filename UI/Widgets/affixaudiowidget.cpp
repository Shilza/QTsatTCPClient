#include "affixaudiowidget.h"
#include <QDebug>

AffixAudioWidget::AffixAudioWidget(QWidget *parent) : QWidget(parent){
    close();

    mainWidget = new QWidget(parent);
    mainLayout = new QGridLayout(mainWidget);

    labelTrack = new QLabel("Sas - sgdofkgdkjfgolkdg", mainWidget);
    labelCurrentTime = new QLabel("0:00",mainWidget);
    labelEndTime = new QLabel(mainWidget);
    sliderTrack = new QSlider(Qt::Horizontal, mainWidget);
    sliderVolume = new QSlider(Qt::Vertical, mainWidget);
    buttonControll = new QPushButton(mainWidget);
    buttonClose = new QPushButton(mainWidget);

    mainWidget->setLayout(mainLayout);
    mainWidget->setStyleSheet("background: #EFFAF8;"
                              "border: 1px solid black;"
                              "border-radius: 2px;");
    mainWidget->setFixedSize(272, 54);

    buttonClose->setStyleSheet("background: transparent;"
                               "border: 0px;");
    buttonClose->move(mainWidget->width()-15, 0);
    buttonClose->setFixedSize(15, 15);
    buttonClose->setIcon(QIcon(":/images/close1.png"));
    buttonClose->setIconSize(buttonClose->size());
    buttonClose->setToolTip("Detach");

    buttonControll->setFixedSize(40, 40);
    buttonControll->setStyleSheet("background: #393838;"
                                  "border: 0px;"
                                  "border-radius: 20px;");
    buttonControll->setIcon(QIcon(":images/play.png"));
    buttonControll->setIconSize(buttonControll->size());

    labelTrack->setStyleSheet("border: 0px");

    labelCurrentTime->setFixedHeight(12);
    labelCurrentTime->setStyleSheet("border: 0px;"
                                    "border-radius: 2px;");

    labelEndTime->setFixedHeight(12);
    labelEndTime->setStyleSheet("border: 0px;"
                                "border-radius: 2px;");

    sliderTrack->setStyleSheet("QSlider{"
                               "border: 0px;"
                               "background: transparent;"
                               "}"
                               "QSlider::groove:horizontal{"
                               "border: 1px solid #bbb;"
                               "height: 2px;"
                               "}"
                               "QSlider::sub-page:horizontal {"
                               "background: qlineargradient(x1: 0, y1: 0, x2: 1, y2: 0,"
                               "stop: 0 #66e, stop: 1 #393838);"
                               "border: 1px solid #777;"
                               "height: 6px;"
                               "border-radius: 3px;"
                               "}"
                               "QSlider::handle:horizontal{"
                               "margin-top: -3px;"
                               "margin-bottom: -3px;"
                               "width: 6px;"
                               "height: 6px;"
                               "border-radius: 3px;"
                               "}"
                               "QSlider::handle:horizontal:hover{"
                               "background: white;"
                               "border: 1px solid black;"
                               "}");
    sliderTrack->setFixedHeight(10);

    sliderVolume->setStyleSheet("QSlider{"
                                "border: 0px;"
                                "background: transparent;"
                                "}"
                                "QSlider::groove:vertical{"
                                "border: 1px solid #bbb;"
                                "border-radius: 1px;"
                                "width: 4px;"
                                "}"
                                "QSlider::add-page:vertical{"
                                "background: qlineargradient(x1: 0, y1: 1, x2: 0, y2: 0,"
                                "stop: 0 #66e, stop: 1 black);"
                                "border: 1px solid #777;"
                                "width: 6px;"
                                "border-radius: 3px;"
                                "}"
                                "QSlider::handle:vertical{"
                                "margin-top: -3px;"
                                "margin-bottom: -3px;"
                                "height: 6px;"
                                "width: 6px;"
                                "border-radius: 3px;"
                                "}"
                                "QSlider::handle:vertical:hover{"
                                "background: white;"
                                "border: 1px solid black;"
                                "}");
    sliderVolume->setFixedSize(12, 46);
    sliderVolume->setValue(50);
    player.setVolume(50);

    mainLayout->addWidget(buttonControll, 0, 0, 3, 1, Qt::AlignLeft);
    mainLayout->addWidget(labelTrack, 0, 1, 1, 4, Qt::AlignTop);
    mainLayout->addWidget(sliderTrack, 1, 1, 1, 10, Qt::AlignBottom);
    mainLayout->addWidget(sliderVolume, 0, 11, 3, 1, Qt::AlignRight);
    mainLayout->addWidget(labelCurrentTime, 2, 1, 1, 1, Qt::AlignTop | Qt::AlignLeft);
    mainLayout->addWidget(labelEndTime, 2, 10, 1, 1, Qt::AlignTop | Qt::AlignLeft);
    mainLayout->setContentsMargins(6, 4, 14, 4);
    mainLayout->setVerticalSpacing(0);

    connect(buttonControll, SIGNAL(released()), SLOT(musicControl()));
    connect(buttonClose, SIGNAL(released()), SLOT(closing()));
    connect(&(FTPClient::getInstance()), SIGNAL(loadAttachmentAllow()), SLOT(loading()));
    connect(&player, &QMediaPlayer::durationChanged, this, [&](qint64){
        labelEndTime->setText(QString::number(player.duration()/60000) + ":" + QString::number((player.duration()%60000)/1000));
    });
    connect(&player, SIGNAL(positionChanged(qint64)), SLOT(setSliderTrackPosition(qint64)));
    connect(sliderVolume, SIGNAL(valueChanged(int)), &player, SLOT(setVolume(int)));
    connect(sliderTrack, SIGNAL(valueChanged(int)), SLOT(setSongValue(int)));
    connect(sliderTrack, QSlider::sliderPressed, this, [&](){ isSliderTrackPressed = true; });
    connect(sliderTrack, QSlider::sliderReleased, this, [&](){ isSliderTrackPressed = false; });
}

QWidget *AffixAudioWidget::getMainWidget() const{
    return mainWidget;
}

void AffixAudioWidget::receivedSongTreatment(QByteArray song, QString filePath){
    this->song = song;
    player.setMedia(QUrl::fromLocalFile(filePath));
}

void AffixAudioWidget::musicControl(){
    static bool isPlaying = true;

    if(isPlaying){
        buttonControll->setIcon(QIcon(":images/pause.png"));
        player.play();
    }
    else{
        buttonControll->setIcon(QIcon(":images/play.png"));
        player.pause();
    }

    isPlaying = !isPlaying;
}

void AffixAudioWidget::closing(){
    mainWidget->close();
    emit detachment();
}

void AffixAudioWidget::loading(){
    FTPClient::getInstance().post(song);
}

void AffixAudioWidget::setSliderTrackPosition(qint64 position){
    if(player.duration() != 0 && !isSliderTrackPressed)
        sliderTrack->setValue((position / player.duration()) * 100);
}

void AffixAudioWidget::setSongValue(int value){
    player.setPosition(value*(player.duration()/100));
}
