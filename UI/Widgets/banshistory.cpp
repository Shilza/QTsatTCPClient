#include "banshistory.h"

BansHistory::BansHistory(QWidget *parent) : QWidget(parent){
    listBansHistory = new QListWidget(parent);
    preloader = new QSvgWidget(listBansHistory);

    listBansHistory->setVerticalScrollMode(QAbstractItemView::ScrollPerPixel);
    listBansHistory->verticalScrollBar()->setStyleSheet(defaultScrollBarStyle);

    listBansHistory->setFixedSize(536, 440);

    preloader->load(QString(":images/pre.svg"));
    preloader->setStyleSheet("background: transparent;");
    preloader->resize(40, 40);
    preloader->move((listBansHistory->width() - preloader->width())/2, (listBansHistory->height() - preloader->height())/2);
    preloader->close();

    connect(&(TCPClient::getInstance()), SIGNAL(bansHistory(QJsonArray)), SLOT(showBansHistory(QJsonArray)));
    connect(listBansHistory->verticalScrollBar(), SIGNAL(valueChanged(int)), SLOT(loadNewPage(int)));
}

QListWidget *BansHistory::getList(){
    return listBansHistory;
}

void BansHistory::start(){
    currentLastPage = 1;
    preloader->show();
}

void BansHistory::showBansHistory(QJsonArray bans){
    preloader->close();

    for(int i = 0; i < bans.count(); i++){
        QJsonObject temp = bans.at(i).toObject();

        QWidget *widget = new QWidget(listBansHistory);
        QGridLayout *layout = new QGridLayout(widget);
        layout->setContentsMargins(2,5,5,5);
        layout->setSpacing(0);
        layout->setHorizontalSpacing(5);
        layout->setVerticalSpacing(5);
        widget->setLayout(layout);

        QLabel *labelNickname = new QLabel(temp.value("Nickname").toString(), widget);
        QLabel *cause = new QLabel("For " + temp.value("Cause").toString() + " by " + temp.value("Moderator").toString(), widget);
        QLabel *button = new QLabel(widget);

        QLocale locale = QLocale(QLocale::English);
        QLabel *startTime = new QLabel(locale.toString(QDateTime::fromTime_t(temp.value("StartTime").toInt()), "d MMM yy hh:mm:ss"), widget);
        QLabel *finishTime = new QLabel(locale.toString(QDateTime::fromTime_t(temp.value("FinishTime").toInt()), "d MMM yy hh:mm:ss"), widget);

        button->setStyleSheet("background: black;");
        button->setFixedSize(30,30);

        labelNickname->setFixedHeight(10);
        startTime->setFixedHeight(10);

        cause->setStyleSheet("border: 0px;"
                             "background: transparent;");

        layout->addWidget(labelNickname, 0, 1, 1, 1);
        layout->addWidget(cause, 1, 1, 1, 7, Qt::AlignHCenter | Qt::AlignTop);
        layout->addWidget(startTime, 0, 7, 1, 1, Qt::AlignRight);
        layout->addWidget(finishTime, 1, 7, 1, 1, Qt::AlignRight);


        QWidgetItem *widgetItem = new QWidgetItem(button);
        widgetItem->setGeometry(QRect(0,0,30,30));
        layout->addItem(widgetItem, 0,0,3,1, Qt::AlignTop);

        QListWidgetItem* item = new QListWidgetItem(listBansHistory);
        item->setSizeHint(QSize(widget->width(), layout->sizeHint().height()));
        listBansHistory->setItemWidget(item, widget);
    }
}

void BansHistory::loadNewPage(int value){
    if(value == listBansHistory->verticalScrollBar()->maximum()){
        QJsonObject request;
        request.insert("Target", "Bans history");
        request.insert("Page", currentLastPage++);
        TCPClient::getInstance().send(QJsonDocument(request).toJson());
    }
}
