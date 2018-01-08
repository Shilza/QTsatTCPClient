#include "menulist.h"

MenuList::MenuList(QWidget *parent) : QWidget(parent){
    menuListLayout = new QVBoxLayout(this);
    setLayout(menuListLayout);

    buttonUserPage = new QPushButton(this);
    buttonPrivateMessages = new QPushButton(this);
    buttonFriends = new QPushButton(this);
    buttonPreSettings = new QPushButton(this);

    buttonPreSettings->setFixedHeight(15);

    buttonUserPage->setFixedSize(50, 50);
    buttonUserPage->setStyleSheet("background: black;"
                                  "border-radius: 25px;");

    QString buttonDefaultStyle = "QPushButton{"
                                 "background: transparent;"
                                 "border: 0px;"
                                 "}"
                                 "QPushButton:hover{"
                                 "background: #D3E9E9;"
                                 "}";

    buttonPrivateMessages->setFixedSize(120, 30);
    buttonPrivateMessages->setStyleSheet(buttonDefaultStyle);
    buttonPrivateMessages->setText("Messages");

    buttonFriends->setFixedSize(120, 30);
    buttonFriends->setStyleSheet(buttonDefaultStyle);
    buttonFriends->setText("Friends");

    menuListLayout->setSpacing(0);
    menuListLayout->setContentsMargins(0, 4, 0, 3);
    menuListLayout->addWidget(buttonUserPage, 0, Qt::AlignTop | Qt::AlignCenter);
    menuListLayout->addWidget(buttonFriends, 0, Qt::AlignTop);
    menuListLayout->addWidget(buttonPrivateMessages, 0, Qt::AlignTop);
    menuListLayout->addWidget(new QWidget(this), 6);
    menuListLayout->addWidget(buttonPreSettings, 1);

    preSettings = new PreSettings(this);
    preSettings->setStyleSheet("background: black;");
    preSettings->move(0, 0);
}
