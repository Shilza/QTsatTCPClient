#include "menulist.h"
#include <QDebug>

MenuList::MenuList(int height, QWidget *parent) : QWidget(parent){
    close();
    widget = new QWidget(this);
    menuListLayout = new QVBoxLayout(widget);
    widget->setLayout(menuListLayout);
    widget->setFixedHeight(height);

    buttonGlobalChat = new QPushButton(widget);
    buttonUserPage = new QPushButton(widget);
    buttonPrivateMessages = new QPushButton(widget);
    buttonFriends = new QPushButton(widget);

    menuListLayout->setSpacing(0);
    menuListLayout->setContentsMargins(0, 4, 0, 3);
    menuListLayout->addWidget(buttonUserPage, 0, Qt::AlignTop | Qt::AlignCenter);
    menuListLayout->addWidget(buttonGlobalChat, 0, Qt::AlignTop);
    menuListLayout->addWidget(buttonFriends, 0, Qt::AlignTop);
    menuListLayout->addWidget(buttonPrivateMessages, 0, Qt::AlignTop);
    menuListLayout->addWidget(new QWidget(widget), 6);

    preSettings = new PreSettings(widget);
    buttonPreSettings = new QPushButton(widget);

    menuListLayout->addWidget(buttonPreSettings, 1);

    buttonPreSettings->setFixedSize(120, 15);

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

    buttonGlobalChat->setFixedSize(120, 30);
    buttonGlobalChat->setStyleSheet(buttonDefaultStyle);
    buttonGlobalChat->setText("Global chat");

    preSettings->move(1, widget->height());

    connect(buttonPreSettings, SIGNAL(released()), SLOT(preSettingsMove()));
    connect(&(TCPClient::getInstance()), SIGNAL(exit()), SLOT(preSettingsMove()));
}

QWidget* MenuList::getWidget(){
    return widget;
}

PreSettings* MenuList::getPreSettings() const{
    return preSettings;
}

QPushButton* MenuList::getGlobalChatButton() const{
    return buttonGlobalChat;
}

void MenuList::preSettingsMove(){
    static bool isShown = false;
    QPropertyAnimation *animation = new QPropertyAnimation(preSettings, "pos");
    animation->setEndValue(QPoint(1, isShown ? widget->height() : widget->height() - buttonPreSettings->height() - preSettings->getWidget()->height() - 5));
    animation->setDuration(300);
    animation->start(QAbstractAnimation::DeleteWhenStopped);
    isShown = !isShown;
}
