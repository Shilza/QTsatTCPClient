#include "affixcontainer.h"

AffixContainer::AffixContainer(QWidget *parent) : QWidget(parent){
    setStyleSheet("background: transparent;"
                  "border: 0px;");

    affixWidgetContainer = new QPushButton(this);
    affixLayout = new QHBoxLayout(affixWidgetContainer);

    buttonPhotos = new QPushButton(affixWidgetContainer);
    buttonVideos = new QPushButton(affixWidgetContainer);
    buttonAudios = new QPushButton(affixWidgetContainer);
    buttonDocuments = new QPushButton(affixWidgetContainer);
    buttonAffix = new QPushButton(affixWidgetContainer);

    affixWidgetContainer->setLayout(affixLayout);
    affixWidgetContainer->setMinimumHeight(19);
    affixWidgetContainer->setFixedWidth(120);
    affixWidgetContainer->move(150, 6);
    affixWidgetContainer->setContentsMargins(0, 0, 0, 4);
    affixWidgetContainer->setStyleSheet("background: transparent;"
                                        "border-bottom: 1px solid black;");

    buttonDocuments->setIcon(QIcon(":/images/documentsGray"));
    buttonAudios->setIcon(QIcon(":/images/audiosGray.png"));
    buttonVideos->setIcon(QIcon(":/images/videosGray.png"));
    buttonPhotos->setIcon(QIcon(":/images/photosGray.png"));

    buttonPhotos->setFixedSize(15, 15);
    buttonVideos->setFixedSize(15, 15);
    buttonAudios->setFixedSize(15, 15);
    buttonDocuments->setFixedSize(15, 15);

    buttonPhotos->setStyleSheet("border: 0px;");
    buttonVideos->setStyleSheet("border: 0px;");
    buttonAudios->setStyleSheet("border: 0px;");
    buttonDocuments->setStyleSheet("border: 0px;");

    buttonAffix->setFixedSize(15,20);
    buttonAffix->setIcon(QIcon(":images/affix30.png"));
    buttonAffix->setIconSize(QSize(15,20));
    buttonAffix->setStyleSheet("background: transparent;"
                               "border: 0px;");

    buttonPhotos->setIconSize(QSize(15,15));
    buttonVideos->setIconSize(QSize(15,15));
    buttonAudios->setIconSize(QSize(15,15));
    buttonDocuments->setIconSize(QSize(15,15));

    buttonPhotos->setCursor(Qt::PointingHandCursor);
    buttonVideos->setCursor(Qt::PointingHandCursor);
    buttonAudios->setCursor(Qt::PointingHandCursor);
    buttonDocuments->setCursor(Qt::PointingHandCursor);

    affixLayout->setMargin(0);
    affixLayout->setSpacing(8);

    affixLayout->addWidget(buttonDocuments, 1, Qt::AlignVCenter);
    affixLayout->addWidget(buttonVideos, 1, Qt::AlignVCenter);
    affixLayout->addWidget(buttonAudios, 1, Qt::AlignVCenter);
    affixLayout->addWidget(buttonPhotos, 1, Qt::AlignVCenter);

    affixWidgetContainer->installEventFilter(this);
    buttonPhotos->installEventFilter(this);
    buttonVideos->installEventFilter(this);
    buttonAudios->installEventFilter(this);
    buttonDocuments->installEventFilter(this);
    buttonAffix->installEventFilter(this);

    connect(buttonPhotos, SIGNAL(released()), SLOT(selectImage()));
    connect(buttonAudios, SIGNAL(released()), SLOT(selectSong()));
}

QPushButton *AffixContainer::getButtonAffix(){
    return buttonAffix;
}

QPushButton *AffixContainer::getAffixWidgetContaiter() const{
    return affixWidgetContainer;
}

bool AffixContainer::eventFilter(QObject *target, QEvent *event){
    if((target == buttonAffix || target == affixWidgetContainer) && buttonAffix->isEnabled()){
        if (event->type() == QEvent::HoverEnter){
            buttonAffix->setIcon(QIcon(":/images/affix30gray.png"));
            QPropertyAnimation *animation = new QPropertyAnimation(affixWidgetContainer, "pos");
            animation->setEndValue(QPoint(30, 6));
            animation->setDuration(200);
            animation->start(QAbstractAnimation::DeleteWhenStopped);
        }
        else if (event->type() == QEvent::HoverLeave){
            buttonAffix->setIcon(QIcon(":/images/affix30.png"));
            QPropertyAnimation *animation = new QPropertyAnimation(affixWidgetContainer, "pos");
            animation->setEndValue(QPoint(150, 6));
            animation->setDuration(200);
            animation->start(QAbstractAnimation::DeleteWhenStopped);
        }
    }
    else if(target == buttonPhotos){
        if(event->type() == QEvent::HoverEnter)
            buttonPhotos->setIcon(QIcon(":/images/photos.png"));
        else if(event->type() == QEvent::HoverLeave)
            buttonPhotos->setIcon(QIcon(":/images/photosGray.png"));
    }
    else if(target == buttonAudios){
        if(event->type() == QEvent::HoverEnter)
            buttonAudios->setIcon(QIcon(":/images/audios.png"));
        else if(event->type() == QEvent::HoverLeave)
            buttonAudios->setIcon(QIcon(":/images/audiosGray.png"));
    }
    else if(target == buttonVideos){
        if(event->type() == QEvent::HoverEnter)
            buttonVideos->setIcon(QIcon(":/images/videos.png"));
        else if(event->type() == QEvent::HoverLeave)
            buttonVideos->setIcon(QIcon(":/images/videosGray.png"));
    }
    else if(target == buttonDocuments){
        if(event->type() == QEvent::HoverEnter)
            buttonDocuments->setIcon(QIcon(":/images/documents.png"));
        else if(event->type() == QEvent::HoverLeave)
            buttonDocuments->setIcon(QIcon(":/images/documentsGray.png"));
    }

    return QWidget::eventFilter(target, event);
}

void AffixContainer::selectImage(){
    static QString lastPath = QDir::homePath();
    QString filePath = QFileDialog::getOpenFileName(this, QObject::tr("Choose an image"), lastPath, QObject::tr("Image file (*.png *.jpg *.jpeg *.jpe *.bmp);;Все файлы (*.*)"));
    if(filePath != ""){
        attachmentIsComing(QVariant(QPixmap(filePath)), filePath.split('.').back());
        lastPath = filePath;
    }
}

void AffixContainer::selectSong(){
    static QString lastPath = QDir::homePath();
    QString filePath = QFileDialog::getOpenFileName(this, QObject::tr("Choose an song"), lastPath, QObject::tr("Image file (*.mp3);;Все файлы (*.*)"));
    if(filePath != ""){
        QFile file(filePath);
        file.open(QIODevice::ReadOnly);

        attachmentIsComing(QVariant(file.readAll()), filePath);
        file.close();
        lastPath = filePath;
    }
}
