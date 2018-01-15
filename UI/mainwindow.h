#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QGridLayout>
#include <QVBoxLayout>
#include <QListWidget>
#include <QScrollBar>
#include <QStackedWidget>
#include <QPixmap>
#include <QSvgWidget>
#include <QLocale>
#include "UI/Widgets/imageview.h"
#include "UI/Widgets/clickablelabel.h"
#include "UI/Widgets/privatetextedit.h"
#include "UI/Widgets/banshistory.h"
#include "UI/Widgets/globalchat.h"
#include "Util/tcpclient.h"
#include "UI/Widgets/menulist.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

private:
    Ui::MainWindow *ui;

    QStackedWidget *stackOfWidgets;
    QWidget *mainWidget;
    QHBoxLayout *mainLayout;
    MenuList *menuListWidget;
    BansHistory *bansHistory;
    GlobalChat *globalChat;

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void showBansHistory();
    void goToGlobalChat();

public slots:
    void start(uint);
};

#endif // MAINWINDOW_H
