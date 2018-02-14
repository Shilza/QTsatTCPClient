#include "image.h"
#include <QDebug>

Image::Image(QString extension, QWidget *parent) : Attachment(parent){
    this->extension = extension;
    mainFrame->setFixedSize(100, 100);
    mainFrame->setIconSize(mainFrame->size());
    mainFrame->setStyleSheet("background: transparent;"
                             "border: 0px;"
                             "boder-radius: 4px;");
    connect(this, SIGNAL(originalSizeReleased(QPixmap)), &(ImageView::getInstance()), SLOT(setPicture(QPixmap)));
}

void Image::fill(QByteArray data){
    static QByteArray fullData;
    fullData.append(data);
    qDebug() << "FullData: " << fullData.size() << "SOA: " << sizeOfAttachment;
    if(fullData.size() >= sizeOfAttachment){

        image.loadFromData(fullData, extension.toStdString().c_str());

        QPixmap mini(image);
        if(mini.height() > mini.width()){
            int leftTop = mini.height()/2-mini.width()/2;

            QRect rect(0, leftTop, mini.width(), mini.width());
            mini = mini.copy(rect);
        }
        else if(mini.height() < mini.width()){
            int leftTop = mini.width()/2-mini.height()/2;

            QRect rect(leftTop, 0, mini.height(), mini.height());
            mini = mini.copy(rect);
        }

        mainFrame->setIcon(QIcon(mini));

        fullData = 0;
        disconnect(&(FTPClient::getInstance()), SIGNAL(getting(QByteArray)), this, SLOT(fill(QByteArray)));
    }
}

void Image::open(){
    emit originalSizeReleased(image);
}
