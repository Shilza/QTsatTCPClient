#ifndef UDPCLIENT_H
#define UDPCLIENT_H
#include <QObject>
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
    QTcpSocket *socket;
    QHostAddress host;

    TCPClient(QObject *parent = 0);

    TCPClient(TCPClient const&) = delete;
    TCPClient& operator= (TCPClient const&) = delete;
    QByteArray buffer;
    QString nickname;

public:
    static TCPClient& getInstance();
    void send(QByteArray);

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
    void exit();
    void bansHistory(QJsonArray);

private slots:
    void reading();
};

#endif // UDPCLIENT_H
