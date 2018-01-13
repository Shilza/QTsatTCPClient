#include "tcpclient.h"

TCPClient::TCPClient(QObject *parent) : QObject(parent){

    socket = new QTcpSocket(this);

    host.setAddress(HOST_IP);
    socket->connectToHost(QHostAddress::LocalHost, 40000);

    connect(socket, SIGNAL(readyRead()), this, SLOT(reading()));
}

TCPClient &TCPClient::getInstance(){
    static TCPClient instance;
    return instance;
}

void TCPClient::send(QByteArray request){
    socket->write(request);
}

void TCPClient::reading(){
    QByteArray receivedObject = socket->readAll();

    QJsonParseError error;

    QJsonObject response = QJsonDocument::fromJson(receivedObject, &error).object();

    if(error.error == QJsonParseError::NoError){
        if(response.value("Target").toString() == "Authorization")
            emit authorization(response.value("Value").toString(),
                               response.contains("Ban") ? response.value("Ban").toInt() : 0);
        else if(response.value("Target").toString() == "DoesNicknameExist")
            emit nicknameExisting(response.value("Value").toString());
        else if(response.value("Target").toString() == "Registration")
            emit registration(response.value("Value").toString());
        else if(response.value("Target").toString() == "Registration code")
            emit registrationCode(response.value("Value").toString());
        else if(response.value("Target").toString() == "Recovery")
            emit recovery(response.value("Value").toString());
        else if(response.value("Target").toString() == "Recovery code")
            emit recoveryCode(response.value("Value").toString());
        else if(response.value("Target").toString() == "Recovery new pass")
            emit recoveryNewPass(response.value("Value").toString());
        else if(response.value("Target").toString() == "Message status"){
            if(!response.contains("Value"))
                emit messageSended();
            else if(response.value("Value").toString() == "Flood")
                emit flood(response.value("Time").toInt());
            else if(response.value("Value").toString() == "Ban")
                emit banStarted(response.value("Time").toInt());
        }
        else if(response.value("Target").toString() == "Message delivery")
            emit messageReceived(response.value("Nickname").toString(), response.value("Message").toString(), response.value("Time").toInt());
        else if(response.value("Target").toString() == "Ban finished")
            emit banFinished(response.value("Value") == "True");
        else if(response.value("Target").toString() == "Exit")
            emit exit();
        else if(response.value("Target").toString() == "Bans history")
            emit bansHistory(response.value("Page").toArray(), response.contains("Value"));
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
