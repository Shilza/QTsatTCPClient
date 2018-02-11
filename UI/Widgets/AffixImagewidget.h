#ifndef AFFIXIMAGEWIDGET_H
#define AFFIXIMAGEWIDGET_H

#include <QEvent>
#include <QBuffer>
#include <QTimer>
#include <QHBoxLayout>
#include <QPushButton>
#include <QPropertyAnimation>
#include <QGraphicsOpacityEffect>
#include "UI/Widgets/clickablelabel.h"
#include "Util/tcpclient.h"

class AffixImageWidget : public QWidget
{
    Q_OBJECT
public:
    explicit AffixImageWidget(QWidget *parent=0);
    QWidget *getSendedImage();
    ~AffixImageWidget();
private:
    QWidget *mainWidget;
    QHBoxLayout *mainAffixLayout;
    QPushButton *sendedImage;
    QPushButton *buttonCloseAffixedPicture;
    QPushButton *toolTipAffixClose;
    QPushButton *originalSize;
    QPushButton *buttonOk;
    ClickableLabel *labelLoadError;
    QGraphicsOpacityEffect *opacity;
    QPixmap affixImage;
    QString extension;

    quint8 sendedImageSize = 60;
    quint8 closeButtonSize = 12;
    bool isLoadError = false;

    bool eventFilter(QObject *target, QEvent *event);

signals:
    void originalSizeReleased(QPixmap);
    void detachmentImage();

public slots:
    void receivedImageTreatment(QPixmap image, QString extension);

private slots:
    void originalSize_released();
    void buttonCloseAffixedPicture_released();
    void affixError();
    void affixAllow();
    void showButtonOk();
    void hideButtonOk();
    void clearing();
};

#endif // AFFIXIMAGEWIDGET_H
