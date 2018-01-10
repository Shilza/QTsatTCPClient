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

private:
    QWidget *widget;
    QVBoxLayout *menuListLayout;

    QPushButton *buttonUserPage;
    QPushButton *buttonPrivateMessages;
    QPushButton *buttonFriends;
    QPushButton *buttonPreSettings;

    PreSettings *preSettings;

signals:

private slots:
    void preSettingsMove();
};

#endif // MENULIST_H
