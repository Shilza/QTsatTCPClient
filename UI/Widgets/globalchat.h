#ifndef GLOBALCHAT_H
#define GLOBALCHAT_H

#include <QGridLayout>
#include <QListWidget>
#include "UI/Widgets/wraplabel.h"
#include "UI/Widgets/sendwidget.h"
#include "UI/Widgets/AffixImagewidget.h"
#include "UI/Widgets/imageview.h"
#include "UI/Widgets/Attachments/image.h"
#include "UI/Widgets/affixaudiowidget.h"
#include "Config/def.h"
#include "Util/tcpclient.h"

class GlobalChat : public QWidget
{
    Q_OBJECT
public:
    explicit GlobalChat(QWidget *parent = nullptr);
    QWidget* getWidget();
    SendWidget* getSendWidget();

private:
    QWidget *globalChatWidget;
    QGridLayout *globalChatLayout;
    QListWidget *listOfGlobalMessages;
    SendWidget *sendWidget;
    AffixImageWidget *affixImageWidget;
    AffixAudioWidget *affixAudioWidget;

private slots:
    void printMessages(QString, QString, int, QString attachment);
    void selectGlobalItem(QListWidgetItem*);
    void clearAll(bool);
    void setVerticalScrollBarValue(int, int max);
};

#endif // GLOBALCHAT_H
