#include "UI/mainwindow.h"
#include "UI/authwindow.h"
#include "Util/tcpclient.h"
#include <QApplication>


int main(int argc, char *argv[])
{   
    QApplication a(argc, argv);

    MainWindow *mainWindow = new MainWindow;
    AuthWindow *authWindow = new AuthWindow;
    authWindow->show();

    QObject::connect(authWindow, SIGNAL(startMainWindow(uint)), mainWindow, SLOT(start(uint)));
    QObject::connect(&(TCPClient::getInstance()), SIGNAL(exit()), mainWindow, SLOT(close()));
    QObject::connect(&(TCPClient::getInstance()), SIGNAL(exit()), authWindow, SLOT(show()));

    return a.exec();
}
