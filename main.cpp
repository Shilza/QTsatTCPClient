#include "UI/mainwindow.h"
#include "UI/authwindow.h"
#include "Util/tcpclient.h"
#include <QApplication>

int main(int argc, char *argv[])
{   
    QApplication a(argc, argv);

    MainWindow *mainWindow = new MainWindow;
    AuthWindow *authWindow = new AuthWindow;

    QFile configFile("config.txt");
    if (configFile.exists()){
        if(!configFile.open(QIODevice::ReadOnly))
            configFile.remove();
        else{
            QJsonObject configJson = QJsonDocument::fromJson(configFile.readAll()).object();
            authWindow->start(configJson.value("Nickname").toString(),
                              configJson.value("Access token").toString(),
                              configJson.value("Refresh token").toString());
        }
        configFile.close();
    }
    authWindow->show();

    QObject::connect(authWindow, SIGNAL(startMainWindow(uint)), mainWindow, SLOT(start(uint)));

    return a.exec();
}
