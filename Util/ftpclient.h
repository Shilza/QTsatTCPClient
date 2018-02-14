#ifndef FTPCLIENT_H
#define FTPCLIENT_H
#include <QTcpSocket>
#include <QHostAddress>
#include <QJsonObject>
#include <QJsonDocument>
#include <QJsonParseError>
#include "Config/def.h"

class FTPClient : public QObject
{
    Q_OBJECT

public:
    static FTPClient& getInstance();
    void send(QJsonObject request);
    void post(QByteArray attachment);
    void setUser(QString nickname, QString accessToken, QString refreshToken);
    QString getNickname() const;

    FTPClient(const FTPClient &) = delete;
    FTPClient& operator= (const FTPClient &) = delete;

private:
    QTcpSocket *socket;
    QHostAddress host;

    FTPClient(QObject *parent = 0);

    QString nickname;
    QString accessToken;
    QString refreshToken;

signals:
    void loadAttachmentDeny();
    void loadAttachmentAllow();
    void postIsFinished(QString reference);
    void getting(QByteArray);
    void sizeWasGotten(int);

private slots:
    void controller();
};

#endif // FTPCLIENT_H
