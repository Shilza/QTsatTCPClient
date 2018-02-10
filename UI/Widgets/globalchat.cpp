#include "globalchat.h"

GlobalChat::GlobalChat(QWidget *parent) : QWidget(parent){
    close();
    globalChatWidget = new QWidget(parent);
    globalChatLayout = new QGridLayout(globalChatWidget);
    listOfGlobalMessages = new QListWidget(globalChatWidget);

    affixImageWidget = new AffixImageWidget(globalChatWidget);

    sendWidget = new SendWidget(globalChatWidget);

    listOfGlobalMessages->setMinimumSize(300, 250);
    listOfGlobalMessages->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
    listOfGlobalMessages->setVerticalScrollMode(QAbstractItemView::ScrollPerPixel);
    listOfGlobalMessages->setStyleSheet("QListWidget{"
                                        "border-color: gray;"
                                        "}"
                                        "QListWidget::item:hover{"
                                        "background: rgba(0, 0, 0, 15);"
                                        "}"
                                        "QListWidget::item:selected{"
                                        "background: rgba(0, 0, 0, 30);"
                                        "}");

    listOfGlobalMessages->verticalScrollBar()->setStyleSheet(defaultScrollBarStyle);

    globalChatWidget->setFixedSize(536, 440);
    globalChatWidget->setLayout(globalChatLayout);
    globalChatLayout->setSpacing(0);
    globalChatLayout->setMargin(3);

    globalChatLayout->addWidget(listOfGlobalMessages, 0, 0, 8, 9);
    globalChatLayout->addWidget(affixImageWidget->getSendedImage(), 6,0,2,9, Qt::AlignLeft | Qt::AlignBottom);
    globalChatLayout->addWidget(sendWidget->getMainWidget(), 8, 0, 2, 9);

    connect(sendWidget, SIGNAL(messageSended(QString)), this, SLOT(sendMessage(QString)));
    connect(sendWidget, SIGNAL(imageReceived(QPixmap, QString)), affixImageWidget, SLOT(receivedImageTreatment(QPixmap, QString)));
    connect(affixImageWidget, SIGNAL(detachmentImage()), sendWidget, SLOT(decrementing()));

    connect(&(TCPClient::getInstance()), SIGNAL(messageReceived(QString,QString, int)), SLOT(printMessages(QString, QString, int)));
    connect(&(TCPClient::getInstance()), SIGNAL(exit(bool)), SLOT(clearAll(bool)));
    connect(affixImageWidget, SIGNAL(originalSizeReleased(QPixmap)), &(ImageView::getInstance()), SLOT(setPicture(QPixmap)));
}

QWidget *GlobalChat::getWidget(){
    return globalChatWidget;
}

SendWidget *GlobalChat::getSendWidget(){
    return sendWidget;
}

void GlobalChat::printMessages(QString strNickname, QString message, int time){
    QWidget *widget = new QWidget(listOfGlobalMessages);
    QGridLayout *layout = new QGridLayout(widget);
    layout->setContentsMargins(2,5,5,5);
    layout->setSpacing(0);
    layout->setHorizontalSpacing(5);
    layout->setVerticalSpacing(5);
    widget->setLayout(layout);

    QLabel *timeOfMessage = new QLabel(QDateTime::fromTime_t(time).time().toString(), widget);
    WrapLabel *textOfMessage = new WrapLabel(widget);
    QLabel *avatar = new QLabel(widget);

    QWidget *nickname = new QWidget(widget);
    QHBoxLayout *nicknameLayout = new QHBoxLayout(nickname);
    ClickableLabel *labelNickname = new ClickableLabel(widget, false);
    QWidget *widgetBicycle = new QWidget(nickname);

    nickname->setLayout(nicknameLayout);
    nicknameLayout->setSpacing(0);
    nicknameLayout->setMargin(0);
    nicknameLayout->addWidget(labelNickname);
    nicknameLayout->addWidget(widgetBicycle);

    timeOfMessage->setStyleSheet("color: #8A8A8A;");

    labelNickname->setText(strNickname);
    labelNickname->setStyleSheet("ClickableLabel{ color: #194A61;}"
                                 "ClickableLabel:hover{ color: #5EBFED;}");
    labelNickname->setCursor(Qt::PointingHandCursor);

    avatar->setStyleSheet("background: black;"
                          "border-radius: 15px;");
    avatar->setFixedSize(30,30);
    avatar->setCursor(Qt::PointingHandCursor);

    labelNickname->setFixedHeight(10);
    timeOfMessage->setFixedHeight(10);

    textOfMessage->setFixedWidth(450);
    textOfMessage->setWordWrap(true);
    textOfMessage->setStyleSheet("border: 0px;"
                                 "background:transparent;");
    textOfMessage->setTextInteractionFlags(textOfMessage->textInteractionFlags() | Qt::TextSelectableByMouse);
    textOfMessage->wrapText(message);

    layout->addWidget(nickname, 0, 1, 1, 1);
    layout->addWidget(timeOfMessage, 0, 7, 1, 1, Qt::AlignRight);
    layout->addWidget(textOfMessage, 1, 1, 2, 7, Qt::AlignLeft | Qt::AlignTop);

    QWidgetItem *widgetItem = new QWidgetItem(avatar);
    widgetItem->setGeometry(QRect(0,0,30,30));
    layout->addItem(widgetItem, 0,0,3,1, Qt::AlignTop);

    QListWidgetItem* item = new QListWidgetItem(listOfGlobalMessages);
    textOfMessage->setItem(item);
    item->setSizeHint(QSize(widget->width(), layout->sizeHint().height()));

    connect(textOfMessage, SIGNAL(select(QListWidgetItem*)), this, SLOT(selectGlobalItem(QListWidgetItem*)));

    listOfGlobalMessages->setItemWidget(item, widget);
}

void GlobalChat::selectGlobalItem(QListWidgetItem *item){
    listOfGlobalMessages->setItemSelected(item, true);
}

void GlobalChat::sendMessage(QString message){
    if(message.simplified() == " " || message.simplified() == "" || message == "")
        return;

    QJsonObject request;

    request.insert("Target", "GMessage");
    request.insert("Message", message);
    TCPClient::getInstance().send(QJsonDocument(request).toJson());
}

void GlobalChat::clearAll(bool){
    listOfGlobalMessages->clear();
    sendWidget->getTextMessage()->clear();
}
