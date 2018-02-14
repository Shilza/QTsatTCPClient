#include "accountwidget.h"
#include <QDebug>

AccountWidget::AccountWidget(QWidget *parent, QPushButton *buttonUserPagePtr) : QWidget(parent){
    close();

    this->buttonUserPagePtr = buttonUserPagePtr;

    mainWidget = new QWidget(parent);
    mainLayout = new QVBoxLayout(mainWidget);
    buttonUser = new ClickableLabel(mainWidget);
    buttonAccountSettings = new QPushButton("Settings", mainWidget);
    buttonExit = new QPushButton("Log out", mainWidget);

    mainWidget->close();
    mainWidget->setGeometry(10, 62, 100, 75);
    mainWidget->setLayout(mainLayout);
    mainWidget->setStyleSheet("background: white;"
                              "border: 1px solid black;"
                              "border-radius: 4px;");

    buttonUser->setStyleSheet("ClickableLabel{"
                              "border: 0px;"
                              "border-bottom: 1px solid gray;"
                              "font-weight: bold;"
                              "}");
    buttonUser->setFixedHeight(33);
    buttonUser->setAlignment(Qt::AlignCenter);

    buttonAccountSettings->setStyleSheet("QPushButton{"
                                         "border: 0px;"
                                         "border-radius: 0px;"
                                         "}"
                                         "QPushButton:hover{"
                                         "background: #F5F5F4;"
                                         "}"
                                         "QPushButton:focus:pressed{"
                                         "background: #E8E8E3;"
                                         "}");
    buttonAccountSettings->setFixedHeight(20);

    buttonExit->setStyleSheet("QPushButton{"
                              "border: 0px;"
                              "border-radius: 0px;"
                              "border-bottom-left-radius: 4px;"
                              "border-bottom-right-radius: 4px;"
                              "}"
                              "QPushButton:hover{"
                              "background: #F5F5F4;"
                              "}"
                              "QPushButton:focus:pressed{"
                              "background: #E8E8E3;"
                              "}");
    buttonExit->setFixedHeight(20);

    mainLayout->setSpacing(0);
    mainLayout->setMargin(1);
    mainLayout->addWidget(buttonUser);
    mainLayout->addWidget(buttonAccountSettings);
    mainLayout->addWidget(buttonExit);

    mainWidget->installEventFilter(this);

    connect(buttonExit, SIGNAL(released()), SLOT(exit()));
    connect(&(TCPClient::getInstance()), SIGNAL(exit(bool)), SLOT(exit(bool)));
}

const QWidget *AccountWidget::getWidget() const{
    return mainWidget;
}

QPushButton *AccountWidget::getButtonSettings() const{
    return buttonAccountSettings;
}

bool AccountWidget::eventFilter(QObject *watched, QEvent *event){
    if(watched == mainWidget)
        if(event->type() == QEvent::FocusOut && mainWidget->isVisible()){
            mainWidget->close();
            emit lostFocus();
        }

    return QWidget::eventFilter(watched, event);
}

void AccountWidget::widgetShow(){
    if(buttonUser->text() == "")
        buttonUser->setText(TCPClient::getInstance().getNickname());
    mainWidget->setFocus();
    mainWidget->show();
}

void AccountWidget::exit(){
    QJsonObject request;
    request.insert("Target", "Exit");
    TCPClient::getInstance().send(QJsonDocument(request).toJson());
}

void AccountWidget::exit(bool){
    mainWidget->close();
    buttonUser->setText("");
}
