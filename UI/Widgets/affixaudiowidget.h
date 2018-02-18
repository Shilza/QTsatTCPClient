#ifndef AFFIXAUDIOWIDGET_H
#define AFFIXAUDIOWIDGET_H

#include <QWidget>
#include <QGridLayout>
#include <QLabel>
#include <QPushButton>
#include <QSlider>
#include <QMediaPlayer>
#include <QBuffer>
#include <QMediaPlayer>
#include "Util/ftpclient.h"

class AffixAudioWidget : public QWidget
{
    Q_OBJECT

public:
    explicit AffixAudioWidget(QWidget *parent = nullptr);
    QPushButton *getMainWidget() const;

public slots:
    void receivedSongTreatment(QByteArray song, QString filePath);

private:
    QPushButton *mainWidget;
    QGridLayout *mainLayout;
    QMediaPlayer player;
    QLabel *labelTrack;
    QLabel *labelCurrentTime;
    QLabel *labelEndTime;
    QSlider *sliderTrack;
    QSlider *sliderVolume;
    QPushButton *buttonControll;
    QPushButton *buttonClose;

    QString filePath;
    QByteArray song;

    bool isSliderTrackPressed = false;

private slots:
    void musicControl();
    void closing();
    void loading();
    void setSliderTrackPosition(qint64 position);
    void setSongValue();

signals:
    void detachment();
};

#endif // AFFIXAUDIOWIDGET_H
