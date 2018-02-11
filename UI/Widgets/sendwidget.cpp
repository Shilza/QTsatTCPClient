#include "sendwidget.h"

SendWidget::SendWidget(QWidget *parent): QWidget(parent){
    close();

    mainWidget = new QWidget(this);
    sendLayout = new QGridLayout(mainWidget);

    textMessage = new GlobalTextEdit(mainWidget);
    affixContainer = new AffixContainer(mainWidget);

    labelBicycle = new QLabel(mainWidget);
    buttonSend = new QPushButton(mainWidget);

    labelFloodError = new ClickableLabel(textMessage, false);
    labelBan = new QLabel(textMessage);

    floodTimer = new FloodTimer(textMessage);

    labelTimerShow = new QLabel(textMessage);
    labelSymbolsCount = new QLabel(textMessage);

    banTimer = new QTimer(this);
    banTimer->setSingleShot(true);

    labelBicycle->setStyleSheet("background: #E5F0F0;"
                                "border: 0px;");

    mainWidget->setLayout(sendLayout);
    mainWidget->setStyleSheet("background: #E5F0F0;"
                              "border: 1px solid gray;"
                              "border-top: 0px;");

    labelTimerShow->setAlignment(Qt::AlignCenter);
    labelTimerShow->setFont(QFont("Times New Roman", 11));
    labelTimerShow->setContentsMargins(0,0,5,2);
    labelTimerShow->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
    labelTimerShow->setStyleSheet("background: transparent;"
                                  "border: 0px;");
    labelTimerShow->close();


    labelSymbolsCount->setContentsMargins(0,0,5,2);
    labelSymbolsCount->setFont(QFont("Times New Roman", 10));
    labelSymbolsCount->setStyleSheet("background: transparent;"
                                     "border: 0px;");
    labelSymbolsCount->close();

    textMessage->setFixedHeight(50);
    textMessage->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
    textMessage->setStyleSheet("border-radius: 8px;"
                               "border: 1px solid gray;"
                               "background-color: white;");
    textMessage->setContentsMargins(2,1,2,1);
    textMessage->verticalScrollBar()->setStyleSheet("QScrollBar:vertical{"
                                                    "background: white;"
                                                    "border-top-right-radius: 1px;"
                                                    "border-bottom-right-radius: 1px;"
                                                    "width: 8px;"
                                                    "margin: 0px;"
                                                    "}"
                                                    "QScrollBar:handle:vertical{"
                                                    "background: gray;"
                                                    "border-radius: 1px;"
                                                    "min-height: 20px;"
                                                    "margin: 0px 2px 0px 2px;"
                                                    "}"
                                                    "QScrollBar:add-line:vertical{"
                                                    "background: transparent;"
                                                    "height: 0px;"
                                                    "subcontrol-position: right;"
                                                    "subcontrol-origin: margin;"
                                                    "}"
                                                    "QScrollBar:sub-line:vertical{"
                                                    "background: transparent;"
                                                    "height: 0px;"
                                                    "subcontrol-position: left;"
                                                    "subcontrol-origin: margin;"
                                                    "}");

    buttonSend->setFixedSize(70, 26);
    buttonSend->setCursor(Qt::PointingHandCursor);
    buttonSend->setText("Send");
    buttonSend->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);

    buttonSend->setStyleSheet("QPushButton{"
                              "background: transparent;"
                              "border: 2px solid black;"
                              "border-radius: 10px;"
                              "color: black;}"
                              "QPushButton:hover{"
                              "background: #CBE2E2;"
                              "}"
                              "QPushButton:focus:pressed{"
                              "background: #A4CCCC;"
                              "}");

    sendLayout->setContentsMargins(7,5,7,5);
    sendLayout->setVerticalSpacing(5);
    sendLayout->setHorizontalSpacing(16);

    sendLayout->addWidget(textMessage,       0, 0, 1, 9);
    sendLayout->addWidget(labelFloodError,   0, 0, 1, 8);
    sendLayout->addWidget(labelTimerShow,    0, 8, 1, 1);
    sendLayout->addWidget(labelSymbolsCount, 0, 0, 1, 9, Qt::AlignRight | Qt::AlignBottom);
    sendLayout->addWidget(labelBan,          0, 0, 1, 8);
    sendLayout->addWidget(labelBicycle,      1, 7, -1, -1);
    sendLayout->addWidget(buttonSend,        1, 8, 1, 1);
    sendLayout->addWidget(affixContainer->getButtonAffix(), 1, 7, 1, 1);
    sendLayout->addWidget(affixContainer, 1, 4, -1, -1);

    QFont fontGothic("Century Gothic");
    fontGothic.setBold(true);
    fontGothic.setPointSize(16);
    labelFloodError->setFont(fontGothic);
    labelFloodError->setAlignment(Qt::AlignCenter);
    labelFloodError->setText("Flood");
    labelFloodError->setStyleSheet("color: red;"
                                   "background: transparent;"
                                   "border: 0px;");
    labelFloodError->close();

    fontGothic.setBold(true);
    fontGothic.setPointSize(16);

    labelBan->setFont(fontGothic);
    labelBan->setAlignment(Qt::AlignCenter);
    labelBan->setText("Ban");
    labelBan->setStyleSheet("color: red;"
                            "background: transparent;"
                            "border: 0px;");
    labelBan->close();

    connect(buttonSend, SIGNAL(released()), SLOT(send()));
    connect(textMessage, SIGNAL(enter()), SLOT(send()));
    connect(textMessage, SIGNAL(textChanged()), SLOT(showSymbolsCount()));
    connect(floodTimer, SIGNAL(errorTimeout()), SLOT(floodErrorHide()));
    connect(floodTimer, SIGNAL(showTimeout()), SLOT(updateTime()));
    connect(textMessage, SIGNAL(imageReceived(QVariant, QString)), SLOT(affixReceivedRedirect(QVariant, QString)));
    connect(affixContainer, SIGNAL(pictureIsComing(QVariant,QString)), SLOT(affixReceivedRedirect(QVariant,QString)));
    connect(banTimer, SIGNAL(timeout()), SLOT(banFinished()));

    connect(&(TCPClient::getInstance()), SIGNAL(flood(int)), SLOT(floodReceived(int)));
    connect(&(TCPClient::getInstance()), SIGNAL(messageSended()), SLOT(messageSended()));
    connect(&(TCPClient::getInstance()), SIGNAL(banFinished(bool)), SLOT(banFinishing(bool)));
    connect(&(TCPClient::getInstance()), SIGNAL(banStarted(uint)), SLOT(ban(uint)));
    connect(&(TCPClient::getInstance()), SIGNAL(loadingIsFinished(QString)), SLOT(setReference(QString)));
}

