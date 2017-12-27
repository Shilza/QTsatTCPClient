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

public:
    explicit TCPClient(QTcpSocket *socket, QObject *parent = 0);
    void sendMessage(QString msg);
    QByteArray buffer;
    QString nickname;
signals:
    void updating();
private slots:
    void reading();
};

#endif // UDPCLIENT_H
