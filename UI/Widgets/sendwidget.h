#ifndef SENDWIDGET_H
#define SENDWIDGET_H

#include <QGridLayout>
#include <QLabel>
#include <QPushButton>
#include <QScrollBar>
#include <QFileDialog>
#include <QPropertyAnimation>
#include <QDateTime>
#include <QLocale>
#include <QBuffer>
#include "Util/tcpclient.h"
#include "Util/floodtimer.h"
#include "Util/sizecounting.h"
#include "UI/Widgets/clickablelabel.h"
#include "UI/Widgets/globaltextedit.h"
#include "Config/def.h"

class SendWidget : public QWidget
{
    Q_OBJECT
public:
    explicit SendWidget(QWidget *parent=0);
    QWidget *getMainWidget();
    GlobalTextEdit *getTextMessage();
    ~SendWidget();

private:
    QWidget *mainWidget;
    QPushButton *affixWidgetContainer;
    QWidget *subAffixWidget;
    QHBoxLayout *affixLayout;
    QLabel *labelBicycle;
    QPushButton *buttonAffix;
    QPushButton *buttonSend;
    ClickableLabel *labelFloodError;
    QLabel *labelBan;
    QLabel *labelTimerShow;
    QLabel *labelSymbolsCount;
    QGridLayout *sendLayout;

    GlobalTextEdit *textMessage;

    QPushButton *buttonPhotos;
    QPushButton *buttonVideos;
    QPushButton *buttonAudios;
    QPushButton *buttonDocuments;

    FloodTimer *floodTimer;
    QTimer *banTimer;

    quint8 countOfAttachment=0;
    uint banFinish = 0;

    bool eventFilter(QObject *target, QEvent *event);

signals:
    void messageSended(QString);
    void imageReceived(QPixmap image, QString extension);
    void attachmentToLarge();

private slots:
    void floodErrorHide();
    void updateTime();
    void showSymbolsCount();
    void send();
    void affixReceivedRedirect(QVariant affix, QString extension);
    void selectImage();
    void messageSended();
    void floodReceived(int);
    void banFinished();
    void banFinishing(bool);

public slots:
    void decrementing();
    void ban(uint);
};

#endif // SENDWIDGET_H
