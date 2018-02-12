#ifndef ATTACHMENT_H
#define ATTACHMENT_H

#include <QObject>

class Attachment : public QObject
{
    Q_OBJECT
public:
    explicit Attachment(QObject *parent = nullptr);
private:
signals:

public slots:
};

#endif // ATTACHMENT_H
