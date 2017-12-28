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
#include "UI/Widgets/imageview.h"
#include "UI/Widgets/sendwidget.h"
#include "UI/Widgets/affiximagewidget.h"
#include "UI/Widgets/clickablelabel.h"
#include "UI/Widgets/globaltextedit.h"
#include "UI/Widgets/privatetextedit.h"
#include "UI/Widgets/wraplabel.h"
#include "Util/tcpclient.h"

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
    QWidget *globalChatWidget;
    QGridLayout *globalChatLayout;
    QWidget *menuListWidget;
    QVBoxLayout *menuListLayout;

    SendWidget *sendWidget;
    AffixImageWidget *affixImageWidget;

    QListWidget *listOfGlobalMessages;

    QPushButton *buttonUserPage;
    QPushButton *buttonPrivateMessages;
    QPushButton *buttonFriends;

    ImageView *imageView;

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
private slots:
    void sendMessage(QString);
    void printMessages();
public slots:
    void start();
};

#endif // MAINWINDOW_H
