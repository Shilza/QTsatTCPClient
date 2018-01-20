#ifndef AFFIXIMAGEWIDGET_H
#define AFFIXIMAGEWIDGET_H
#include <QPushButton>
#include <QEvent>
#include <QHBoxLayout>
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
    ClickableLabel *labelLoadError;
    QPixmap affixImage;

    quint8 sendedImageSize = 60;
    quint8 closeButtonSize = 12;
    bool isLoadError = false;

    bool eventFilter(QObject *target, QEvent *event);

signals:
    void originalSizeReleased(QPixmap);
    void detachmentImage();

public slots:
    void receivedImageTreatment(QPixmap);

private slots:
    void originalSize_released();
    void buttonCloseAffixedPicture_released();
    void affixError();
    void affixAllow();
};

#endif // AFFIXIMAGEWIDGET_H
