#include "banshistory.h"

BansHistory::BansHistory(QWidget *parent) : QWidget(parent){
    close();
    listBansHistory = new QListWidget(parent);
    preloader = new QSvgWidget(listBansHistory);

    listBansHistory->setVerticalScrollMode(QAbstractItemView::ScrollPerPixel);
    listBansHistory->verticalScrollBar()->setStyleSheet(defaultScrollBarStyle);

    listBansHistory->setFixedSize(536, 440);
    listBansHistory->setSelectionMode(QAbstractItemView::NoSelection);
    listBansHistory->setStyleSheet("QListWidget::item{"
                                   "background: transparent;"
                                   "}"
                                   "QListWidget::item:hover{"
                                   "background: rgba(0, 0, 0, 15);"
                                   "}"
                                   "QListWidget::item:focus:pressed{"
                                   "background: transparent;"
                                   "}");
    preloader->load(QString(":images/pre.svg"));
    preloader->setStyleSheet("background: transparent;");
    preloader->resize(40, 40);
    preloader->move((listBansHistory->width() - preloader->width())/2, (listBansHistory->height() - preloader->height())/2);
    preloader->close();

    connect(&(TCPClient::getInstance()), SIGNAL(bansHistory(QJsonArray, bool)), SLOT(showBansHistory(QJsonArray, bool)));
    connect(listBansHistory->verticalScrollBar(), SIGNAL(valueChanged(int)), SLOT(loadNewPage(int)));
}

QListWidget *BansHistory::getList(){
    return listBansHistory;
}

void BansHistory::start(){
    currentLastPage = 1;
    end = false;
    listBansHistory->clear();
    preloader->show();
}

void BansHistory::showBansHistory(QJsonArray bans, bool isContains){
    preloader->close();
    end = isContains;
    QLocale locale = QLocale(QLocale::English);

    for(int i = bans.count()-1 ; i >= 0; i--){
        QJsonObject temp = bans.at(i).toObject();

        QWidget *widget = new QWidget(listBansHistory);
        QGridLayout *layout = new QGridLayout(widget);
        QWidget *bansBody = new QWidget(widget);
        QHBoxLayout *bansLayout = new QHBoxLayout(bansBody);
        ClickableLabel *labelModerator = new ClickableLabel(bansBody, false);
        QLabel *startTime = new QLabel(locale.toString(QDateTime::fromTime_t(temp.value("StartTime").toInt()), "d MMM yy hh:mm:ss"), widget);
        QLabel *finishTime = new QLabel(locale.toString(QDateTime::fromTime_t(temp.value("FinishTime").toInt()), "d MMM yy hh:mm:ss"), widget);
        QLabel *labelCause = new QLabel("For " + temp.value("Cause").toString() + " by ", bansBody);
        QPushButton *avatar = new QPushButton(widget);
        QWidget *nickname = new QWidget(widget);
        QHBoxLayout *nicknameLayout = new QHBoxLayout(nickname);
        ClickableLabel *labelNickname = new ClickableLabel(nickname, false);
        QWidget *widgetBicycle = new QWidget(nickname);

        layout->setContentsMargins(2,5,5,5);
        layout->setSpacing(0);
        layout->setHorizontalSpacing(5);
        layout->setVerticalSpacing(5);
        widget->setLayout(layout);

        nickname->setLayout(nicknameLayout);
        nicknameLayout->setSpacing(0);
        nicknameLayout->setMargin(0);
        nicknameLayout->addWidget(labelNickname);
        nicknameLayout->addWidget(widgetBicycle);

        labelNickname->setText(temp.value("Nickname").toString());
        labelNickname->setStyleSheet("ClickableLabel:hover{"
                                     "color: #5EBFED;"
                                     "}");
        labelNickname->setCursor(Qt::PointingHandCursor);

        bansLayout->setSpacing(0);
        bansLayout->setMargin(0);
        bansBody->setLayout(bansLayout);
        labelCause->setStyleSheet("font-family: Century Gothic;"
                                  "background: transparent;");

        labelModerator->setStyleSheet("ClickableLabel:hover{"
                                      "color: #5EBFED;"
                                      "}");
        labelModerator->setText(temp.value("Moderator").toString());
        labelModerator->setCursor(Qt::PointingHandCursor);

        bansLayout->addWidget(labelCause);
        bansLayout->addWidget(labelModerator);

        avatar->setFixedSize(30,30);
        avatar->setStyleSheet("background: black;"
                              "border-radius: 15px;");
        avatar->setCursor(Qt::PointingHandCursor);

        labelNickname->setFixedHeight(10);
        startTime->setFixedHeight(10);

        bansBody->setStyleSheet("border: 0px;"
                                "background: transparent;");

        layout->addWidget(nickname, 0, 1, 1, 1);
        layout->addWidget(bansBody, 1, 1, 1, 7, Qt::AlignHCenter | Qt::AlignTop);
        layout->addWidget(startTime, 0, 7, 1, 1, Qt::AlignRight);
        layout->addWidget(finishTime, 1, 7, 1, 1, Qt::AlignRight);

        QWidgetItem *widgetItem = new QWidgetItem(avatar);
        widgetItem->setGeometry(QRect(0,0,30,30));
        layout->addItem(widgetItem, 0,0,3,1, Qt::AlignTop);

        QListWidgetItem* item = new QListWidgetItem(listBansHistory);
        item->setSizeHint(QSize(widget->width(), layout->sizeHint().height()));
        listBansHistory->setItemWidget(item, widget);
    }
}

void BansHistory::loadNewPage(int value){
    if(value == listBansHistory->verticalScrollBar()->maximum() && !end){
        QJsonObject request;
        request.insert("Target", "Bans history");
        request.insert("Page", currentLastPage++);
        TCPClient::getInstance().send(QJsonDocument(request).toJson());
    }
}
