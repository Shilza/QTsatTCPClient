#ifndef ACCOUNTSETTINGS_H
#define ACCOUNTSETTINGS_H

#include <QWidget>
#include <QPushButton>
#include <QGridLayout>
#include <QFileDialog>
#include <QLineEdit>
#include <QLabel>
#include <QDir>
#include <QHBoxLayout>
#include <QEvent>
#include <QKeyEvent>
#include <QRegExpValidator>
#include "Util/tcpclient.h"
#include "Util/sizecounting.h"

class AccountSettings : public QWidget
{
    Q_OBJECT
public:
    explicit AccountSettings(QWidget *parent = nullptr);
    QWidget *getMainWidget() const;

private:
    bool eventFilter(QObject *watched, QEvent *event);

    QWidget *mainWidget;
    QGridLayout *mainLayout;

    QWidget *avatarWidget;
    QPixmap avatarImage;
    QPushButton *buttonAvatar;
    QPushButton *buttonAvatarChanging;
    QString avatarExtension;

    QLabel *labelNickname;
    QLineEdit *lineNewNickname;

    QLabel *labelAboutMe;
    QLineEdit *lineAboutMe;

    QWidget *widgetPassword;
    QHBoxLayout *layoutPassword;
    QLabel *labelPassword;
    QPushButton *buttonEye;
    QLineEdit *lineOldPassword;
    QLineEdit *lineNewPassword;
    QLineEdit *lineConfirmNewPassword;

    QPushButton *buttonBlackList;
    QPushButton *buttonActivityHistory;

private slots:
    void avatarChanging();
    void setNickname(QString);
    void setPassEchoMode();
    void setAvatarImage(QPixmap image);
    void setAvatarImage();
    void loadingAvatarToFTP();

signals:
    void attachmentToLarge();
};

#endif // ACCOUNTSETTINGS_H
