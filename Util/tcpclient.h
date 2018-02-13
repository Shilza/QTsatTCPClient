#ifndef TCPCLIENT_H
#define TCPCLIENT_H

#include <QFile>
#include <QTcpSocket>
#include <QHostAddress>
#include <QJsonObject>
#include <QJsonDocument>
#include <QJsonParseError>
#include <QJsonArray>
#include "Config/def.h"

class TCPClient : public QObject
{
    Q_OBJECT
private:
    QTcpSocket *serverSocket;
    QTcpSocket *ftpSocket;
    QHostAddress host;

    TCPClient(QObject *parent = 0);

    QByteArray lastRequest;
    QString nickname;
    QString accessToken;
    QString refreshToken;

    void tokenRefreshing();
    void configFileUpdate();

public:
    static TCPClient& getInstance();
    void send(QByteArray request);
    void sendToFTP(QJsonObject request);
    void postToFTP(QByteArray attachment);
    void getFromFTP(QString attachment);
    void setUser(QString nickname, QString accessToken, QString refreshToken);
    QString getNickname() const;

    TCPClient(const TCPClient &) = delete;
    TCPClient& operator= (const TCPClient &) = delete;

signals:
    void updating();
    void authorization(QString, uint);
    void nicknameExisting(QString);
    void registration(QString);
    void registrationCode(QString);
    void recovery(QString);
    void recoveryCode(QString);
    void recoveryNewPass(QString);
    void messageSended();
    void messageReceived(QString, QString, int, QString);
    void flood(int);
    void banFinished(bool);
    void banStarted(uint);
    void exit(bool);
    void bansHistory(QJsonArray, bool);
    void loadAttachmentDeny();
    void loadAttachmentAllow();
    void postIsFinished(QString reference);
    void getting(QByteArray);
    void sizeWasGotten(int);

private slots:
    void controller();
    void ftpController();
};

#endif // TCPCLIENT_H
