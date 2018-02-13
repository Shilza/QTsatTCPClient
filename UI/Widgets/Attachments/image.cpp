#include "image.h"
#include <QDebug>

Image::Image(QString extension, QWidget *parent) : Attachment(parent){
    this->extension = extension;
    mainFrame->setFixedSize(100, 100);
    mainFrame->setIconSize(QSize(mainFrame->width()-2, mainFrame->height()-2));
    mainFrame->setStyleSheet("background: transparent;"
                             "border: 1px solid black;"
                             "border-radius: 4px;");
}

void Image::fill(QByteArray data){
    static QByteArray fullData;
    fullData.append(data);
    qDebug() << "FullData: " << fullData.size() << "SOA: " << sizeOfAttachment;
    if(fullData.size() >= sizeOfAttachment){
        QFile file("/Sas.jpg");
        file.open(QIODevice::WriteOnly);
        file.write(fullData);
        image.loadFromData(fullData, extension.toStdString().c_str());
        mainFrame->setIcon(QIcon(image));
        fullData = 0;
        disconnect(&(TCPClient::getInstance()), SIGNAL(getting(QByteArray)), this, SLOT(fill(QByteArray)));
    }
}

void Image::open(){

}
