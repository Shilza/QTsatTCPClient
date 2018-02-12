#include "attachment.h"

Attachment::Attachment(QWidget *parent) : QWidget(parent){
    mainFrame = new QPushButton;
    connect(mainFrame, SIGNAL(released()), SLOT(open()));
    connect(&(TCPClient::getInstance()), SIGNAL(getIsFinished(QByteArray)), SLOT(fill(QByteArray)));
}

Attachment::~Attachment(){
    delete mainFrame;
    delete mainLayout;
}
