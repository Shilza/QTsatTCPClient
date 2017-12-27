#include "tcpclient.h"

TCPClient::TCPClient(QTcpSocket *socket, QObject *parent) : QObject(parent){

    this->socket = socket;

    connect(this->socket, SIGNAL(readyRead()), this, SLOT(reading()));
}

void TCPClient::sendMessage(QString msg){
    QJsonObject request;

    request.insert("Target", "GMessage");
    request.insert("Message", msg);

    socket->write(QJsonDocument(request).toJson());
}

void TCPClient::reading(){
    QByteArray receivedObject = socket->readAll();
    QJsonParseError error;

    QJsonObject response = QJsonDocument::fromJson(receivedObject, &error).object();

    if(error.error == QJsonParseError::NoError){
        if(response.value("Target")=="Message delivery"){
            qDebug() << "sdf";
        }
    }

    /*buffer.resize(socket->pendingDatagramSize());
    socket->readDatagram(buffer.data(), buffer.size());

    QList<QByteArray> tempList = buffer.split('|');
    nickname = tempList.at(0);

    tempList.pop_front();
    buffer.clear();

    for(int i=0; i<tempList.size(); i++)
        buffer.push_back(tempList.at(i));

    emit updating();*/
}

