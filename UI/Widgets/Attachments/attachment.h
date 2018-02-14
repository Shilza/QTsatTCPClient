#ifndef ATTACHMENT_H
#define ATTACHMENT_H

#include <QObject>
#include <QPushButton>
#include <QLayout>
#include "Util/ftpclient.h"

class Attachment : public QWidget
{
    Q_OBJECT
public:
    explicit Attachment(QWidget *parent = nullptr);
    QPushButton *getMainFrame() const;
    virtual ~Attachment();

protected:
    QPushButton *mainFrame;
    QLayout *mainLayout;
    int sizeOfAttachment = 0;

protected slots:
    virtual void fill(QByteArray data) = 0;
    virtual void open() = 0;
    void setAttachmentSize(int sizeOfAttachment);
};

#endif // ATTACHMENT_H
