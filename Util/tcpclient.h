#ifndef TCPCLIENT_H
#define TCPCLIENT_H
#include <QObject>
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

    TCPClient(TCPClient const&) = delete;
    TCPClient& operator= (TCPClient const&) = delete;

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
    void sendToFTP(QByteArray attachment);
    void setUser(QString nickname, QString accessToken, QString refreshToken);

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
    void messageReceived(QString, QString, int);
    void flood(int);
    void banFinished(bool);
    void banStarted(uint);
    void exit(bool);
    void bansHistory(QJsonArray, bool);
    void loadAttachmentDeny();
    void loadAttachmentAllow();

private slots:
    void controller();
    void ftpController();
};

#endif // TCPCLIENT_H
