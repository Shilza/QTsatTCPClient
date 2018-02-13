#include "attachment.h"

Attachment::Attachment(QWidget *parent) : QWidget(parent){
    mainFrame = new QPushButton;
    connect(mainFrame, SIGNAL(released()), SLOT(open()));
    connect(&(TCPClient::getInstance()), SIGNAL(getting(QByteArray)), SLOT(fill(QByteArray)));
    connect(&(TCPClient::getInstance()), SIGNAL(sizeWasGotten(int)), SLOT(setAttachmentSize(int)));
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
    disconnect(&(TCPClient::getInstance()), SIGNAL(sizeWasGotten(int)), this, SLOT(setAttachmentSize(int)));
}