void SendWidget::floodErrorHide(){
    labelFloodError->close();
    labelTimerShow->close();
    textMessage->setEnabled(true);
    buttonSend->setEnabled(true);
    affixContainer->getButtonAffix()->setEnabled(true);
    textMessage->setFocus();
}

void SendWidget::updateTime(){
    int time = floodTimer->remainingTime()/10;

    QString result = QString::number(float(time)/100.0);
    if(time%100 == 0)
        result += ".00";
    else while(time!=0)
        if(time%10 != 0)
            break;
        else{
            result += "0";
            time = time/10;
        }
    labelTimerShow->setText(result);
}

void SendWidget::showSymbolsCount(){
    labelSymbolsCount->setText(QString::number(textMessage->toPlainText().length())+"/"+QString::number(MAX_GLOBAL_MESSAGE_SIZE));
    labelSymbolsCount->show();
}

void SendWidget::send(){
    QString message = textMessage->toPlainText();
    if(message.simplified() == " " || message.simplified() == "" || message == "")
        return;

    QJsonObject request;

    request.insert("Target", "GMessage");
    request.insert("Message", message);

    if(countOfAttachment==1){
        request.insert("Attachment", attachmentReference);
    }

    TCPClient::getInstance().send(QJsonDocument(request).toJson());
}

void SendWidget::affixReceivedRedirect(QVariant affix, QString extension){
    if(countOfAttachment<1){
        int size=0;
        QString typeName = QString(affix.typeName());
        if(typeName == "QPixmap" || typeName == "QImage"){

            QPixmap image = qvariant_cast<QPixmap>(affix);

            if(image.isNull())
                return;

            size = getSize(image, extension);

            /*if(size > MAX_AFFIX_SIZE){
                emit attachmentToLarge();
                return;
            }*/

            emit imageReceived(image, extension);
        }

        QJsonObject request;
        request.insert("Target", "Post");
        request.insert("Extension", extension);
        request.insert("Location", "GlobalChat");
        request.insert("Size", size);
        TCPClient::getInstance().sendToFTP(request);

        countOfAttachment++;
    }
}

void SendWidget::messageSended(){
    textMessage->clear();
    attachmentReference = "";
    countOfAttachment = 0;
}

void SendWidget::floodReceived(int time){
    labelFloodError->show();
    labelTimerShow->show();
    textMessage->setDisabled(true);
    floodTimer->start(time);
}

void SendWidget::banFinished(){
    QJsonObject request;
    request.insert("Target", "Ban finished");
    TCPClient::getInstance().send(QJsonDocument(request).toJson());
}

void SendWidget::banFinishing(bool isFinished){
    banTimer->stop();

    if(isFinished){
        labelBan->close();
        buttonSend->setEnabled(true);
        textMessage->setEnabled(true);
    }
    else
        banTimer->start(300000);
}

void SendWidget::setReference(QString reference){
    attachmentReference = reference;
}

void SendWidget::decrementing(){
    if(countOfAttachment > 0)
        countOfAttachment--;
}

void SendWidget::ban(uint time){
    textMessage->clear();
    QLocale locale = QLocale(QLocale::English);
    banTimer->start((time-QDateTime::currentDateTime().toTime_t())*1000);
    labelBan->setText("Ban until " + locale.toString(QDateTime::fromTime_t(time), "d MMM yy hh:mm:ss"));
    labelBan->show();
    textMessage->setDisabled(true);
    buttonSend->setDisabled(true);
}

QWidget *SendWidget::getMainWidget(){
    return mainWidget;
}

GlobalTextEdit *SendWidget::getTextMessage(){
    return textMessage;
}

SendWidget::~SendWidget(){
    delete affixContainer;
    delete labelBicycle;
    delete textMessage;
    delete buttonSend;
    delete labelFloodError;
    delete labelBan;
    delete labelTimerShow;
    delete labelSymbolsCount;
    delete sendLayout;

    delete floodTimer;
}
