#ifndef BANSHISTORY_H
#define BANSHISTORY_H

#include <QListWidget>
#include <QSvgWidget>
#include <QGridLayout>
#include <QLabel>
#include <QScrollBar>
#include <QDateTime>
#include <QPushButton>
#include "Config/def.h"
#include "UI/Widgets/clickablelabel.h"
#include "Util/tcpclient.h"

class BansHistory : public QWidget
{
    Q_OBJECT
public:
    explicit BansHistory(QWidget* parent = nullptr);
    QListWidget* getList();
    void start();

private:
    QListWidget *listBansHistory;
    QSvgWidget *preloader;
    quint8 currentLastPage;
    bool end;

private slots:
    void showBansHistory(QJsonArray, bool);
    void loadNewPage(int);

};

#endif // BANSHISTORY_H
