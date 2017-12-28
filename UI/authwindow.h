#ifndef AUTHWINDOW_H
#define AUTHWINDOW_H

#include <QMainWindow>
#include <QLabel>
#include <QtSvg/QSvgWidget>
#include <QLineEdit>
#include <QTcpSocket>
#include <QPushButton>
#include <QMouseEvent>
#include <QRegExpValidator>
#include <QPropertyAnimation>
#include <QDesktopWidget>
#include <QKeyEvent>
#include <QFontMetrics>
#include <QGraphicsOpacityEffect>
#include <QDateTime>
#include <QTimer>
#include <QNetworkAccessManager>
#include <QJsonObject>
#include <QJsonDocument>
#include <QNetworkReply>
#include <QHostAddress>
#include "UI/Widgets/authlineedit.h"
#include "UI/Widgets/clickablelabel.h"
#include "Config/def.h"
#include "Util/tcpclient.h"

#define DURATION 300
#define LOC_SIGNIN 1
#define LOC_REGISTRATION 2
#define LOC_REGISTRATION_CODE 3
#define LOC_RECOVERY_EMAIL 4
#define LOC_RECOVERY_CODE 5
#define LOC_RECOVERY_PASS 6

namespace Ui {
class AuthWindow;
}

class AuthWindow : public QMainWindow
{
    Q_OBJECT

private:
    Ui::AuthWindow *ui;
    int defaultFontSize;
    bool nicknameExists = false;
    bool isPassEmpty = false;
    bool isRecoveryPassEmpty = false;

    quint8 location=LOC_SIGNIN;

    quint16 defaultY, defaultLineX, defaultButtonX;
    quint16 lineW, lineH;
    quint16 buttonW, buttonH;
    quint16 lineHWithSpace, buttonHWithSpace;

    AuthLineEdit *lineEmail;
    AuthLineEdit *lineLog;
    AuthLineEdit *linePass;
    AuthLineEdit *lineConfirmPass;
    AuthLineEdit *lineConfirmCode;
    AuthLineEdit *lineRecoveryPass;
    AuthLineEdit *lineRecoveryConfirmPass;

    QPushButton *buttonSignIn;
    QPushButton *buttonSignUp;
    QPushButton *buttonOk;
    QPushButton *buttonClose;
    QPushButton *buttonEye;
    QPushButton *buttonRecoveryEye;
    QPushButton *buttonMinimize;

    QLabel *labelUncorrectNickname;
    QLabel *labelPass;
    QLabel *labelRecoveryPass;
    ClickableLabel *labelForgotPass;
    ClickableLabel *labelSignUp;
    ClickableLabel *labelSignIn;
    ClickableLabel *labelError;
    ClickableLabel *labelErrorBackground;
    ClickableLabel *labelSuccess;

    QSvgWidget *preloader;
    QGraphicsOpacityEffect *opacity;
    QGraphicsOpacityEffect *opacityLabel;
    QPoint mpos;

    QTimer *timerWaitingAnswer;
    QTimer *timerLabelSuccess;
    QTimer *timerErrorLabel;

    bool isOnline();
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *);
    void changeEvent(QEvent *e);
    void setPassEnabled();
    void resizeAll();

public:
    explicit AuthWindow(QMainWindow *parent = 0);
    bool eventFilter(QObject *target, QEvent *event);
    ~AuthWindow();

signals:
    void startMainWindow();
    void loadingWasStart();
    void errorHasOccured();

private slots:
    void signIn_released();
    void authorizationSend();
    void signUp_released();
    void registrationSend();
    void registrationCodeSend();
    void buttonOk_released();
    void recoveryEmailSend();
    void recoveryCodeSend();
    void recoveryNewPassSend();

    void gotoSignInLoc();
    void gotoSignUpLoc();
    void gotoRecoveryLoc();

    void waitingAnswer();

    void checkingNickname();
    void checkingConfirming(QString);
    void checkingRecoveryConfirming(QString);

    void changingPassEchoMode();
    void changingRecoveryPassEchoMode();
    void changingPassBorder();
    void changingRecoveryPassBorder();
    void changingStateOfNicknameExist();

    void buttonMinimize_released();

    void startPreloading();
    void cancelPreloading();

    void errorHide();
    void labelSuccessHide();

    void authorizationReceived(QString);
    void nicknameExisting(QString);
    void registrationReceived(QString);
    void registrationCodeReceived(QString);
    void recoveryReceived(QString);
    void recoveryCodeReceived(QString);
    void recoveryNewPassReceived(QString);
};

#endif // AUTHWINDOW_H
