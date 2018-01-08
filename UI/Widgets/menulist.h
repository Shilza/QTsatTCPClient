#ifndef MENULIST_H
#define MENULIST_H

#include <QWidget>
#include <QVBoxLayout>
#include <QPushButton>
#include "UI/Widgets/presettings.h"

class MenuList : public QWidget
{
    Q_OBJECT
public:
    explicit MenuList(QWidget *parent = nullptr);

private:
    QVBoxLayout *menuListLayout;

    QPushButton *buttonUserPage;
    QPushButton *buttonPrivateMessages;
    QPushButton *buttonFriends;
    QPushButton *buttonPreSettings;

    PreSettings *preSettings;

signals:

public slots:


};

#endif // MENULIST_H
