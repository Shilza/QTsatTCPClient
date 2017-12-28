#ifndef UDPCLIENT_H
#define UDPCLIENT_H
#include <QObject>
#include <QTcpSocket>
#include <QHostAddress>
#include <QJsonObject>
#include <QJsonDocument>
#include <QJsonParseError>
#include "Config/def.h"

class TCPClient : public QObject
{
    Q_OBJECT
private:
    QTcpSocket *socket;
    QHostAddress host;

    TCPClient(QObject *parent = 0);

    TCPClient(TCPClient const&) = delete;
    TCPClient& operator= (TCPClient const&) = delete;

public:
    static TCPClient& getInstance();
    void sendMessage(QString msg);
    void send(QByteArray);
    QByteArray buffer;
    QString nickname;

signals:
    void updating();
    void authorization(QString);
    void nicknameExisting(QString);
    void registration(QString);
    void registrationCode(QString);
    void recovery(QString);
    void recoveryCode(QString);
    void recoveryNewPass(QString);

private slots:
    void reading();
};

#endif // UDPCLIENT_H
