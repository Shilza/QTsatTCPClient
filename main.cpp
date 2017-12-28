#include "UI/mainwindow.h"
#include "UI/authwindow.h"
#include <QApplication>


int main(int argc, char *argv[])
{   
    QApplication a(argc, argv);

    MainWindow *mainWindow=new MainWindow;
    AuthWindow *authWindow=new AuthWindow;
    authWindow->show();

    QObject::connect(authWindow, SIGNAL(startMainWindow()), mainWindow, SLOT(start()));

    return a.exec();
}
