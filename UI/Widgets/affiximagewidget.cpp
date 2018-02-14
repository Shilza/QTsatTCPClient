#include "AffixImagewidget.h"

AffixImageWidget::AffixImageWidget(QWidget *parent) : QWidget(parent){
    close();

    mainWidget = new QWidget(parent);
    mainAffixLayout = new QHBoxLayout(mainWidget);
    sendedImage = new QPushButton(mainWidget);
    toolTipAffixClose = new QPushButton(parent);
    originalSize = new QPushButton(sendedImage);
    labelLoadError = new ClickableLabel(sendedImage, false);
    buttonOk = new QPushButton(sendedImage);
    buttonCloseAffixedPicture = new QPushButton(sendedImage);
    opacity = new QGraphicsOpacityEffect(buttonOk);

    sendedImage->installEventFilter(this);

    mainAffixLayout->setMargin(5);
    mainWidget->setLayout(mainAffixLayout);

    sendedImage->setFixedSize(sendedImageSize, sendedImageSize);
    sendedImage->setStyleSheet("border: 1px solid black;");
    sendedImage->close();

    buttonOk->setFixedSize(sendedImage->size());
    buttonOk->setStyleSheet("background: transparent;");
    buttonOk->setIcon(QIcon(":/images/ok.png"));
    buttonOk->setIconSize(buttonOk->size());
    buttonOk->setGraphicsEffect(opacity);
    buttonOk->close();

    originalSize->resize(sendedImage->width(), sendedImage->width());
    originalSize->setIcon(QIcon(":/images/originalSize.png"));
    originalSize->setIconSize(QSize(sendedImage->width(), sendedImage->width()));
    originalSize->setStyleSheet("background: transparent;"
                                "border: 0px;");
    originalSize->close();

    buttonCloseAffixedPicture->setGeometry(originalSize->width()-closeButtonSize-2, 2, closeButtonSize, closeButtonSize);
    buttonCloseAffixedPicture->setIcon(QIcon(":/images/affixClose.png"));
    buttonCloseAffixedPicture->setIconSize(QSize(closeButtonSize, closeButtonSize));
    buttonCloseAffixedPicture->setStyleSheet("background: white;"
                                             "border-radius: 6px;"
                                             "border: 0px;");
    buttonCloseAffixedPicture->installEventFilter(this);

    toolTipAffixClose->setStyleSheet("background: transparent;"
                                     "border: 0px;");
    toolTipAffixClose->setGeometry(0, 0, 100, 26);
    toolTipAffixClose->setIcon(QIcon(":/images/toolTipAffixClose.png"));
    toolTipAffixClose->setIconSize(QSize(100, 26));
    toolTipAffixClose->close();

    labelLoadError->close();
    labelLoadError->setText("Error");
    labelLoadError->setAlignment(Qt::AlignCenter);
    labelLoadError->setFixedSize(originalSize->size());
    labelLoadError->setStyleSheet("background: rgba(0, 0, 0, 150);"
                                  "border: 0px;"
                                  "color: white;");

    connect(originalSize, SIGNAL(released()), SLOT(showOrigin()));
    connect(buttonOk, SIGNAL(released()), SLOT(showOrigin()));
    connect(buttonCloseAffixedPicture, SIGNAL(released()), SLOT(buttonCloseAffixedPicture_released()));
    connect(&(TCPClient::getInstance()), SIGNAL(exit(bool)), SLOT(buttonCloseAffixedPicture_released()));
    connect(&(FTPClient::getInstance()), SIGNAL(loadAttachmentDeny()), SLOT(affixError()));
    connect(&(FTPClient::getInstance()), SIGNAL(loadAttachmentAllow()), SLOT(affixAllow()));
    connect(&(FTPClient::getInstance()), SIGNAL(postIsFinished(QString)), SLOT(showButtonOk()));
    connect(&(TCPClient::getInstance()), SIGNAL(messageSended()), SLOT(clearing()));
}

QWidget *AffixImageWidget::getSendedImage(){
    return mainWidget;
}

void AffixImageWidget::receivedImageTreatment(QPixmap image, QString extension){
    this->extension = extension;
    affixImage = image;

    if(image.height() > image.width()){
        int leftTop = image.height()/2-image.width()/2;

        QRect rect(0, leftTop, image.width(), image.width());
        image = image.copy(rect);
    }
    else if(image.height() < image.width()){
        int leftTop = image.width()/2-image.height()/2;

        QRect rect(leftTop, 0, image.height(), image.height());
        image = image.copy(rect);
    }

    if(image.width()<sendedImageSize-2)
        image = image.scaled(sendedImageSize-2,sendedImageSize-2);

    sendedImage->setIcon(QIcon(image));
    sendedImage->setIconSize(QSize(sendedImageSize-2, sendedImageSize-2));
    mainAffixLayout->addWidget(sendedImage, 1, Qt::AlignLeft | Qt::AlignBottom);
    sendedImage->show();
}

void AffixImageWidget::buttonCloseAffixedPicture_released(){
    affixImage = QPixmap(); //cleaning
    labelLoadError->close();
    isLoadError = false;
    sendedImage->close();
    emit detachmentImage();
}

void AffixImageWidget::affixError(){
    isLoadError = true;
    labelLoadError->show();
}

void AffixImageWidget::affixAllow(){
    isLoadError = false;
    labelLoadError->close();
    QByteArray attachment;
    QBuffer buffer(&attachment);
    buffer.open(QIODevice::WriteOnly);
    affixImage.save(&buffer, extension.toStdString().c_str());
    FTPClient::getInstance().post(attachment);
}

void AffixImageWidget::showButtonOk(){
    buttonOk->show();
    opacity->setOpacity(1.0);
    QTimer::singleShot(1000, this, SLOT(hideButtonOk()));
}

void AffixImageWidget::hideButtonOk(){
    QPropertyAnimation *animation = new QPropertyAnimation(opacity, "opacity");
    animation->setDuration(2000);
    animation->setEndValue(0.0);
    animation->start(QAbstractAnimation::DeleteWhenStopped);
    connect(animation, SIGNAL(finished()), buttonOk, SLOT(close()));
}

void AffixImageWidget::clearing(){
    affixImage = QPixmap();
    labelLoadError->close();
    isLoadError = false;
    sendedImage->close();
}

AffixImageWidget::~AffixImageWidget(){
    delete sendedImage;
    delete buttonCloseAffixedPicture;
    delete toolTipAffixClose;
    delete originalSize;
}

bool AffixImageWidget::eventFilter(QObject *target, QEvent *event)
{
    if(target == buttonCloseAffixedPicture){
        if(event->type() == QEvent::HoverEnter){
            QPoint point = parentWidget()->mapFromGlobal(QCursor::pos());
            toolTipAffixClose->move(point.x()-20, point.y()-toolTipAffixClose->height()-toolTipAffixClose->height()/5);
            toolTipAffixClose->show();
        }
        else if(event->type() == QEvent::HoverLeave)
            toolTipAffixClose->close();
    }
    else if(target==sendedImage && !isLoadError && buttonOk->isHidden()){
        if(event->type() == QEvent::HoverEnter)
            originalSize->show();
        else if(event->type() == QEvent::HoverLeave)
            originalSize->close();
    }

    return QObject::eventFilter(target, event);
}

void AffixImageWidget::showOrigin(){
    emit originalSizeReleased(affixImage);
}
