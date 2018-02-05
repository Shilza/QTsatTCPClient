#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStackedWidget>
#include "UI/Widgets/imageview.h"
#include "UI/Widgets/banshistory.h"
#include "UI/Widgets/globalchat.h"
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
    ClickableLabel *labelAttachmentSizeToLarge;

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void showBansHistory();
    void goToGlobalChat();
    void exit(bool isExit);

public slots:
    void start(uint);
};

#endif // MAINWINDOW_H
