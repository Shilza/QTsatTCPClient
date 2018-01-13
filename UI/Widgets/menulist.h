#ifndef MENULIST_H
#define MENULIST_H

#include <QWidget>
#include <QVBoxLayout>
#include <QPushButton>
#include <QPropertyAnimation>
#include "UI/Widgets/presettings.h"

class MenuList : public QWidget
{
    Q_OBJECT
public:
    explicit MenuList(int height, QWidget *parent = nullptr);
    QWidget* getWidget();
    PreSettings* getPreSettings() const;
    QPushButton* getGlobalChatButton() const;

private:
    QWidget *widget;
    QVBoxLayout *menuListLayout;

    QPushButton *buttonGlobalChat;
    QPushButton *buttonUserPage;
    QPushButton *buttonPrivateMessages;
    QPushButton *buttonFriends;
    QPushButton *buttonPreSettings;

    PreSettings *preSettings;

private slots:
    void preSettingsMove();

};

#endif // MENULIST_H
