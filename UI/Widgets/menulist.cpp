#include "menulist.h"

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
    buttonBansHistory = new QPushButton(buttonGlobalChat);
    buttonSettings = new QPushButton(widget);
    accountWidget = new AccountWidget(widget, buttonUserPage);
    temp = new QPushButton(widget);

    temp->setMaximumSize(1000, 1000);
    temp->setStyleSheet("background: transparent;");

    menuListLayout->setSpacing(0);
    menuListLayout->setContentsMargins(0, 4, 0, 3);
    menuListLayout->addWidget(buttonUserPage, 0, Qt::AlignTop | Qt::AlignCenter);
    menuListLayout->addWidget(buttonGlobalChat, 0, Qt::AlignTop);
    menuListLayout->addWidget(buttonFriends, 0, Qt::AlignTop);
    menuListLayout->addWidget(buttonPrivateMessages, 0, Qt::AlignTop);
    menuListLayout->addWidget(buttonSettings, 0, Qt::AlignTop);
    menuListLayout->addWidget(temp, 6);

    buttonUserPage->setFixedSize(50, 50);
    buttonUserPage->setStyleSheet("background: black;"
                                  "border-radius: 25px;");
    buttonUserPage->setCursor(Qt::PointingHandCursor);
    buttonUserPage->installEventFilter(accountWidget);

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

    buttonBansHistory->setGeometry(12, 10, 12, 12);
    buttonBansHistory->setStyleSheet("QPushButton{"
                                     "background: transparent;"
                                     "border: 0px;"
                                     "}"
                                     "QToolTip{"
                                     "color: black;"
                                     "}");
    buttonBansHistory->setIcon(QIcon(":/images/list.png"));
    buttonBansHistory->setIconSize(buttonBansHistory->size());
    buttonBansHistory->setToolTip("Bans history");

    buttonSettings->setFixedSize(120, 30);
    buttonSettings->setStyleSheet(buttonDefaultStyle);
    buttonSettings->setText("Settings");

    connect(buttonUserPage, SIGNAL(released()), accountWidget, SLOT(widgetShow()));
}

QWidget* MenuList::getWidget(){
    return widget;
}

const QPushButton *MenuList::getButtonBansHistory() const{
    return buttonBansHistory;
}

const QPushButton *MenuList::getGlobalChatButton() const{
    return buttonGlobalChat;
}
