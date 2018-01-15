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
   //explicit ImageView(QWidget *parent=0);
    static ImageView& getInstance();
    ~ImageView();
    void create(QWidget *parent);

private:
    QPushButton *picture;
    QPushButton *buttonClose;
    QGridLayout *mainLayout;
    ClickableLabel *background;
    ImageView(QWidget* parent = 0);
    ImageView(ImageView const&) = delete;
    ImageView& operator= (ImageView const&) = delete;
    bool eventFilter(QObject *target, QEvent *event);

public slots:
    void setPicture(QPixmap);
};

#endif // IMAGEVIEW_H
