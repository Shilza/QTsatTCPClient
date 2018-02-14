#ifndef ACCOUNTSETTINGS_H
#define ACCOUNTSETTINGS_H

#include <QWidget>
#include <QPushButton>
#include <QVBoxLayout>
#include <QFileDialog>
#include <QLineEdit>
#include <QLabel>
#include <QDir>
#include "Util/tcpclient.h"

class AccountSettings : public QWidget
{
    Q_OBJECT
public:
    explicit AccountSettings(QWidget *parent = nullptr);
    QWidget *getMainWidget() const;

private:
    QWidget *mainWidget;
    QVBoxLayout *mainLayout;

    QPushButton *buttonAvatar;
    QPushButton *buttonAvatarChanging;

    QLabel *labelNickname;
    QLineEdit *lineNewNickname;

    QLabel *labelAboutMe;
    QLineEdit *lineAboutMe;

    QLabel *labelPassword;
    QLineEdit *lineOldPassword;
    QLineEdit *lineNewPassword;
    QLineEdit *lineConfirmNewPassword;

private slots:
    void avatarChanging();
    void setNickname(QString);
};

#endif // ACCOUNTSETTINGS_H
