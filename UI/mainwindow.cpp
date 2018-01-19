#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    resize(MAINWINDOW_WIDTH, MAINWINDOW_HEIGHT);


    mainWidget = new QWidget(this);
    mainLayout = new QHBoxLayout(mainWidget);

    stackOfWidgets = new QStackedWidget(mainWidget);

    menuListWidget = new MenuList(height() - contentsMargins().top() - contentsMargins().bottom() - 2, mainWidget);

    globalChat = new GlobalChat(stackOfWidgets);

    bansHistory = new BansHistory(stackOfWidgets);

    ImageView::getInstance().create(this);

    setCentralWidget(mainWidget);

    mainWidget->setLayout(mainLayout);
    mainLayout->setMargin(2);
    mainLayout->setSpacing(0);
    mainLayout->addWidget(stackOfWidgets, 6);
    mainLayout->addWidget(menuListWidget->getWidget(), 1, Qt::AlignTop);

    stackOfWidgets->addWidget(globalChat->getWidget());
    stackOfWidgets->addWidget(bansHistory->getList());
    stackOfWidgets->setCurrentWidget(globalChat->getWidget());

    connect(menuListWidget->getPreSettings(), SIGNAL(showBansHistory()), SLOT(showBansHistory()));
    connect(menuListWidget->getGlobalChatButton(), SIGNAL(released()), SLOT(goToGlobalChat()));
    connect(&(TCPClient::getInstance()), SIGNAL(exit(bool)), SLOT(exit(bool)));
}

void MainWindow::start(uint time){
    if(time)
        globalChat->getSendWidget()->ban(time);

    show();
}

void MainWindow::showBansHistory(){
    stackOfWidgets->setCurrentWidget(bansHistory->getList());
    bansHistory->start();
}

void MainWindow::goToGlobalChat(){
    stackOfWidgets->setCurrentWidget(globalChat->getWidget());
    QJsonObject request;
    request.insert("Target", "Location");
    request.insert("Value", "Global chat");
    TCPClient::getInstance().send(QJsonDocument(request).toJson());
}

void MainWindow::exit(bool isExit){
    close();
    if(isExit)
        stackOfWidgets->setCurrentWidget(globalChat->getWidget());
}

MainWindow::~MainWindow(){
    delete ui;

    delete stackOfWidgets;
    delete mainWidget;
    delete mainLayout;
    delete menuListWidget;
}

//The purpose of this slot is to select a random line from our list of fortunes, encode it into a QByteArray using QDataStream, and then write it to the connecting socket. This is a common way to transfer binary data using QTcpSocket. First we create a QByteArray and a QDataStream object, passing the bytearray to QDataStream's constructor. We then explicitly set the protocol version of QDataStream to QDataStream::Qt_4_0 to ensure that we can communicate with clients from future versions of Qt (see QDataStream::setVersion()). We continue by streaming in a random fortune.
