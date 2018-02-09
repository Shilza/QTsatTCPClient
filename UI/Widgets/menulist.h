#ifndef MENULIST_H
#define MENULIST_H

#include <QWidget>
#include <QVBoxLayout>
#include <QPushButton>
#include <QPropertyAnimation>
#include "Ui/Widgets/accountwidget.h"

class MenuList : public QWidget
{
    Q_OBJECT
public:
    explicit MenuList(int height, QWidget *parent = nullptr);
    QWidget* getWidget();
    const QPushButton *getButtonBansHistory() const;
    const QPushButton* getGlobalChatButton() const;

private:
    QWidget *widget;
    QVBoxLayout *menuListLayout;

    QPushButton *buttonGlobalChat;
    QPushButton *buttonUserPage;
    QPushButton *buttonPrivateMessages;
    QPushButton *buttonFriends;
    QPushButton *buttonBansHistory;
    QPushButton *buttonSettings;
    AccountWidget *accountWidget;
    QPushButton *temp;
};

#endif // MENULIST_H
