#ifndef GLOBALCHAT_H
#define GLOBALCHAT_H

#include <QWidget>
#include <QGridLayout>
#include <QListWidget>
#include "UI/Widgets/wraplabel.h"
#include "UI/Widgets/sendwidget.h"
#include "UI/Widgets/affiximagewidget.h"
#include "UI/Widgets/imageview.h"
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

private slots:
    void printMessages(QString, QString, int);
    void selectGlobalItem(QListWidgetItem*);
    void sendMessage(QString);
    void clearAll(bool);
};

#endif // GLOBALCHAT_H
