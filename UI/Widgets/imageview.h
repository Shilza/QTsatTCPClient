#ifndef IMAGEVIEW_H
#define IMAGEVIEW_H

#include <QLabel>
#include <QEvent>
#include <QPushButton>
#include "UI/Widgets/clickablelabel.h"
#include <QGridLayout>

class ImageView : public QWidget
{
    Q_OBJECT

public:
    static ImageView& getInstance();
    ImageView(ImageView const&) = delete;
    ImageView& operator= (ImageView const&) = delete;
    ~ImageView();
    void create(QWidget *parent);

private:
    QPushButton *picture;
    QPushButton *buttonClose;
    QGridLayout *mainLayout;
    ClickableLabel *background;
    ImageView(QWidget* parent = nullptr);
    bool eventFilter(QObject *target, QEvent *event);

public slots:
    void setPicture(QPixmap);
};

#endif // IMAGEVIEW_H
