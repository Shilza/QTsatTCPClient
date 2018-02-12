#ifndef ATTACHMENT_H
#define ATTACHMENT_H

#include <QObject>
#include <QPushButton>
#include <QLayout>
#include "Util/tcpclient.h"

class Attachment : public QWidget
{
    Q_OBJECT
public:
    explicit Attachment(QWidget *parent = nullptr);
    virtual ~Attachment();

protected:
    QPushButton *mainFrame;
    QLayout *mainLayout;

protected slots:
    virtual void fill(QByteArray data) = 0;
    virtual void open() = 0;
};

#endif // ATTACHMENT_H
