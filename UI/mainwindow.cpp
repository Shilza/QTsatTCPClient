#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "Config/def.h"
#include <QDateTime>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    resize(MAINWINDOW_WIDTH, MAINWINDOW_HEIGHT);

    mainWidget = new QWidget(this);
    mainLayout = new QHBoxLayout(mainWidget);

    stackOfWidgets = new QStackedWidget(mainWidget);

    globalChatWidget = new QWidget(stackOfWidgets);
    globalChatLayout = new QGridLayout(globalChatWidget);

    menuListWidget = new MenuList(height() - contentsMargins().top() - contentsMargins().bottom() - 2, mainWidget);

    listOfGlobalMessages = new QListWidget(globalChatWidget);

    affixImageWidget = new AffixImageWidget(globalChatWidget);

    sendWidget = new SendWidget(globalChatWidget);

    imageView = new ImageView(this);

    bansHistory = new BansHistory(stackOfWidgets);

    setCentralWidget(mainWidget);

    mainWidget->setLayout(mainLayout);
    mainLayout->setMargin(2);
    mainLayout->setSpacing(0);
    mainLayout->addWidget(stackOfWidgets, 6);
    mainLayout->addWidget(menuListWidget->getWidget(), 1, Qt::AlignTop);

    listOfGlobalMessages->setMinimumSize(300, 250);
    listOfGlobalMessages->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
    listOfGlobalMessages->setVerticalScrollMode(QAbstractItemView::ScrollPerPixel);
    listOfGlobalMessages->setStyleSheet("border-color: gray;");

    listOfGlobalMessages->verticalScrollBar()->setStyleSheet(defaultScrollBarStyle);

    globalChatWidget->setFixedSize(536, 440);
    globalChatWidget->setLayout(globalChatLayout);
    globalChatLayout->setSpacing(0);
    globalChatLayout->setMargin(3);

    globalChatLayout->addWidget(listOfGlobalMessages, 0, 0, 8, 9);
    globalChatLayout->addWidget(affixImageWidget->getSendedImage(), 6,0,2,9, Qt::AlignLeft | Qt::AlignBottom);
    globalChatLayout->addWidget(sendWidget->getMainWidget(), 8, 0, 2, 9);

    stackOfWidgets->addWidget(globalChatWidget);
    stackOfWidgets->addWidget(bansHistory->getList());
    stackOfWidgets->setCurrentWidget(globalChatWidget);

    //connect(sendWidget, SIGNAL(messageSended()), this, SLOT(printMessages()));
    connect(sendWidget, SIGNAL(messageSended(QString)), this, SLOT(sendMessage(QString)));
    connect(sendWidget, SIGNAL(imageReceived(QPixmap)), affixImageWidget, SLOT(receivedImageTreatment(QPixmap)));
    connect(affixImageWidget, SIGNAL(originalSizeReleased(QPixmap)), imageView, SLOT(setPicture(QPixmap)));
    connect(affixImageWidget, SIGNAL(detachmentImage()), sendWidget, SLOT(decrementing()));

    connect(&(TCPClient::getInstance()), SIGNAL(messageReceived(QString,QString, int)), SLOT(printMessages(QString, QString, int)));
    connect(&(TCPClient::getInstance()), SIGNAL(exit()), listOfGlobalMessages, SLOT(clear()));

    connect(menuListWidget->getPreSettings(), SIGNAL(showBansHistory()), SLOT(showBansHistory()));
    connect(menuListWidget->getGlobalChatButton(), SIGNAL(released()), SLOT(goToGlobalChat()));
}

void MainWindow::start(uint time){
    if(time)
        sendWidget->ban(time);

    show();
}

void MainWindow::sendMessage(QString message){
    if(message == "")
        return;

    QJsonObject request;

    request.insert("Target", "GMessage");
    request.insert("Message", message);
    TCPClient::getInstance().send(QJsonDocument(request).toJson());
}

void MainWindow::printMessages(QString nickname, QString message, int time){
    QWidget *widget = new QWidget(listOfGlobalMessages);
    QGridLayout *layout = new QGridLayout(widget);
    layout->setContentsMargins(2,5,5,5);
    layout->setSpacing(0);
    layout->setHorizontalSpacing(5);
    layout->setVerticalSpacing(5);
    widget->setLayout(layout);

    QLabel *labelNickname = new QLabel(nickname, widget);
    QLabel *timeOfMessage = new QLabel(QDateTime::fromTime_t(time).time().toString(), widget);
    WrapLabel *textOfMessage = new WrapLabel(widget);
    QLabel *button = new QLabel(widget);

    button->setStyleSheet("background: black;");
    button->setFixedSize(30,30);

    labelNickname->setFixedHeight(10);
    timeOfMessage->setFixedHeight(10);

    textOfMessage->setFixedWidth(450);
    textOfMessage->setWordWrap(true);
    textOfMessage->setStyleSheet("border: 0px;"
                                 "background:transparent;");
    textOfMessage->setTextInteractionFlags(textOfMessage->textInteractionFlags() | Qt::TextSelectableByMouse);
    textOfMessage->wrapText(message);

    layout->addWidget(labelNickname, 0, 1, 1, 1);
    layout->addWidget(timeOfMessage, 0, 7, 1, 1, Qt::AlignRight);
    layout->addWidget(textOfMessage, 1, 1, 2, 7, Qt::AlignLeft | Qt::AlignTop);

    QWidgetItem *widgetItem = new QWidgetItem(button);
    widgetItem->setGeometry(QRect(0,0,30,30));
    layout->addItem(widgetItem, 0,0,3,1, Qt::AlignTop);

    QListWidgetItem* item = new QListWidgetItem(listOfGlobalMessages);
    item->setSizeHint(QSize(widget->width(), layout->sizeHint().height()));
    listOfGlobalMessages->setItemWidget(item, widget);
}

void MainWindow::showBansHistory(){
    stackOfWidgets->setCurrentWidget(bansHistory->getList());
    bansHistory->start();
}

void MainWindow::goToGlobalChat(){
    stackOfWidgets->setCurrentWidget(globalChatWidget);
    QJsonObject request;
    request.insert("Target", "Location");
    request.insert("Value", "Global chat");
    TCPClient::getInstance().send(QJsonDocument(request).toJson());
}

MainWindow::~MainWindow(){
    delete ui;

    delete imageView;
    delete stackOfWidgets;
    delete mainWidget;
    delete mainLayout;
    delete menuListWidget;

    delete sendWidget;
    delete affixImageWidget;

    delete listOfGlobalMessages;
    delete globalChatWidget;
    delete globalChatLayout;
    delete listOfGlobalMessages;
}

//The purpose of this slot is to select a random line from our list of fortunes, encode it into a QByteArray using QDataStream, and then write it to the connecting socket. This is a common way to transfer binary data using QTcpSocket. First we create a QByteArray and a QDataStream object, passing the bytearray to QDataStream's constructor. We then explicitly set the protocol version of QDataStream to QDataStream::Qt_4_0 to ensure that we can communicate with clients from future versions of Qt (see QDataStream::setVersion()). We continue by streaming in a random fortune.
