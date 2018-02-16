#include "affixaudiowidget.h"

AffixAudioWidget::AffixAudioWidget(QWidget *parent) : QWidget(parent){
    close();
    const QString sliderStyle = "QSlider{"
                                "border: 0px;"
                                "background: transparent;"
                                "}"
                                "QSlider::groove:horizontal{"
                                "border: 1px solid #bbb;"
                                "height: 2px;"
                                "}"
                                "QSlider::sub-page:horizontal {"
                                "background: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1,"
                                "stop: 0 #66e, stop: 1 black);"
                                "border: 1px solid #777;"
                                "height: 6px;"
                                "border-radius: 3px;"
                                "}"
                                "QSlider::handle:horizontal{"
                                "margin-top: -4px;"
                                "margin-bottom: -4px;"
                                "width: 6px;"
                                "border-radius: 3px;"
                                "}"
                                "QSlider::handle:horizontal:hover{"
                                "background: white;"
                                "border: 1px solid black;"
                                "}";

    mainWidget = new QWidget(this);
    mainLayout = new QGridLayout(mainWidget);

    labelTrack = new QLabel(mainWidget);
    labelCurrentTime = new QLabel(mainWidget);
    labelEndTime = new QLabel(mainWidget);
    sliderTrack = new QSlider(Qt::Horizontal, mainWidget);
    sliderVolume = new QSlider(Qt::Vertical, mainWidget);
    buttonControll = new QPushButton(mainWidget);

    mainWidget->setLayout(mainLayout);
}

QWidget *AffixAudioWidget::getMainWidget() const{
    return mainWidget;
}
