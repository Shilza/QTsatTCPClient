#include "attachment.h"

Attachment::Attachment(QWidget *parent) : QWidget(parent){
    mainFrame = new QPushButton;
    mainFrame->setCursor(Qt::PointingHandCursor);
    connect(mainFrame, SIGNAL(released()), SLOT(open()));
    connect(&(FTPClient::getInstance()), SIGNAL(getting(QByteArray)), SLOT(fill(QByteArray)));
    connect(&(FTPClient::getInstance()), SIGNAL(sizeWasGotten(int)), SLOT(setAttachmentSize(int)));
}

QPushButton *Attachment::getMainFrame() const{
    return mainFrame;
}

Attachment::~Attachment(){
    delete mainFrame;
    delete mainLayout;
}

void Attachment::setAttachmentSize(int sizeOfAttachment){
    qDebug() << "sizeOfAaaa" << sizeOfAttachment;
    this->sizeOfAttachment = sizeOfAttachment;
    disconnect(&(FTPClient::getInstance()), SIGNAL(sizeWasGotten(int)), this, SLOT(setAttachmentSize(int)));
}
