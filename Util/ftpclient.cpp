#include "ftpclient.h"

FTPClient::FTPClient(QObject *parent) : QObject(parent){
    socket = new QTcpSocket(this);

    //host.setAddress(HOST_IP);
    socket->connectToHost(QHostAddress::LocalHost, FTP_PORT);

    connect(socket, SIGNAL(readyRead()), SLOT(controller()));
}

FTPClient &FTPClient::getInstance(){
    static FTPClient instance;
    return instance;
}

void FTPClient::send(QJsonObject request){
    request.insert("Nickname", nickname);
    request.insert("Access token", accessToken);

    socket->write(QJsonDocument(request).toJson());
}

void FTPClient::post(QByteArray attachment){
    qDebug() << "Send attachment";
    socket->write(attachment);
}

void FTPClient::setUser(QString nickname, QString accessToken, QString refreshToken){
    this->nickname = nickname;
    this->accessToken = accessToken;
    this->refreshToken = refreshToken;
}

void FTPClient::controller(){
    qDebug() << "Sos";
    QByteArray receivedObject = socket->readAll();

    QJsonParseError error;

    QJsonObject response = QJsonDocument::fromJson(receivedObject, &error).object();

    if(error.error == QJsonParseError::NoError){
        if(response.value("Target").toString() == "Post"){
            if(response.value("Value").toString() == "Deny")
                emit loadAttachmentDeny();
            else if(response.value("Value").toString() == "Allow")
                emit loadAttachmentAllow();
        }
        else if(response.value("Target").toString() == "Loading"){
            if(response.value("Value").toInt() == 100)
                emit postIsFinished(response.value("Reference").toString());
        }
        else if(response.value("Target").toString() == "Get"){
            qDebug() << "Getttt" << response.value("SizeOfAttachment").toInt();
            emit sizeWasGotten(response.value("SizeOfAttachment").toInt());
        }
    }
    else{
        qDebug() << "Getting";
        emit getting(receivedObject);
    }
}
