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
    const QPushButton *getGlobalChatButton() const;
    const QPushButton *getButtonAccountSettings() const;

private:
    QWidget *mainWidget;
    QVBoxLayout *menuListLayout;

    QPushButton *buttonGlobalChat;
    QPushButton *buttonUserPage;
    QPushButton *buttonPrivateMessages;
    QPushButton *buttonFriends;
    QPushButton *buttonBansHistory;
    QPushButton *buttonSettings;
    AccountWidget *accountWidget;
    QPushButton *temp;
    QPushButton *widgetOverlappingUserPage;

private slots:
    void overlapping();
    void unoverlapping();
};

#endif // MENULIST_H
