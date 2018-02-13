#ifndef IMAGE_H
#define IMAGE_H
#include "UI/Widgets/Attachments/attachment.h"

class Image : public Attachment
{
    Q_OBJECT
public:
    Image(QString extension, QWidget *parent = nullptr);
private:
    QPixmap image;
    QString extension;

    void fill(QByteArray data) override;
    void open() override;
};

#endif // IMAGE_H
