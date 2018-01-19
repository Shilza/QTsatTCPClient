#include "tcpclient.h"
#include <QDebug>

TCPClient::TCPClient(QObject *parent) : QObject(parent){

    socket = new QTcpSocket(this);

    host.setAddress(HOST_IP);
    socket->connectToHost(QHostAddress::LocalHost, 40000);

    connect(socket, SIGNAL(readyRead()), this, SLOT(reading()));
}

void TCPClient::tokenRefreshing(){
    QJsonObject request;
    request.insert("Target", "Token refreshing");
    request.insert("Refresh token", refreshToken);

    //DO NOT REPLACE THIS WITH "SEND" FUNCTION
    socket->write(QJsonDocument(request).toJson());
}

void TCPClient::configFileUpdate(QString nickname){
    QJsonObject configJson;
    configJson.insert("Nickname", nickname);
    configJson.insert("Access token", accessToken);
    configJson.insert("Refresh token", refreshToken);

    QFile configFile("sosik.txt");
    configFile.open(QIODevice::WriteOnly);
    configFile.write(QJsonDocument(configJson).toJson());
    configFile.close();
}

TCPClient &TCPClient::getInstance(){
    static TCPClient instance;
    return instance;
}

void TCPClient::send(QByteArray request){
    lastRequest = request;
    socket->write(request);
}

void TCPClient::setTokens(QString accessToken, QString refreshToken){
    this->accessToken = accessToken;
    this->refreshToken = refreshToken;
}

void TCPClient::reading(){
    QByteArray receivedObject = socket->readAll();

    QJsonParseError error;

    QJsonObject response = QJsonDocument::fromJson(receivedObject, &error).object();

    if(error.error == QJsonParseError::NoError){
        if(response.value("Target").toString() == "Authorization"){
            if(response.contains("Access token")){
                accessToken = response.value("Access token").toString();
                refreshToken = response.value("Refresh token").toString();

                configFileUpdate(response.value("Nickname").toString());
            }

            emit authorization(response.value("Value").toString(),
                               response.contains("Ban") ? response.value("Ban").toInt() : 0);
        }
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
        else if(response.value("Target").toString() == "Exit"){
            QFile configFile("sosik.txt");
            if(configFile.exists())
                configFile.remove();
            accessToken = "";
            refreshToken = "";

            emit exit(QJsonDocument::fromJson(lastRequest).object().value("Target").toString() == "Exit");
        }
        else if(response.value("Target").toString() == "Bans history")
            emit bansHistory(response.value("Page").toArray(), response.contains("Value"));
        else if(response.value("Target").toString() == "Token refreshing")
            tokenRefreshing();
        else if(response.value("Target").toString() == "Token refreshed"){
            accessToken = response.value("Access token").toString();
            configFileUpdate(response.value("Nickname").toString());
            send(lastRequest);
        }
    }
}
