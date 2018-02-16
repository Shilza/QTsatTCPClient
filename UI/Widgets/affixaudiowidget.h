#ifndef AFFIXAUDIOWIDGET_H
#define AFFIXAUDIOWIDGET_H

#include <QWidget>
#include <QGridLayout>
#include <QLabel>
#include <QPushButton>
#include <QSlider>

class AffixAudioWidget : public QWidget
{
    Q_OBJECT

public:
    explicit AffixAudioWidget(QWidget *parent = nullptr);
    QWidget *getMainWidget() const;

private:
    QWidget *mainWidget;
    QGridLayout *mainLayout;
    QLabel *labelTrack;
    QLabel *labelCurrentTime;
    QLabel *labelEndTime;
    QSlider *sliderTrack;
    QSlider *sliderVolume;
    QPushButton *buttonControll;
};

#endif // AFFIXAUDIOWIDGET_H
