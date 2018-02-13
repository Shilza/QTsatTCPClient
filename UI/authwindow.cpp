#include "authwindow.h"
#include "ui_authwindow.h"

AuthWindow::AuthWindow(QMainWindow *parent) :
    QMainWindow(parent),
    ui(new Ui::AuthWindow)
{
    ui->setupUi(this);

    timerWaitingAnswer = new QTimer(this);
    timerWaitingAnswer->setInterval(10000);
    timerWaitingAnswer->setSingleShot(true);

    timerLabelSuccess = new QTimer(this);
    timerLabelSuccess->setInterval(2000);
    timerLabelSuccess->setSingleShot(true);

    timerErrorLabel = new QTimer(this);
    timerErrorLabel->setInterval(5000);
    timerErrorLabel->setSingleShot(true);

    timerAuthentication = new QTimer(this);
    timerAuthentication->setInterval(DURATION);

    QTime randTime(0,0,0);
    qsrand(randTime.secsTo(QTime::currentTime()));

    labelPass = new QLabel(this);
    labelRecoveryPass = new QLabel(this);

    lineLog = new AuthLineEdit(this);
    linePass = new AuthLineEdit(labelPass, false);
    lineConfirmPass = new AuthLineEdit(this);
    lineEmail = new AuthLineEdit(this);
    lineConfirmCode = new AuthLineEdit(this);
    lineRecoveryPass = new AuthLineEdit(labelRecoveryPass, false);
    lineRecoveryConfirmPass = new AuthLineEdit(this);

    buttonSignUp = new QPushButton(this);
    buttonSignIn = new QPushButton(this);
    buttonOk = new QPushButton(this);
    buttonMinimize = new QPushButton(this);
    buttonClose = new QPushButton(this);
    buttonEye = new QPushButton(labelPass);
    buttonRecoveryEye = new QPushButton(labelRecoveryPass);

    labelForgotPass = new ClickableLabel(this);
    labelSignUp = new ClickableLabel(this);
    labelSignIn = new ClickableLabel(this);
    labelSuccess = new ClickableLabel(this, false);
    labelUncorrectNickname = new QLabel(this);
    labelErrorBackground = new ClickableLabel(this);
    labelError = new ClickableLabel(labelErrorBackground, false);

    preloader = new QSvgWidget(this);
    opacity = new QGraphicsOpacityEffect;
    opacityLabel = new QGraphicsOpacityEffect;

    buttonClose->installEventFilter(this);
    buttonMinimize->installEventFilter(this);
    lineLog->installEventFilter(this);
    linePass->installEventFilter(this);
    buttonEye->installEventFilter(this);
    lineRecoveryPass->installEventFilter(this);
    buttonRecoveryEye->installEventFilter(this);
    lineEmail->installEventFilter(this);
    lineConfirmPass->installEventFilter(this);
    lineRecoveryConfirmPass->installEventFilter(this);
    lineConfirmCode->installEventFilter(this);

    buttonEye->setCursor(Qt::ArrowCursor);
    buttonRecoveryEye->setCursor(Qt::ArrowCursor);
    buttonSignIn->setCursor(Qt::PointingHandCursor);
    buttonOk->setCursor(Qt::PointingHandCursor);
    buttonSignUp->setCursor(Qt::PointingHandCursor);

    labelSignUp->setCursor(Qt::PointingHandCursor);
    labelSignIn->setCursor(Qt::PointingHandCursor);
    labelForgotPass->setCursor(Qt::PointingHandCursor);

    lineEmail->setValidator(new QRegExpValidator(QRegExp("([^@]){,32}(@?)([^@]){,32}")));
    lineLog->setValidator(new QRegExpValidator(QRegExp("([^@]){,32}(@?)([^@]){,12}")));
    lineConfirmPass->setValidator(new QRegExpValidator(QRegExp("^(\\d|\\w|[._]){6,32}$")));
    linePass->setValidator(new QRegExpValidator(QRegExp("^(\\d|\\w|[._]){6,32}$")));
    lineRecoveryPass->setValidator(new QRegExpValidator(QRegExp("^(\\d|\\w|[._]){6,32}$")));
    lineRecoveryConfirmPass->setValidator(new QRegExpValidator(QRegExp("^(\\d|\\w|[._]){6,32}$")));
    lineConfirmCode->setValidator(new QRegExpValidator(QRegExp("^(\\d|\\w){,6}$")));

    linePass->setEchoMode(QLineEdit::Password);
    lineConfirmPass->setEchoMode(QLineEdit::Password);
    lineRecoveryPass->setEchoMode(QLineEdit::Password);
    lineRecoveryConfirmPass->setEchoMode(QLineEdit::Password);

    lineLog->setPlaceholderText("Login or email");
    linePass->setPlaceholderText("Password");
    lineConfirmPass->setPlaceholderText("Confirm password");
    lineEmail->setPlaceholderText("Email");
    lineConfirmCode->setPlaceholderText("Confirmation code");
    lineRecoveryPass->setPlaceholderText("New password");
    lineRecoveryConfirmPass->setPlaceholderText("Confirm new password");

    buttonSignIn->setText("Sign in");
    buttonSignUp->setText("Sign up");
    buttonOk->setText("Ok");

    labelForgotPass->setText("Forgot password?");
    labelForgotPass->setAlignment(Qt::AlignLeft | Qt::AlignTop);
    labelSignUp->setText("Sign up");
    labelSignUp->setAlignment(Qt::AlignRight | Qt::AlignTop);
    labelSignIn->setText("Sign in");
    labelUncorrectNickname->setText("Nickname already exists");
    labelUncorrectNickname->setAlignment(Qt::AlignLeft | Qt::AlignTop);
    labelError->setText("Wrong login or password");
    labelError->setAlignment(Qt::AlignCenter|Qt::AlignTop);
    labelSuccess->setAlignment(Qt::AlignCenter);

    setMouseTracking(true);
    lineLog->setMouseTracking(true);
    preloader->load(QString(":images/pre.svg"));

    labelAuthentication = new QLabel(this);

    resizeAll();

    this->setAttribute(Qt::WA_TranslucentBackground);
    this->setWindowFlags(Qt::FramelessWindowHint);
    this->setStyleSheet("background-image: url(background.png);");

    QString strButtonStyle =  "QPushButton{"
                              "font-family: Century Gothic;"
                              "font-size: %1px;"
                              "border-radius: 6px;"
                              "border: 1px solid black;"
                              "background: rgba(172,230,168,245);"
                              "}"
                              "QPushButton:focus:pressed{"
                              "border: 2px solid #63E3E9;"
                              "background: rgba(172,230,168,210);"
                              "}"
                              "QPushButton:hover{"
                              "border-radius: 6px;"
                              "border: 1px solid #63E3E9;"
                              "background: rgba(172,230,168,220);"
                              "}";

    defaultFontSize = (width()/260)*11;
    preloader->setStyleSheet("background:transparent;");

    labelAuthentication->setStyleSheet(QString("background: transparent;"
                                       "color: #d9d9d9;"
                                       "font-size: %1px;").arg(defaultFontSize*3/2));

    buttonSignIn->setStyleSheet(strButtonStyle.arg(defaultFontSize));
    buttonSignUp->setStyleSheet(strButtonStyle.arg(defaultFontSize));
    buttonOk->setStyleSheet(strButtonStyle.arg(defaultFontSize));

    buttonEye->setStyleSheet("QPushButton{"
                             "background: transparent;"
                             "border: 1px solid gray;"
                             "border-left: 0px;"
                             "}");
    buttonEye->setIcon(QIcon(":images/eye.png"));

    buttonRecoveryEye->setStyleSheet("QPushButton{"
                                     "background: transparent;"
                                     "border: 1px solid gray;"
                                     "border-left: 0px;"
                                     "}");
    buttonRecoveryEye->setIcon(QIcon(":images/eye.png"));


    buttonClose->setStyleSheet("QPushButton {"
                               "qproperty-icon: url(:/images/close1.png);"
                               "border: 0px;"
                               "background: transparent;"
                               "}"
                               "QPushButton:hover{"
                               "background: #fd3755;"
                               "border: 0px;"
                               "}");

    buttonMinimize->setStyleSheet("QPushButton {"
                                  "qproperty-icon: url(:/images/min1.png);"
                                  "border: 0px;"
                                  "background: transparent;"
                                  "}"
                                  "QPushButton:hover{"
                                  "background: #939494;"
                                  "border: 0px;"
                                  "}");

    linePass->setStyleSheet(QString("AuthLineEdit{"
                                    "font-family: Century Gothic;"
                                    "font-size: %1px;"
                                    "background: transparent;"
                                    "border: 1px solid gray;"
                                    "border-right: 0px;"
                                    "color: #B5EBEE;"
                                    "}").arg(defaultFontSize));
    lineRecoveryPass->setStyleSheet(QString("AuthLineEdit{"
                                            "font-family: Century Gothic;"
                                            "font-size: %1px;"
                                            "background: transparent;"
                                            "border: 1px solid gray;"
                                            "border-right: 0px;"
                                            "color: #B5EBEE;"
                                            "}").arg(defaultFontSize));

    labelForgotPass->setStyleSheet(QString("font-family: Century Gothic;"
                                           "font-size: %1px;"
                                           "background: transparent;"
                                           "color: #B5EBEE;").arg(defaultFontSize));

    labelSignUp->setStyleSheet(QString("font-family: Century Gothic;"
                                       "font-size: %1px;"
                                       "background: transparent;"
                                       "color: #B5EBEE;").arg(defaultFontSize));

    labelSignIn->setStyleSheet(QString("font-family: Century Gothic;"
                                       "font-size: %1px;"
                                       "background: transparent;"
                                       "color: #B5EBEE;").arg(defaultFontSize));

    labelError->setStyleSheet(QString("font-family: Century Gothic;"
                                                 "font-size: %1px;"
                                                 "background: transparent;"
                                                 "color: red;").arg(defaultFontSize/11*13));

    labelSuccess->setStyleSheet(QString("font-family: Century Gothic;"
                                        "font-size: %1px;"
                                        "background: rgba(255,255,255,200);").arg(defaultFontSize/11*13));
    labelPass->setStyleSheet("background: transparent;");
    labelRecoveryPass->setStyleSheet("background: transparent;");


    labelErrorBackground->setStyleSheet("background:transparent;");
    labelErrorBackground->setPixmap(QPixmap(":images/gradient.png").scaled(width(),labelErrorBackground->height()));

    QFont fontGothic("Century Gothic");
    fontGothic.setBold(true);
    fontGothic.setPointSize((defaultFontSize/11)*8);

    labelUncorrectNickname->setStyleSheet("background: transparent;"
                                          "color: red;");
    labelUncorrectNickname->setFont(fontGothic);

    QFontMetrics *tempFontSize = new QFontMetrics(labelUncorrectNickname->font());
    labelUncorrectNickname->resize(QSize(tempFontSize->width(labelUncorrectNickname->text()), tempFontSize->height()));
    delete tempFontSize;

    labelSuccess->setGraphicsEffect(opacityLabel);

    lineConfirmPass->close();
    lineEmail->close();
    lineConfirmCode->close();

    labelSignIn->close();
    labelSuccess->close();
    labelUncorrectNickname->close();
    labelErrorBackground->close();

    buttonOk->close();
    buttonSignUp->close();

    preloader->close();

    connect(this, SIGNAL(loadingWasStart()),this, SLOT(startPreloading()));
    connect(this, SIGNAL(errorHasOccured()), this, SLOT(cancelPreloading()));

    connect(buttonSignIn, SIGNAL(released()), this, SLOT(signIn_released()));
    connect(buttonSignUp, SIGNAL(released()), this, SLOT(signUp_released()));
    connect(buttonOk, SIGNAL(released()), this, SLOT(buttonOk_released()));
    connect(buttonEye, SIGNAL(released()), this, SLOT(changingPassEchoMode()));
    connect(buttonClose, SIGNAL(released()), this, SLOT(close()));
    connect(buttonMinimize, SIGNAL(released()), this, SLOT(buttonMinimize_released()));
    connect(buttonRecoveryEye, SIGNAL(released()), this, SLOT(changingRecoveryPassEchoMode()));

    connect(labelSignUp, SIGNAL(released()),this, SLOT(gotoSignUpLoc()));
    connect(labelSignIn, SIGNAL(released()),this, SLOT(gotoSignInLoc()));
    connect(labelForgotPass, SIGNAL(released()), this,SLOT(gotoRecoveryLoc()));
    connect(labelSuccess, SIGNAL(released()), this, SLOT(labelSuccessHide()));
    connect(labelError, SIGNAL(released()),this,SLOT(errorHide()));

    connect(lineLog, SIGNAL(editingFinished()), this, SLOT(checkingNickname()));
    connect(lineLog, SIGNAL(textEdited(QString)), this, SLOT(changingStateOfNicknameExist()));
    connect(linePass, SIGNAL(textChanged(QString)), this, SLOT(checkingConfirming(QString)));
    connect(linePass, SIGNAL(textChanged(QString)), this, SLOT(changingPassBorder()));
    connect(lineConfirmPass, SIGNAL(textChanged(QString)),this, SLOT(checkingConfirming(QString)));
    connect(lineRecoveryPass, SIGNAL(textChanged(QString)), this, SLOT(checkingRecoveryConfirming(QString)));
    connect(lineRecoveryPass, SIGNAL(textChanged(QString)), this, SLOT(changingRecoveryPassBorder()));
    connect(lineRecoveryConfirmPass, SIGNAL(textChanged(QString)),this, SLOT(checkingRecoveryConfirming(QString)));
    connect(timerWaitingAnswer, SIGNAL(timeout()), this, SLOT(waitingAnswer()));
    connect(timerLabelSuccess, SIGNAL(timeout()), this, SLOT(labelSuccessHide()));
    connect(timerErrorLabel, SIGNAL(timeout()), this, SLOT(errorHide()));
    connect(timerAuthentication, SIGNAL(timeout()), this, SLOT(labelAuthenticationChanging()));

    connect(&(TCPClient::getInstance()), SIGNAL(authorization(QString, uint)), SLOT(authorizationReceived(QString, uint)));
    connect(&(TCPClient::getInstance()), SIGNAL(registration(QString)), SLOT(registrationReceived(QString)));
    connect(&(TCPClient::getInstance()), SIGNAL(registrationCode(QString)), SLOT(registrationCodeReceived(QString)));
    connect(&(TCPClient::getInstance()), SIGNAL(recovery(QString)), SLOT(recoveryReceived(QString)));
    connect(&(TCPClient::getInstance()), SIGNAL(recoveryCode(QString)), SLOT(recoveryCodeReceived(QString)));
    connect(&(TCPClient::getInstance()), SIGNAL(recoveryNewPass(QString)), SLOT(recoveryNewPassReceived(QString)));
    connect(&(TCPClient::getInstance()), SIGNAL(nicknameExisting(QString)), SLOT(nicknameExisting(QString)));
    connect(&(TCPClient::getInstance()), SIGNAL(exit(bool)), SLOT(tokensDead()));
}

void AuthWindow::start(QString nickname, QString accessToken, QString refreshToken){
    lineLog->close();
    linePass->close();
    labelSignUp->close();
    labelForgotPass->close();
    buttonSignIn->close();
    buttonEye->close();

    labelAuthentication->setText("Authentication");
    labelAuthentication->show();
    timerAuthentication->start();

    TCPClient::getInstance().setUser(nickname, accessToken, refreshToken);
    QJsonObject request;
    request.insert("Target", "Authorization");
    request.insert("Access token", accessToken);
    request.insert("Nickname", nickname);
    TCPClient::getInstance().send(QJsonDocument(request).toJson());
}


void AuthWindow::signIn_released(){
    QString log = lineLog->text();
    QString pass = linePass->text();
    bool isLineEmpty=false;

    if(log==""){
        lineLog->setErrorStyleSheet();
        isLineEmpty=true;
    }
    if(pass==""){
        isPassEmpty=true;
        linePass->setStyleSheet(QString("font-family: Century Gothic;"
                                        "font-size: %1px;"
                                        "background: transparent;"
                                        "border: 1px solid red;"
                                        "border-right: 0px;"
                                        "color: #B5EBEE;").arg(defaultFontSize));
        buttonEye->setStyleSheet("border: 1px solid red;"
                                 "border-left: 0px;");
        isLineEmpty=true;
    }

    if(!isLineEmpty){
        if(!isOnline()){
            labelError->setText("No Internet access");
            emit errorHasOccured();
        }
        else{
            emit loadingWasStart();
            errorHide();

            timerWaitingAnswer->start();
            QTimer::singleShot(DURATION*2, this, SLOT(authorizationSend()));
        }
    }
}

void AuthWindow::authorizationSend(){
    QJsonObject request;
    request.insert("Target", "Authorization");
    request.insert("Login", lineLog->text());
    request.insert("Password", QString::fromUtf8(QCryptographicHash::hash(linePass->text().toUtf8(), QCryptographicHash::Md5).toHex()));
    TCPClient::getInstance().send(QJsonDocument(request).toJson());
}


void AuthWindow::signUp_released(){
    if(location==LOC_REGISTRATION){
        QString email = lineEmail->text();
        QString log = lineLog->text();
        QString pass = linePass->text();
        QString confirmPass = lineConfirmPass->text();
        bool isLineEmpty=false;

        if(email==""){
            isLineEmpty=true;
            lineEmail->setErrorStyleSheet();
        }
        if(log==""){
            isLineEmpty=true;
            lineLog->setErrorStyleSheet();
        }
        if(pass==""){
            isLineEmpty=true;
            isPassEmpty=true;
            linePass->setStyleSheet(QString("font-family: Century Gothic;"
                                            "font-size: %1px;"
                                            "background: transparent;"
                                            "border: 1px solid red;"
                                            "border-right: 0px;"
                                            "color: #B5EBEE;").arg(defaultFontSize));
            buttonEye->setStyleSheet("border: 1px solid red;"
                                     "border-left: 0px;");
        }
        if(confirmPass==""){
            isLineEmpty=true;
            lineConfirmPass->setErrorStyleSheet();
        }
        if(!isLineEmpty && pass==confirmPass){

            if(!isOnline()){
                labelError->setText("No Internet access");
                emit errorHasOccured();
            }
            else{
                emit loadingWasStart();
                errorHide();

                timerWaitingAnswer->start();
                QTimer::singleShot(500, this, SLOT(registrationSend()));
            }
        }
    }
    else if(location==LOC_REGISTRATION_CODE){
        if(lineConfirmCode->text()==""){
            lineConfirmCode->setErrorStyleSheet();
        }
        else{

            if(!isOnline()){
                labelError->setText("No Internet access");
                emit errorHasOccured();
            }
            else{
                emit loadingWasStart();
                errorHide();
                lineConfirmCode->setDisabledOverride();

                timerWaitingAnswer->start();
                QTimer::singleShot(500, this, SLOT(registrationCodeSend()));
            }
        }
    }
}

void AuthWindow::registrationSend(){
    QJsonObject request;
    request.insert("Target", "Registration");
    request.insert("Email", lineEmail->text());
    request.insert("Nickname", lineLog->text());
    TCPClient::getInstance().send(QJsonDocument(request).toJson());
}

void AuthWindow::registrationCodeSend(){
    QJsonObject request;
    request.insert("Target", "Registration code");
    request.insert("Email", lineEmail->text());
    request.insert("Nickname", lineLog->text());
    request.insert("Password", QString::fromUtf8(QCryptographicHash::hash(linePass->text().toUtf8(), QCryptographicHash::Md5).toHex()));
    request.insert("Code", lineConfirmCode->text());
    TCPClient::getInstance().send(QJsonDocument(request).toJson());
}


void AuthWindow::buttonOk_released(){
    if(location == LOC_RECOVERY_EMAIL){
        if(lineLog->text()==""){
            lineLog->setErrorStyleSheet();
        }
        else{
            if(!isOnline()){
                labelError->setText("No Internet access");
                emit errorHasOccured();
            }
            else{
                emit loadingWasStart();
                errorHide();

                timerWaitingAnswer->start();
                QTimer::singleShot(500, this, SLOT(recoveryEmailSend()));
            }
        }
    }
    else if(location == LOC_RECOVERY_CODE){
        if(lineConfirmCode->text()==""){
            lineConfirmCode->setErrorStyleSheet();
        }
        else{

            if(!isOnline()){
                labelError->setText("No Internet access");
                emit errorHasOccured();
            }
            else{
                emit loadingWasStart();
                errorHide();
                lineConfirmCode->setDisabledOverride();

                timerWaitingAnswer->start();
                QTimer::singleShot(500, this, SLOT(recoveryCodeSend()));
            }
        }
    }
    else if(location == LOC_RECOVERY_PASS){
        if(lineRecoveryConfirmPass->text()==""){
            lineRecoveryConfirmPass->setErrorStyleSheet();
        }

        if(lineRecoveryPass->text().length() < 6){
            isRecoveryPassEmpty=true;
            lineRecoveryPass->setStyleSheet(QString("font-family: Century Gothic;"
                                                    "font-size: %1px;"
                                                    "background: transparent;"
                                                    "border: 1px solid red;"
                                                    "border-right: 0px;"
                                                    "color: #B5EBEE;").arg(defaultFontSize));
            buttonRecoveryEye->setStyleSheet("border: 1px solid red;"
                                             "border-left: 0px;");
        }
        else if(lineRecoveryConfirmPass->text()!=lineRecoveryPass->text()){
            lineRecoveryConfirmPass->setErrorStyleSheet();
        }
        else{

            if(!isOnline()){
                labelError->setText("No Internet access");
                emit errorHasOccured();
            }
            else{
                emit loadingWasStart();
                errorHide();
                lineRecoveryConfirmPass->setDisabledOverride();
                labelRecoveryPass->setDisabled(true);
                lineRecoveryPass->setDisabled(true);
                buttonRecoveryEye->setDisabled(true);
                lineRecoveryPass->setStyleSheet(QString("AuthLineEdit{"
                                                        "font-family: Century Gothic;"
                                                        "font-size: %1px;"
                                                        "background: transparent;"
                                                        "border: 1px solid #cccccc;"
                                                        "border-right: 0px;"
                                                        "color: #B5EBEE;"
                                                        "}").arg(defaultFontSize));
                buttonRecoveryEye->setStyleSheet("border: 1px solid #cccccc; border-left: 0px;");
                buttonRecoveryEye->setStyleSheet("border: 1px solid #cccccc; border-left: 0px");

                timerWaitingAnswer->start();
                QTimer::singleShot(500, this, SLOT(recoveryNewPassSend()));
            }
        }
    }
}

void AuthWindow::recoveryEmailSend(){
    QJsonObject request;
    request.insert("Target", "Recovery");
    request.insert("Value", lineLog->text());

    TCPClient::getInstance().send(QJsonDocument(request).toJson());
}

void AuthWindow::recoveryCodeSend(){
    QJsonObject request;
    request.insert("Target", "Recovery code");
    request.insert("Value", lineLog->text());
    request.insert("Code", lineConfirmCode->text());

    TCPClient::getInstance().send(QJsonDocument(request).toJson());
}

void AuthWindow::recoveryNewPassSend(){
    QJsonObject request;
    request.insert("Target", "Recovery new pass");
    request.insert("Value", lineLog->text());
    request.insert("Password", QString::fromUtf8(QCryptographicHash::hash(lineRecoveryPass->text().toUtf8(), QCryptographicHash::Md5).toHex()));

    TCPClient::getInstance().send(QJsonDocument(request).toJson());
}


void AuthWindow::labelSuccessHide(){
    timerLabelSuccess->stop();
    QPropertyAnimation *animation = new QPropertyAnimation(opacityLabel, "opacity");
    animation->setDuration(DURATION);
    animation->setEndValue(0.0);
    animation->start(QAbstractAnimation::DeleteWhenStopped);
    connect(animation, SIGNAL(finished()), labelSuccess, SLOT(close()));
    connect(animation, SIGNAL(finished()), labelErrorBackground, SLOT(close()));

    if(location==LOC_REGISTRATION){
        connect(animation, SIGNAL(finished()), this, SLOT(gotoSignInLoc()));
    }
}


void AuthWindow::authorizationReceived(QString value, uint time){
    timerWaitingAnswer->stop();
    if(value == "Authorization failed"){
        labelError->setText("Invalid password or nickname");
        emit errorHasOccured();
    }
    else if(value == "Authorization successful"){
        close();
        lineLog->show();
        linePass->show();
        labelSignUp->show();
        labelForgotPass->show();
        buttonSignIn->show();
        buttonEye->show();

        labelAuthentication->close();

        timerAuthentication->stop();

        gotoSignInLoc();
        cancelPreloading();
        errorHide();
        linePass->clear();
        emit startMainWindow(time);
    }
}

void AuthWindow::nicknameExisting(QString value){
    timerWaitingAnswer->stop();
    if(value == "Nickname exists"){
        nicknameExists = true;
        lineLog->setErrorStyleSheet();
    }
    else if(value == "Nickname doesn't exist"){
        nicknameExists = false;
        labelUncorrectNickname->close();
        lineLog->setDefaultStyleSheet();
    }
}

void AuthWindow::registrationReceived(QString value){
    timerWaitingAnswer->stop();
    if(value == "Email exists"){
        labelError->setText("Email already exists");
        emit errorHasOccured();
    }
    else if(value == "Email doesn't exist"){
        preloader->close();
        labelSuccess->show();
        lineConfirmCode->show();
        buttonSignUp->show();
        opacity->setOpacity(1.0);
        labelSuccess->setText("Сheck your email for confirmation code");
        lineConfirmCode->setEnabledOverride();

        QPropertyAnimation *animations[6];
        animations[0] = new QPropertyAnimation(labelPass, "pos");
        animations[1] = new QPropertyAnimation(lineConfirmPass, "pos");
        animations[2] = new QPropertyAnimation(lineConfirmCode, "pos");
        animations[3] = new QPropertyAnimation(buttonSignUp, "pos");
        animations[4] = new QPropertyAnimation(labelSignIn, "pos");
        animations[5] = new QPropertyAnimation(opacityLabel, "opacity");

        animations[0]->setEndValue(QPoint(width(), labelPass->y()));
        animations[1]->setEndValue(QPoint(width(), lineConfirmPass->y()));
        animations[2]->setStartValue(QPoint(defaultLineX, height()));
        animations[2]->setEndValue(QPoint(defaultLineX, defaultY+lineHWithSpace));
        animations[3]->setStartValue(QPoint(defaultButtonX, height()+lineHWithSpace));
        animations[3]->setEndValue(QPoint(defaultButtonX, defaultY+(2*lineHWithSpace)));
        animations[4]->setEndValue(QPoint(labelSignIn->x(), defaultY+(2*lineHWithSpace)+buttonHWithSpace));
        animations[5]->setStartValue(0.0);
        animations[5]->setEndValue(1.0);

        for(int i=0; i<5; i++){
            animations[i]->setDuration(DURATION);
            animations[i]->start(QAbstractAnimation::DeleteWhenStopped);
        }

        animations[5]->setDuration(DURATION*2);
        animations[5]->start(QAbstractAnimation::DeleteWhenStopped);
        timerLabelSuccess->start();
        location = LOC_REGISTRATION_CODE;
    }
}

void AuthWindow::registrationCodeReceived(QString value){
    timerWaitingAnswer->stop();
    if(value == "Registration successful"){
        preloader->close();
        labelSuccess->setText("Registration completed successfully");

        labelSignUp->show();
        labelSuccess->show();
        lineLog->setEnabledOverride();
        setPassEnabled();

        QPropertyAnimation *animations[6];
        animations[0] = new QPropertyAnimation(opacityLabel, "opacity");
        animations[1] = new QPropertyAnimation(lineEmail, "pos");
        animations[2] = new QPropertyAnimation(labelPass, "pos");
        animations[3] = new QPropertyAnimation(buttonSignIn, "pos");
        animations[4] = new QPropertyAnimation(labelForgotPass, "pos");
        animations[5] = new QPropertyAnimation(labelSignUp, "pos");

        animations[0]->setStartValue(0.0);
        animations[0]->setEndValue(1.0);
        animations[1]->setEndValue(QPoint(width(), lineEmail->y()));
        animations[2]->setStartValue(QPoint(-lineW, defaultY+lineHWithSpace));
        animations[2]->setEndValue(QPoint(defaultLineX, defaultY+lineHWithSpace));
        animations[3]->setStartValue(QPoint(defaultButtonX, height()));
        animations[3]->setEndValue(QPoint(defaultButtonX, defaultY+(2*lineHWithSpace)));
        animations[4]->setStartValue(QPoint(defaultLineX, height()+buttonHWithSpace));
        animations[4]->setEndValue(QPoint(defaultLineX, defaultY+(2*lineHWithSpace)+buttonHWithSpace));
        animations[5]->setStartValue(QPoint(defaultLineX+lineW-labelSignUp->width(), height()+buttonHWithSpace));
        animations[5]->setEndValue(QPoint(defaultLineX+lineW-labelSignUp->width(), defaultY+(2*lineHWithSpace)+buttonHWithSpace));

        for(int i=1; i<6; i++){
            animations[i]->setDuration(DURATION);
            animations[i]->start(QAbstractAnimation::DeleteWhenStopped);
        }
        animations[0]->setDuration(DURATION*2);
        animations[0]->start(QAbstractAnimation::DeleteWhenStopped);

        location = LOC_SIGNIN;
        timerLabelSuccess->start();
    }
    else if(value == "Invalid code"){
        labelError->setText("Invalid confirmation code");
        emit errorHasOccured();
    }
}

void AuthWindow::recoveryReceived(QString value){
    timerWaitingAnswer->stop();
    if(value == "Founded"){
        preloader->close();
        location = LOC_RECOVERY_CODE;
        QPropertyAnimation *animations[4];
        animations[0] = new QPropertyAnimation(lineConfirmCode, "pos");
        animations[1] = new QPropertyAnimation(buttonOk, "pos");
        animations[2] = new QPropertyAnimation(labelSignIn, "pos");
        animations[3] = new QPropertyAnimation(labelSignUp, "pos");

        lineConfirmCode->show();
        animations[0]->setDuration(DURATION);
        animations[0]->setStartValue(QPoint(defaultLineX, height()));
        animations[0]->setEndValue(QPoint(defaultLineX, defaultY+lineHWithSpace));
        animations[0]->start(QAbstractAnimation::DeleteWhenStopped);

        opacity->setOpacity(1.0);
        buttonOk->show();
        animations[1]->setDuration(DURATION);
        animations[1]->setStartValue(QPoint(buttonOk->x(), height()));
        animations[1]->setEndValue(QPoint(buttonOk->x(), defaultY+(2*lineHWithSpace)));
        animations[1]->start(QAbstractAnimation::DeleteWhenStopped);

        animations[2]->setDuration(DURATION);
        animations[2]->setEndValue(QPoint(labelSignIn->x(), defaultY+(2*lineHWithSpace)+buttonHWithSpace));
        animations[2]->start(QAbstractAnimation::DeleteWhenStopped);

        animations[3]->setDuration(DURATION);
        animations[3]->setEndValue(QPoint(labelSignUp->x(), defaultY+(2*lineHWithSpace)+buttonHWithSpace));
        animations[3]->start(QAbstractAnimation::DeleteWhenStopped);

        lineConfirmCode->setFocus();
    }
    else if(value == "Not founded"){
        labelError->setText("Nickname or email not found");
        emit errorHasOccured();
    }
}

void AuthWindow::recoveryCodeReceived(QString value){
    timerWaitingAnswer->stop();
    if(value == "Right code"){
        location = LOC_RECOVERY_PASS;
        preloader->close();
        QPropertyAnimation *animations[6];
        animations[0] = new QPropertyAnimation(lineConfirmCode, "pos");
        animations[1] = new QPropertyAnimation(labelRecoveryPass, "pos");
        animations[2] = new QPropertyAnimation(lineRecoveryConfirmPass, "pos");
        animations[3] = new QPropertyAnimation(opacity, "opacity");
        animations[4] = new QPropertyAnimation(labelSignIn, "pos");
        animations[5] = new QPropertyAnimation(labelSignUp, "pos");

        labelRecoveryPass->show();
        lineRecoveryConfirmPass->show();
        labelRecoveryPass->setEnabled(true);
        lineRecoveryPass->setEnabled(true);
        buttonRecoveryEye->setEnabled(true);
        lineRecoveryPass->setStyleSheet(QString("AuthLineEdit{"
                                                        "font-family: Century Gothic;"
                                                        "font-size: %1px;"
                                                        "background: transparent;"
                                                        "border: 1px solid #0078d7;"
                                                        "border-right: 0px;"
                                                        "color: #B5EBEE;"
                                                        "}").arg(defaultFontSize));
        lineRecoveryPass->setFocus();
        buttonRecoveryEye->setStyleSheet("QPushButton{"
                                         "background: transparent;"
                                         "border: 1px solid #0078d7;"
                                         "border-left: 0px;"
                                         "}");
        lineRecoveryConfirmPass->setEnabledOverride();

        animations[0]->setEndValue(QPoint(width(), lineConfirmCode->y()));
        animations[1]->setStartValue(QPoint(defaultLineX, height()));
        animations[1]->setEndValue(QPoint(defaultLineX, defaultY+lineHWithSpace));
        animations[2]->setStartValue(QPoint(defaultLineX, height()+lineHWithSpace));
        animations[2]->setEndValue(QPoint(defaultLineX, defaultY+(2*lineHWithSpace)));
        animations[3]->setEndValue(1.0);
        animations[4]->setEndValue(QPoint(labelSignIn->x(), defaultY+(3*lineHWithSpace)+buttonHWithSpace));
        animations[5]->setEndValue(QPoint(labelSignUp->x(), defaultY+(3*lineHWithSpace)+buttonHWithSpace));

        buttonOk->move(defaultButtonX, defaultY+(3*lineHWithSpace));
        buttonOk->show();

        connect(animations[0], SIGNAL(finished()), lineConfirmCode, SLOT(clear()));
        for(int i=0; i<6; i++){
            animations[i]->setDuration(DURATION);
            animations[i]->start(QAbstractAnimation::DeleteWhenStopped);
        }
    }
    else if(value == "Invalid code"){
        labelError->setText("Invalid confirmation code");
        emit errorHasOccured();
    }
}

void AuthWindow::recoveryNewPassReceived(QString value){
    timerWaitingAnswer->stop();
    if(value == "Password changed successfully"){
        labelSuccess->setText("Your password has been changed succesfully");

        location=LOC_SIGNIN;
        lineLog->setEnabledOverride();
        preloader->close();
        labelSignIn->close();

        QPropertyAnimation *animations[5];
        animations[0] = new QPropertyAnimation(lineRecoveryConfirmPass, "pos");
        animations[1] = new QPropertyAnimation(buttonSignIn, "pos");
        animations[2] = new QPropertyAnimation(labelSignUp, "pos");
        animations[3] = new QPropertyAnimation(labelForgotPass, "pos");
        animations[4] = new QPropertyAnimation(opacityLabel, "opacity");

        animations[0]->setEndValue(QPoint(width(), lineRecoveryConfirmPass->y()));
        animations[1]->setStartValue(QPoint(defaultButtonX, height()));
        animations[1]->setEndValue(QPoint(defaultButtonX, defaultY+(2*lineHWithSpace)));
        animations[2]->setStartValue(QPoint(defaultLineX+lineW-labelSignUp->width(), height()+buttonHWithSpace));
        animations[2]->setEndValue(QPoint(defaultLineX+lineW-labelSignUp->width(), defaultY+(2*lineHWithSpace)+buttonHWithSpace));
        animations[3]->setStartValue(QPoint(defaultLineX, height()+buttonHWithSpace));
        animations[3]->setEndValue(QPoint(defaultLineX, defaultY+(2*lineHWithSpace)+buttonHWithSpace));
        animations[4]->setStartValue(0.0);
        animations[4]->setEndValue(1.0);

        animations[0]->setDuration(DURATION);
        animations[1]->setDuration(DURATION);
        animations[2]->setDuration(DURATION);
        animations[3]->setDuration(DURATION);
        animations[4]->setDuration(DURATION);

        buttonSignIn->show();
        labelSignUp->show();
        labelForgotPass->show();
        labelPass->move(labelRecoveryPass->x(), labelRecoveryPass->y());
        labelRecoveryPass->close();
        lineRecoveryPass->clear();
        lineRecoveryConfirmPass->clear();
        labelPass->show();
        labelSuccess->show();

        connect(animations[0], SIGNAL(finished()), lineRecoveryConfirmPass, SLOT(close()));
        animations[0]->start(QAbstractAnimation::DeleteWhenStopped);
        animations[1]->start(QAbstractAnimation::DeleteWhenStopped);
        animations[2]->start(QAbstractAnimation::DeleteWhenStopped);
        animations[3]->start(QAbstractAnimation::DeleteWhenStopped);
        animations[4]->start(QAbstractAnimation::DeleteWhenStopped);

        timerLabelSuccess->start();
    }
    else if(value == "Password hasn't been changed"){
        //TODO
    }
}

void AuthWindow::labelAuthenticationChanging(){
    static quint8 dots = 0;
    QString text = "Authentication";
    for(int i=0; i<dots%4; i++)
        text += '.';
    dots++;
    labelAuthentication->setText(text);
}

void AuthWindow::tokensDead(){
    lineLog->show();
    linePass->show();
    labelSignUp->show();
    labelForgotPass->show();
    buttonSignIn->show();
    buttonEye->show();

    labelAuthentication->close();

    timerAuthentication->stop();

    gotoSignInLoc();
    errorHide();
    show();
}


void AuthWindow::startPreloading(){
    if(location == LOC_SIGNIN){
        buttonSignIn->setGraphicsEffect(opacity);

        QPropertyAnimation *animations[3];

        animations[0] = new QPropertyAnimation(labelSignUp, "pos");
        animations[0]->setDuration(DURATION);
        animations[0]->setEndValue(QPoint(labelSignUp->x(),this->height()));

        animations[1] = new QPropertyAnimation(labelForgotPass, "pos");
        animations[1]->setDuration(DURATION);
        animations[1]->setEndValue(QPoint(labelForgotPass->x(),this->height()));

        animations[2] = new QPropertyAnimation(opacity, "opacity");
        animations[2]->setDuration(DURATION/2);
        animations[2]->setEndValue(0.0);

        animations[0]->start(QAbstractAnimation::DeleteWhenStopped);
        animations[1]->start(QAbstractAnimation::DeleteWhenStopped);
        animations[2]->start(QAbstractAnimation::DeleteWhenStopped);

        preloader->move((width()-buttonSignIn->height())/2,buttonSignIn->y());

        lineLog->setDisabledOverride();
        labelPass->setDisabled(true);
        linePass->setDisabled(true);
        buttonEye->setDisabled(true);
        linePass->setStyleSheet(QString("AuthLineEdit{"
                                        "font-family: Century Gothic;"
                                        "font-size: %1px;"
                                        "background: transparent;"
                                        "border: 1px solid #cccccc;"
                                        "border-right: 0px;"
                                        "color: #B5EBEE;"
                                        "}").arg(defaultFontSize));
        buttonEye->setStyleSheet("border: 1px solid #cccccc; border-left: 0px;");

        connect(animations[2], SIGNAL(finished()), buttonSignIn, SLOT(close()));
    }
    else if(location==LOC_REGISTRATION){
        buttonSignUp->setGraphicsEffect(opacity);

        QPropertyAnimation *animations[2];

        animations[0] = new QPropertyAnimation(labelSignIn, "pos");
        animations[0]->setDuration(DURATION);
        animations[0]->setEndValue(QPoint(labelSignIn->x(),this->height()));

        animations[1] = new QPropertyAnimation(opacity, "opacity");
        animations[1]->setDuration(DURATION/2);
        animations[1]->setEndValue(0.0);

        animations[0]->start(QAbstractAnimation::DeleteWhenStopped);
        animations[1]->start(QAbstractAnimation::DeleteWhenStopped);

        preloader->move((width()-buttonSignUp->height())/2,buttonSignUp->y());
        lineEmail->setDisabledOverride();
        lineLog->setDisabledOverride();
        labelPass->setDisabled(true);
        linePass->setDisabled(true);
        buttonEye->setDisabled(true);
        linePass->setStyleSheet(QString("AuthLineEdit{"
                                        "font-family: Century Gothic;"
                                        "font-size: %1px;"
                                        "background: transparent;"
                                        "border: 1px solid #cccccc;"
                                        "border-right: 0px;"
                                        "color: #B5EBEE;"
                                        "}").arg(defaultFontSize));
        buttonEye->setStyleSheet("border: 1px solid #cccccc; border-left: 0px;");
        lineConfirmPass->setDisabledOverride();

        connect(animations[1], SIGNAL(finished()), buttonSignUp, SLOT(close()));
    }
    else if(location==LOC_REGISTRATION_CODE){
        preloader->move(preloader->x(), buttonSignUp->y());
        QPropertyAnimation *animations[3];
        animations[0] = new QPropertyAnimation(labelSignIn, "pos");
        animations[1] = new QPropertyAnimation(buttonSignUp, "pos");
        animations[2] = new QPropertyAnimation(lineConfirmCode, "pos");

        animations[0]->setDuration(DURATION);
        animations[0]->setEndValue(QPoint(labelSignIn->x(), height()));
        animations[0]->start(QAbstractAnimation::DeleteWhenStopped);

        animations[1]->setDuration(DURATION);
        animations[1]->setEndValue(QPoint(buttonSignUp->x(), height()));
        animations[1]->start(QAbstractAnimation::DeleteWhenStopped);

        animations[2]->setDuration(DURATION);
        animations[2]->setEndValue(QPoint(lineConfirmCode->x(), height()));
        animations[2]->start(QAbstractAnimation::DeleteWhenStopped);
    }
    else if(location==LOC_RECOVERY_EMAIL || location == LOC_RECOVERY_CODE || location == LOC_RECOVERY_PASS){
        buttonOk->setGraphicsEffect(opacity);
        QPropertyAnimation *animations[3];

        animations[0] = new QPropertyAnimation(labelSignUp, "pos");
        animations[0]->setDuration(DURATION);
        animations[0]->setEndValue(QPoint(labelSignUp->x(),this->height()));

        animations[1] = new QPropertyAnimation(labelSignIn, "pos");
        animations[1]->setDuration(DURATION);
        animations[1]->setEndValue(QPoint(labelSignIn->x(),this->height()));

        animations[2] = new QPropertyAnimation(opacity, "opacity");
        animations[2]->setDuration(DURATION/2);
        animations[2]->setEndValue(0.0);

        animations[0]->start(QAbstractAnimation::DeleteWhenStopped);
        animations[1]->start(QAbstractAnimation::DeleteWhenStopped);
        animations[2]->start(QAbstractAnimation::DeleteWhenStopped);

        preloader->move((width()-buttonOk->height())/2,buttonOk->y());
        lineLog->setDisabledOverride();

        connect(animations[2], SIGNAL(finished()), buttonOk, SLOT(close()));
    }
    preloader->show();
}

void AuthWindow::cancelPreloading(){
    preloader->close();

    if(location == LOC_SIGNIN){
        buttonSignIn->show();
        buttonSignIn->setGraphicsEffect(opacity);

        QPropertyAnimation *animations[3];

        animations[0] = new QPropertyAnimation(labelSignUp, "pos");
        animations[0]->setDuration(DURATION);
        animations[0]->setEndValue(QPoint(labelSignUp->x(), defaultY+(2*lineHWithSpace)+buttonHWithSpace));

        animations[1] = new QPropertyAnimation(labelForgotPass, "pos");
        animations[1]->setDuration(DURATION);
        animations[1]->setEndValue(QPoint(labelForgotPass->x(), defaultY+(2*lineHWithSpace)+buttonHWithSpace));

        animations[2] = new QPropertyAnimation(opacity, "opacity");
        animations[2]->setDuration(DURATION);
        animations[2]->setEndValue(1);

        animations[0]->start(QAbstractAnimation::DeleteWhenStopped);
        animations[1]->start(QAbstractAnimation::DeleteWhenStopped);
        animations[2]->start(QAbstractAnimation::DeleteWhenStopped);

        lineLog->setEnabledOverride();
        setPassEnabled();
    }
    else if(location==LOC_REGISTRATION){
        buttonSignUp->show();
        buttonSignUp->setGraphicsEffect(opacity);

        QPropertyAnimation *animations[2];
        animations[0] = new QPropertyAnimation(labelSignIn, "pos");

        animations[0]->setDuration(DURATION);
        animations[0]->setEndValue(QPoint(labelSignIn->x(), defaultY+(3*lineHWithSpace)+buttonHWithSpace));
        animations[0]->start(QAbstractAnimation::DeleteWhenStopped);

        animations[1] = new QPropertyAnimation(opacity, "opacity");
        animations[1]->setDuration(DURATION);
        animations[1]->setEndValue(1);
        animations[1]->start(QAbstractAnimation::DeleteWhenStopped);


        lineEmail->setEnabledOverride();
        lineLog->setEnabledOverride();
        setPassEnabled();
        lineConfirmPass->setEnabledOverride();
        if(labelError->text() == "Email already exists")
            lineEmail->setFocus();
    }
    else if(location==LOC_REGISTRATION_CODE){
        lineConfirmCode->setEnabledOverride();
        QPropertyAnimation *animations[3];
        animations[0] = new QPropertyAnimation(lineConfirmCode, "pos");
        animations[1] = new QPropertyAnimation(buttonSignUp, "pos");
        animations[2] = new QPropertyAnimation(labelSignIn, "pos");

        animations[0]->setDuration(DURATION);
        animations[0]->setEndValue(QPoint(defaultLineX, defaultY+lineHWithSpace));
        animations[0]->start(QAbstractAnimation::DeleteWhenStopped);

        animations[1]->setDuration(DURATION);
        animations[1]->setEndValue(QPoint(defaultButtonX, defaultY+(2*lineHWithSpace)));
        animations[1]->start(QAbstractAnimation::DeleteWhenStopped);

        animations[2]->setDuration(DURATION);
        animations[2]->setEndValue(QPoint(defaultLineX+lineW-labelSignIn->width(), defaultY+(2*lineHWithSpace)+buttonHWithSpace));
        animations[2]->start(QAbstractAnimation::DeleteWhenStopped);
    }
    else if(location==LOC_RECOVERY_EMAIL){
        buttonOk->show();
        buttonOk->setGraphicsEffect(opacity);

        QPropertyAnimation *animations[3];

        animations[0] = new QPropertyAnimation(labelSignUp, "pos");
        animations[0]->setDuration(DURATION);
        animations[0]->setEndValue(QPoint(labelSignUp->x(), defaultY+lineHWithSpace+buttonHWithSpace));

        animations[1] = new QPropertyAnimation(labelSignIn, "pos");
        animations[1]->setDuration(DURATION);
        animations[1]->setEndValue(QPoint(labelSignIn->x(), defaultY+lineHWithSpace+buttonHWithSpace));

        animations[2] = new QPropertyAnimation(opacity, "opacity");
        animations[2]->setDuration(DURATION);
        animations[2]->setEndValue(1);

        animations[0]->start(QAbstractAnimation::DeleteWhenStopped);
        animations[1]->start(QAbstractAnimation::DeleteWhenStopped);
        animations[2]->start(QAbstractAnimation::DeleteWhenStopped);

        lineLog->setEnabledOverride();
    }
    else if(location==LOC_RECOVERY_CODE){
        buttonOk->show();
        buttonOk->setGraphicsEffect(opacity);

        lineConfirmCode->setEnabledOverride();
        QPropertyAnimation *animations[3];

        animations[0] = new QPropertyAnimation(labelSignUp, "pos");
        animations[0]->setDuration(DURATION);
        animations[0]->setEndValue(QPoint(labelSignUp->x(), defaultY+(2*lineHWithSpace)+buttonHWithSpace));

        animations[1] = new QPropertyAnimation(labelSignIn, "pos");
        animations[1]->setDuration(DURATION);
        animations[1]->setEndValue(QPoint(labelSignIn->x(), defaultY+(2*lineHWithSpace)+buttonHWithSpace));

        animations[2] = new QPropertyAnimation(opacity, "opacity");
        animations[2]->setDuration(DURATION);
        animations[2]->setEndValue(1);

        animations[0]->start(QAbstractAnimation::DeleteWhenStopped);
        animations[1]->start(QAbstractAnimation::DeleteWhenStopped);
        animations[2]->start(QAbstractAnimation::DeleteWhenStopped);

    }
    else if(location==LOC_RECOVERY_PASS){
        buttonOk->show();
        buttonOk->setGraphicsEffect(opacity);

        labelRecoveryPass->setEnabled(true);
        lineRecoveryPass->setEnabled(true);
        buttonRecoveryEye->setEnabled(true);
        lineRecoveryPass->setStyleSheet(QString("AuthLineEdit{"
                                                "font-family: Century Gothic;"
                                                "font-size: %1px;"
                                                "background: transparent;"
                                                "border: 1px solid gray;"
                                                "border-right: 0px;"
                                                "color: #B5EBEE;"
                                                "}").arg(defaultFontSize));
        buttonRecoveryEye->setStyleSheet("QPushButton{"
                                         "background: transparent;"
                                         "border: 1px solid gray;"
                                         "border-left: 0px;"
                                         "}");


        lineRecoveryConfirmPass->setEnabledOverride();
        QPropertyAnimation *animations[3];

        animations[0] = new QPropertyAnimation(labelSignUp, "pos");
        animations[0]->setDuration(DURATION);
        animations[0]->setEndValue(QPoint(labelSignUp->x(), defaultY+(3*lineHWithSpace)+buttonHWithSpace));

        animations[1] = new QPropertyAnimation(labelSignIn, "pos");
        animations[1]->setDuration(DURATION);
        animations[1]->setEndValue(QPoint(labelSignIn->x(), defaultY+(3*lineHWithSpace)+buttonHWithSpace));

        animations[2] = new QPropertyAnimation(opacity, "opacity");
        animations[2]->setDuration(DURATION);
        animations[2]->setEndValue(1);

        animations[0]->start(QAbstractAnimation::DeleteWhenStopped);
        animations[1]->start(QAbstractAnimation::DeleteWhenStopped);
        animations[2]->start(QAbstractAnimation::DeleteWhenStopped);
    }

    labelErrorBackground->show();
    QPropertyAnimation *animation = new QPropertyAnimation(labelErrorBackground, "pos");
    animation->setDuration(DURATION*2);
    animation->setEndValue(QPoint(0,labelErrorBackground->y()));
    animation->start(QAbstractAnimation::DeleteWhenStopped);
    timerErrorLabel->start();
}


void AuthWindow::changingPassEchoMode(){
    linePass->setFocus();
    if(linePass->echoMode()==QLineEdit::Password){
        linePass->setEchoMode(QLineEdit::Normal);
        lineConfirmPass->setEchoMode(QLineEdit::Normal);
    }
    else{
        linePass->setEchoMode(QLineEdit::Password);
        lineConfirmPass->setEchoMode(QLineEdit::Password);
    }
}

void AuthWindow::changingRecoveryPassEchoMode(){
    lineConfirmPass->setFocus();
    if(lineRecoveryPass->echoMode()==QLineEdit::Password){
        lineRecoveryPass->setEchoMode(QLineEdit::Normal);
        lineRecoveryConfirmPass->setEchoMode(QLineEdit::Normal);
    }
    else{
        lineRecoveryPass->setEchoMode(QLineEdit::Password);
        lineRecoveryConfirmPass->setEchoMode(QLineEdit::Password);
    }
}

void AuthWindow::changingPassBorder(){
    isPassEmpty=false;

    linePass->setStyleSheet(QString("AuthLineEdit{"
                                    "font-family: Century Gothic;"
                                    "font-size: %1px;"
                                    "background: transparent;"
                                    "border: 1px solid gray;"
                                    "border-right: 0px;"
                                    "color: #B5EBEE;"
                                    "}").arg(defaultFontSize));
    buttonEye->setStyleSheet("QPushButton{"
                             "background: transparent;"
                             "border: 1px solid gray;"
                             "border-left: 0px;"
                             "}");
}

void AuthWindow::changingRecoveryPassBorder(){
    isRecoveryPassEmpty = false;
    lineRecoveryPass->setStyleSheet(QString("AuthLineEdit{"
                                            "font-family: Century Gothic;"
                                            "font-size: %1px;"
                                            "background: transparent;"
                                            "border: 1px solid #0078d7;"
                                            "border-right: 0px;"
                                            "color: #B5EBEE;"
                                            "}").arg(defaultFontSize));
    buttonRecoveryEye->setStyleSheet("QPushButton{"
                                     "background: transparent;"
                                     "border: 1px solid #0078d7;"
                                     "border-left: 0px;"
                                     "}");
}

void AuthWindow::changingStateOfNicknameExist(){
    labelUncorrectNickname->close();
    nicknameExists = false;
}


void AuthWindow::gotoRecoveryLoc(){
    lineConfirmCode->setEnabledOverride();
    lineConfirmCode->clear();
    opacity->setOpacity(1.0);
    location=LOC_RECOVERY_EMAIL;
    lineLog->setFocus();
    isRecoveryPassEmpty=false;
    lineLog->setValidator(new QRegExpValidator(QRegExp("([^@]){,32}(@?)([^@]){,12}")));
    lineLog->setDefaultStyleSheet();
    linePass->setStyleSheet(QString("AuthLineEdit{"
                                    "font-family: Century Gothic;"
                                    "font-size: %1px;"
                                    "background: transparent;"
                                    "border: 1px solid gray;"
                                    "border-right: 0px;"
                                    "color: #B5EBEE;"
                                    "}").arg(defaultFontSize));
    buttonEye->setStyleSheet("QPushButton{"
                             "background: transparent;"
                             "border: 1px solid gray;"
                             "border-left: 0px;"
                             "}");

    QPropertyAnimation *animations[5];

    animations[0] = new QPropertyAnimation(labelForgotPass, "pos");
    animations[1] = new QPropertyAnimation(buttonSignIn, "pos");
    animations[2] = new QPropertyAnimation(labelSignIn, "pos");
    animations[3] = new QPropertyAnimation(labelSignUp, "pos");
    animations[4] = new QPropertyAnimation(labelPass, "pos");

    animations[0]->setEndValue(QPoint(-lineW, labelForgotPass->y()));
    animations[1]->setEndValue(QPoint(buttonSignIn->x(), defaultY+lineHWithSpace));
    animations[2]->setStartValue(QPoint(defaultLineX, height()));
    animations[2]->setEndValue(QPoint(defaultLineX, defaultY+lineHWithSpace+buttonHWithSpace));
    animations[3]->setEndValue(QPoint(labelSignUp->x(), defaultY+lineHWithSpace+buttonHWithSpace));
    animations[4]->setEndValue(QPoint(-lineW, labelPass->y()));

    labelSignIn->setAlignment(Qt::AlignLeft | Qt::AlignTop);
    labelSignIn->show();
    for(int i=0;i<5;i++){
        animations[i]->setDuration(DURATION);
        animations[i]->start(QAbstractAnimation::DeleteWhenStopped);
    }

    buttonOk->move(defaultButtonX, defaultY+lineHWithSpace);
    connect(animations[1], SIGNAL(finished()), buttonOk, SLOT(show()));
    connect(animations[1], SIGNAL(finished()), buttonSignIn, SLOT(close()));
}

void AuthWindow::gotoSignUpLoc(){
    lineLog->clear();
    linePass->clear();
    lineEmail->clear();
    lineConfirmPass->clear();
    lineLog->setEnabledOverride();
    lineEmail->setEnabledOverride();
    lineConfirmPass->setEnabledOverride();
    lineEmail->setFocus();
    isPassEmpty=false;

    lineLog->setPlaceholderText("Nickname");
    lineLog->setValidator(new QRegExpValidator(QRegExp("^(\\d|\\w|[_.]){3,12}$")));

    lineConfirmPass->show();
    lineEmail->show();
    if(location==LOC_RECOVERY_EMAIL){
        labelSignIn->close();

        lineLog->setDefaultStyleSheet();
        lineConfirmCode->setDefaultStyleSheet();

        QPropertyAnimation *localAnimations[5];
        localAnimations[0] = new QPropertyAnimation(labelPass, "pos");
        localAnimations[1] = new QPropertyAnimation(buttonOk, "pos");
        localAnimations[2] = new QPropertyAnimation(lineConfirmPass, "pos");
        localAnimations[3] = new QPropertyAnimation(lineEmail, "pos");
        localAnimations[4] = new QPropertyAnimation(labelSignUp, "pos");


        localAnimations[0]->setDuration(DURATION);
        localAnimations[0]->setEndValue(QPoint(defaultLineX, labelPass->y()));
        localAnimations[0]->start(QAbstractAnimation::DeleteWhenStopped);

        localAnimations[1]->setDuration(DURATION);
        localAnimations[1]->setEndValue(QPoint(buttonOk->x(), defaultY+(3*lineHWithSpace)));
        localAnimations[1]->start(QAbstractAnimation::DeleteWhenStopped);

        localAnimations[2]->setDuration(DURATION);
        localAnimations[2]->setEndValue(QPoint(defaultLineX, lineConfirmPass->y()));
        localAnimations[2]->start(QAbstractAnimation::DeleteWhenStopped);

        localAnimations[3]->setDuration(DURATION);
        localAnimations[3]->setEndValue(QPoint(defaultLineX, lineEmail->y()));
        localAnimations[3]->start(QAbstractAnimation::DeleteWhenStopped);

        localAnimations[4]->setDuration(DURATION);
        localAnimations[4]->setEndValue(QPoint(labelSignUp->x(), defaultY+(3*lineHWithSpace)+buttonHWithSpace));
        localAnimations[4]->start(QAbstractAnimation::DeleteWhenStopped);

        labelSignIn->move(labelSignUp->x(), defaultY+(3*lineHWithSpace)+buttonHWithSpace);
        labelSignIn->setAlignment(Qt::AlignRight | Qt::AlignTop);
        buttonSignUp->move(buttonOk->x(), labelSignUp->y() + labelSignUp->height() + height()/26);
        buttonSignIn->move(width(), buttonSignIn->y());
        connect(localAnimations[1], SIGNAL(finished()), buttonOk, SLOT(close()));
        connect(localAnimations[1], SIGNAL(finished()), buttonSignUp, SLOT(show()));
        connect(localAnimations[4], SIGNAL(finished()), labelSignUp, SLOT(close()));
        connect(localAnimations[4], SIGNAL(finished()), labelSignIn, SLOT(show()));
    }
    else if(location==LOC_RECOVERY_CODE){
        QPropertyAnimation *animations[6];
        animations[0] = new QPropertyAnimation(lineEmail, "pos");
        animations[1] = new QPropertyAnimation(lineConfirmCode, "pos");
        animations[2] = new QPropertyAnimation(labelPass, "pos");
        animations[3] = new QPropertyAnimation(buttonOk, "pos");
        animations[4] = new QPropertyAnimation(lineConfirmPass, "pos");
        animations[5] = new QPropertyAnimation(labelSignUp, "pos");

        animations[0]->setStartValue(QPoint(-lineW, defaultY-lineHWithSpace));
        animations[0]->setEndValue(QPoint(defaultLineX, defaultY-lineHWithSpace));
        animations[1]->setEndValue(QPoint(width(), lineConfirmCode->y()));
        animations[2]->setStartValue(QPoint(-lineW, defaultY+lineHWithSpace));
        animations[2]->setEndValue(QPoint(defaultLineX, defaultY+lineHWithSpace));
        animations[3]->setEndValue(QPoint(defaultButtonX, defaultY+(3*lineHWithSpace)));
        animations[4]->setStartValue(QPoint(-lineW, defaultY+(2*lineHWithSpace)));
        animations[4]->setEndValue(QPoint(defaultLineX, defaultY+(2*lineHWithSpace)));
        animations[5]->setEndValue(QPoint(labelSignUp->x(), defaultY+(3*lineHWithSpace)+buttonHWithSpace));

        for(int i=0; i<6; i++){
            animations[i]->setDuration(DURATION);
            animations[i]->start(QAbstractAnimation::DeleteWhenStopped);
        }
        labelSignIn->close();
        connect(animations[3], SIGNAL(finished()), buttonOk, SLOT(close()));
        buttonSignUp->move(defaultButtonX, defaultY+(3*lineHWithSpace));
        connect(animations[3], SIGNAL(finished()), buttonSignUp, SLOT(show()));
        connect(animations[5], SIGNAL(finished()), labelSignUp, SLOT(close()));
        labelSignIn->move(labelSignUp->x(), defaultY+(3*lineHWithSpace)+buttonHWithSpace);
        labelSignIn->setAlignment(Qt::AlignRight | Qt::AlignTop);
        connect(animations[5], SIGNAL(finished()), labelSignIn, SLOT(show()));
    }
    else if(location==LOC_RECOVERY_PASS){
        QPropertyAnimation *animations[3];
        animations[0] = new QPropertyAnimation(lineEmail, "pos");
        animations[1] = new QPropertyAnimation(labelSignUp, "pos");
        animations[2] = new QPropertyAnimation(labelSignIn, "pos");

        animations[0]->setDuration(DURATION);
        animations[0]->setStartValue(QPoint(-lineW, defaultY-lineHWithSpace));
        animations[0]->setEndValue(QPoint(defaultLineX, defaultY-lineHWithSpace));
        animations[0]->start(QAbstractAnimation::DeleteWhenStopped);

        connect(animations[1], SIGNAL(finished()), labelSignUp, SLOT(close()));
        animations[1]->setDuration(DURATION);
        animations[1]->setEndValue(QPoint(width(), labelSignUp->y()));
        animations[1]->start(QAbstractAnimation::DeleteWhenStopped);

        animations[2]->setDuration(DURATION);
        animations[2]->setEndValue(QPoint(defaultLineX+lineW-labelSignIn->width(), labelSignIn->y()));
        animations[2]->start(QAbstractAnimation::DeleteWhenStopped);
        labelSignIn->setAlignment(Qt::AlignRight | Qt::AlignTop);
        labelRecoveryPass->close();
        labelPass->move(labelRecoveryPass->x(), labelRecoveryPass->y());
        labelPass->show();
        lineRecoveryConfirmPass->close();
        lineConfirmPass->move(lineRecoveryConfirmPass->x(), lineRecoveryConfirmPass->y());
        lineConfirmPass->show();
        buttonOk->close();
        buttonSignUp->move(buttonOk->x(), buttonOk->y());
        buttonSignUp->show();
    }
    else if(location==LOC_SIGNIN){
        lineLog->setDefaultStyleSheet();
        linePass->setStyleSheet(QString("AuthLineEdit{"
                                        "font-family: Century Gothic;"
                                        "font-size: %1px;"
                                        "background: transparent;"
                                        "border: 1px solid gray;"
                                        "border-right: 0px;"
                                        "color: #B5EBEE;"
                                        "}").arg(defaultFontSize));
        buttonEye->setStyleSheet("QPushButton{"
                                 "background: transparent;"
                                 "border: 1px solid gray;"
                                 "border-left: 0px;"
                                 "}");

        QPropertyAnimation *localAnimations[6];
        localAnimations[0] = new QPropertyAnimation(buttonSignUp, "pos");
        localAnimations[1] = new QPropertyAnimation(buttonSignIn, "pos");
        localAnimations[2] = new QPropertyAnimation(labelForgotPass, "pos");
        localAnimations[3] = new QPropertyAnimation(lineConfirmPass, "pos");
        localAnimations[4] = new QPropertyAnimation(lineEmail, "pos");
        localAnimations[5] = new QPropertyAnimation(labelSignUp, "pos");

        localAnimations[0]->setStartValue(QPoint(width(), defaultY+(3*lineHWithSpace)));
        localAnimations[0]->setEndValue(QPoint(defaultButtonX, defaultY+(3*lineHWithSpace)));
        localAnimations[1]->setEndValue(QPoint(width(), buttonSignIn->y()));
        localAnimations[2]->setEndValue(QPoint(-labelForgotPass->width(), labelForgotPass->y()));
        localAnimations[3]->setStartValue(QPoint(-lineW, lineConfirmPass->y()));
        localAnimations[3]->setEndValue(QPoint(defaultLineX, lineConfirmPass->y()));
        localAnimations[4]->setStartValue(QPoint(-lineW, lineEmail->y()));
        localAnimations[4]->setEndValue(QPoint(defaultLineX, lineEmail->y()));
        localAnimations[5]->setEndValue(QPoint(labelSignUp->x(), defaultY+(3*lineHWithSpace)+buttonHWithSpace));
        labelSignIn->move(labelSignUp->x(), defaultY+(3*lineHWithSpace)+buttonHWithSpace);

        for(int i=0;i<6;i++){
            localAnimations[i]->setDuration(DURATION);
            localAnimations[i]->start(QAbstractAnimation::DeleteWhenStopped);
        }

        buttonSignUp->show();


        labelSignIn->setAlignment(Qt::AlignRight | Qt::AlignTop);
        connect(localAnimations[5], SIGNAL(finished()), labelSignUp, SLOT(close()));
        connect(localAnimations[5], SIGNAL(finished()), labelSignIn, SLOT(show()));

    }

    location=LOC_REGISTRATION;
}

void AuthWindow::gotoSignInLoc(){
    lineLog->clear();
    linePass->clear();
    lineEmail->clear();
    lineConfirmPass->clear();
    lineLog->setEnabledOverride();
    lineLog->setFocus();
    isPassEmpty=false;
    setPassEnabled();
    lineLog->setValidator(new QRegExpValidator(QRegExp("([^@]){,32}(@?)([^@]){,12}")));

    lineEmail->setDefaultStyleSheet();
    lineLog->setDefaultStyleSheet();
    lineConfirmPass->setDefaultStyleSheet();
    linePass->setStyleSheet(QString("AuthLineEdit{"
                                    "font-family: Century Gothic;"
                                    "font-size: %1px;"
                                    "background: transparent;"
                                    "border: 1px solid gray;"
                                    "border-right: 0px;"
                                    "color: #B5EBEE;"
                                    "}").arg(defaultFontSize));
    lineConfirmCode->setDefaultStyleSheet();

    lineLog->setValidator(new QRegExpValidator(QRegExp("([^@])+(@?)([^@])+")));
    buttonSignIn->show();

    if(location==LOC_RECOVERY_EMAIL){
        QPropertyAnimation *localAnimations[5];
        localAnimations[0] = new QPropertyAnimation(buttonOk,"pos");
        localAnimations[1] = new QPropertyAnimation(labelPass,"pos");
        localAnimations[2] = new QPropertyAnimation(labelSignUp, "pos");
        localAnimations[3] = new QPropertyAnimation(buttonSignIn, "pos");

        localAnimations[0]->setDuration(DURATION);
        localAnimations[0]->setEndValue(QPoint(width(), buttonOk->y()));
        localAnimations[0]->start(QAbstractAnimation::DeleteWhenStopped);

        localAnimations[1]->setDuration(DURATION);
        localAnimations[1]->setEndValue(QPoint(defaultLineX,labelPass->y()));
        localAnimations[1]->start(QAbstractAnimation::DeleteWhenStopped);

        localAnimations[2]->setDuration(DURATION);
        localAnimations[2]->setEndValue(QPoint(labelSignUp->x(), defaultY+(2*lineHWithSpace)+buttonHWithSpace));
        localAnimations[2]->start(QAbstractAnimation::DeleteWhenStopped);

        localAnimations[3]->setDuration(DURATION);
        localAnimations[3]->setStartValue(QPoint(-buttonW, defaultY+(2*lineHWithSpace)));
        localAnimations[3]->setEndValue(QPoint(defaultButtonX, defaultY+(2*lineHWithSpace)));
        localAnimations[3]->start(QAbstractAnimation::DeleteWhenStopped);

        localAnimations[4] = new QPropertyAnimation(labelForgotPass, "pos");
        localAnimations[4]->setEndValue(QPoint(defaultLineX, defaultY+(2*lineHWithSpace)+buttonHWithSpace));
        localAnimations[4]->start(QAbstractAnimation::DeleteWhenStopped);

        labelSignIn->close();
        connect(localAnimations[0], SIGNAL(finished()), buttonOk, SLOT(close()));

    }
    else if(location==LOC_REGISTRATION || location == LOC_AUTHENTICATION){
        QPropertyAnimation *animations[6];

        animations[0] = new QPropertyAnimation(labelForgotPass, "pos");
        animations[1] = new QPropertyAnimation(buttonSignIn, "pos");
        animations[2] = new QPropertyAnimation(lineConfirmPass, "pos");
        animations[3] = new QPropertyAnimation(lineEmail, "pos");
        animations[4] = new QPropertyAnimation(buttonSignUp, "pos");
        animations[5] = new QPropertyAnimation(labelSignIn, "pos");

        animations[0]->setEndValue(QPoint(defaultLineX, defaultY+(2*lineHWithSpace)+buttonHWithSpace));
        animations[1]->setStartValue(QPoint(width(), defaultY+(2*lineHWithSpace)));
        animations[1]->setEndValue(QPoint(defaultButtonX, defaultY+(2*lineHWithSpace)));
        animations[2]->setEndValue(QPoint(-lineW, lineConfirmPass->y()));
        animations[3]->setEndValue(QPoint(-lineW, lineEmail->y()));
        animations[4]->setEndValue(QPoint(width(), buttonSignUp->y()));
        animations[5]->setEndValue(QPoint(labelSignIn->x(), defaultY+(2*lineHWithSpace)+buttonHWithSpace));

        nicknameExists=false;
        lineLog->setPlaceholderText("Login or email");
        labelSignUp->move(defaultLineX+lineW-labelSignUp->width(), defaultY+(2*lineHWithSpace)+buttonHWithSpace);
        connect(animations[5],SIGNAL(finished()), labelSignIn, SLOT(close()));
        connect(animations[5],SIGNAL(finished()), labelSignUp, SLOT(show()));
        connect(animations[4], SIGNAL(finished()), buttonSignUp, SLOT(close()));

        for(int i=0;i<6;i++){
            animations[i]->setDuration(DURATION);
            animations[i]->start(QAbstractAnimation::DeleteWhenStopped);
        }
    }
    else if(location==LOC_REGISTRATION_CODE){
        QPropertyAnimation *animations[2];
        animations[0] = new QPropertyAnimation(lineEmail, "pos");
        animations[1] = new QPropertyAnimation(labelForgotPass, "pos");

        animations[0]->setDuration(DURATION);
        animations[0]->setEndValue(QPoint(width(), lineEmail->y()));
        animations[0]->start(QAbstractAnimation::DeleteWhenStopped);

        animations[1]->setDuration(DURATION);
        animations[1]->setStartValue(QPoint(-labelForgotPass->width(), defaultY+(2*lineHWithSpace)+buttonHWithSpace));
        animations[1]->setEndValue(QPoint(defaultLineX, defaultY+(2*lineHWithSpace)+buttonHWithSpace));
        animations[1]->start(QAbstractAnimation::DeleteWhenStopped);

        buttonSignUp->close();
        buttonSignIn->move(buttonSignUp->x(), buttonSignUp->y());
        buttonSignIn->show();
        lineConfirmCode->clear();
        lineConfirmCode->close();
        labelPass->move(lineConfirmCode->x(), lineConfirmCode->y());
        labelPass->show();
        labelSignIn->close();
        labelSignUp->move(labelSignIn->x(), labelSignIn->y());
        labelSignUp->show();
    }
    else if(location==LOC_RECOVERY_CODE){
        QPropertyAnimation *animations[4];
        animations[0] = new QPropertyAnimation(lineConfirmCode, "pos");
        animations[1] = new QPropertyAnimation(labelPass, "pos");
        animations[2] = new QPropertyAnimation(labelSignIn, "pos");
        animations[3] = new QPropertyAnimation(labelForgotPass, "pos");

        animations[0]->setDuration(DURATION);
        animations[0]->setEndValue(QPoint(width(), lineConfirmCode->y()));

        animations[1]->setDuration(DURATION);
        animations[1]->setStartValue(QPoint(-lineW, defaultY+lineHWithSpace));
        animations[1]->setEndValue(QPoint(defaultLineX, defaultY+lineHWithSpace));

        animations[2]->setDuration(DURATION);
        animations[2]->setEndValue(QPoint(-labelSignIn->width(), labelSignIn->y()));

        animations[3]->setDuration(DURATION);
        animations[3]->setStartValue(QPoint(-labelForgotPass->width(), defaultY+(2*lineHWithSpace)+buttonHWithSpace));
        animations[3]->setEndValue(QPoint(defaultLineX, defaultY+(2*lineHWithSpace)+buttonHWithSpace));

        connect(animations[2], SIGNAL(finished()), labelSignIn, SLOT(close()));
        animations[0]->start(QAbstractAnimation::DeleteWhenStopped);
        animations[1]->start(QAbstractAnimation::DeleteWhenStopped);
        animations[2]->start(QAbstractAnimation::DeleteWhenStopped);
        animations[3]->start(QAbstractAnimation::DeleteWhenStopped);

        buttonSignIn->move(buttonOk->x(), buttonOk->y());
        buttonOk->close();
    }
    else if(location==LOC_RECOVERY_PASS){
        buttonSignIn->close();
        QPropertyAnimation *animations[5];
        animations[0] = new QPropertyAnimation(lineRecoveryConfirmPass, "pos");
        animations[1] = new QPropertyAnimation(buttonOk, "pos");
        animations[2] = new QPropertyAnimation(labelSignUp, "pos");
        animations[3] = new QPropertyAnimation(labelSignIn, "pos");
        animations[4] = new QPropertyAnimation(labelForgotPass, "pos");

        animations[0]->setDuration(DURATION);
        animations[0]->setEndValue(QPoint(width(), lineRecoveryConfirmPass->y()));

        animations[1]->setDuration(DURATION);
        animations[1]->setEndValue(QPoint(defaultButtonX, defaultY+(2*lineHWithSpace)));

        animations[2]->setDuration(DURATION);
        animations[2]->setEndValue(QPoint(labelSignUp->x(), defaultY+(2*lineHWithSpace)+buttonHWithSpace));

        animations[3]->setDuration(DURATION);
        animations[3]->setEndValue(QPoint(-labelSignIn->width(), labelSignIn->y()));

        animations[4]->setDuration(DURATION);
        animations[4]->setEndValue(QPoint(defaultLineX, defaultY+(2*lineHWithSpace)+buttonHWithSpace));

        buttonSignIn->move(defaultButtonX, defaultY+(2*lineHWithSpace));
        labelRecoveryPass->close();
        labelPass->move(labelRecoveryPass->x(), labelRecoveryPass->y());
        labelPass->show();
        connect(animations[1], SIGNAL(finished()), buttonOk, SLOT(close()));
        connect(animations[1], SIGNAL(finished()), buttonSignIn, SLOT(show()));
        connect(animations[3], SIGNAL(finished()), labelSignIn, SLOT(close()));
        animations[0]->start(QAbstractAnimation::DeleteWhenStopped);
        animations[1]->start(QAbstractAnimation::DeleteWhenStopped);
        animations[2]->start(QAbstractAnimation::DeleteWhenStopped);
        animations[3]->start(QAbstractAnimation::DeleteWhenStopped);
        animations[4]->start(QAbstractAnimation::DeleteWhenStopped);
    }

    location = LOC_SIGNIN;
}


void AuthWindow::checkingNickname(){
    if(location==LOC_REGISTRATION && lineLog->text()!=""){
        QJsonObject request;
        request.insert("Target", "DoesNicknameExist");
        request.insert("Nickname", lineLog->text());

        TCPClient::getInstance().send(QJsonDocument(request).toJson());
    }
}

void AuthWindow::checkingConfirming(QString){
    if(lineConfirmPass->text()=="")
        lineConfirmPass->setDefaultStyleSheet();
    else if(lineConfirmPass->text()!=linePass->text())
        lineConfirmPass->setErrorStyleSheet();
    else
        lineConfirmPass->setDefaultStyleSheet();
}

void AuthWindow::checkingRecoveryConfirming(QString){
    if(lineRecoveryConfirmPass->text()=="")
        lineRecoveryConfirmPass->setDefaultStyleSheet();
    else if(lineRecoveryConfirmPass->text()!=lineRecoveryPass->text())
        lineRecoveryConfirmPass->setErrorStyleSheet();
    else
        lineRecoveryConfirmPass->setDefaultStyleSheet();
}


void AuthWindow::waitingAnswer(){
    labelError->setText("Server is not available");
    emit errorHasOccured();
}


void AuthWindow::errorHide(){
    timerLabelSuccess->stop();
    QPropertyAnimation *animation = new QPropertyAnimation(labelErrorBackground, "pos");
    animation->setDuration(DURATION*2);
    animation->setEndValue(QPoint(-labelErrorBackground->width(), labelErrorBackground->y()));
    animation->start(QAbstractAnimation::DeleteWhenStopped);
    connect(animation, SIGNAL(finished()), labelErrorBackground, SLOT(close()));
}

void AuthWindow::resizeAll(){
    quint16 windowSize = (QApplication::desktop()->width()/100)*25;

    if(QApplication::desktop()->width()<1366)
        windowSize=(1366/100)*25;
    else if(QApplication::desktop()->width()>7680)
        windowSize=(7680/100)*25;

    QImage(":/images/default.png").scaled(windowSize,windowSize).save("background.png");
    this->setFixedSize(windowSize, windowSize);

    lineW = (windowSize/13)*7;
    lineH = windowSize/13;
    lineHWithSpace = lineH + windowSize/26;
    buttonW = windowSize/52*15;
    buttonH = windowSize/52*5;
    buttonHWithSpace = buttonH + windowSize/26;
    defaultY = lineH * 4;
    defaultLineX = (windowSize - lineW)/2;
    defaultButtonX = (windowSize - buttonW)/2;

    quint16 buttonCloseW = windowSize/10;
    quint16 buttonCloseH = windowSize/16;
    quint16 buttonCloseX = windowSize - buttonCloseW;

    quint16 buttonMinimizeH = buttonCloseH;
    quint16 buttonMinimizeW = buttonCloseW;
    quint16 buttonMinimizeX = buttonCloseX - buttonMinimizeW;

    quint16 lineLogW = (windowSize/13)*7;
    quint16 lineLogH = windowSize/13;
    quint16 lineLogX = (windowSize - lineLogW)/2;
    quint16 lineLogY = lineLogH * 4;

    quint16 buttonSignInH = windowSize/52*5;

    quint16 labelSignUpW = (windowSize/26)*4;
    quint16 labelSignUpH = windowSize/13;

    quint16 labelForgotPassW = windowSize/26*9;
    quint16 labelForgotPassH = labelSignUpH;

    quint16 buttonEyeH = lineH;
    quint16 buttonEyeW = buttonEyeH;

    quint16 labelSignInW = labelSignUpW;
    quint16 labelSignInH = labelSignUpH;

    quint16 labelUncorrectNicknameX = lineLogX;
    quint16 labelUncorrectNicknameY = lineLogY - windowSize/26 - labelUncorrectNickname->height();

    quint16 preloaderH = buttonSignInH;
    quint16 preloaderW = preloaderH;

    quint16 labelConnectionFailedH = (windowSize/65)*6;
    quint16 labelConnectionFailedW = windowSize;

    quint16 labelConnectionFailedBackgroundH = (windowSize/65)*6;
    quint16 labelConnectionFailedBackgroundW = windowSize;
    quint16 labelConnectionFailedBackgroundY = windowSize - labelConnectionFailedBackgroundH;

    quint16 labelRegistrationSuccessfulH = windowSize/3;
    quint16 labelRegistrationSuccessfulW = windowSize;
    quint16 labelRegistrationSuccessfulX = 0;
    quint16 labelRegistrationSuccessfulY = windowSize/3;

    quint16 lineConfirmCodeH = lineH;
    quint16 lineConfirmCodeW = lineW;
    quint16 lineConfirmCodeX = lineLogX;
    quint16 lineConfirmCodeY = windowSize;

    lineEmail->setGeometry(-lineW, defaultY-lineHWithSpace, lineW, lineH);
    lineLog->setGeometry(defaultLineX, defaultY, lineW, lineH);
    linePass->setGeometry(0, 0, windowSize/13*6, lineH);
    lineConfirmPass->setGeometry(-lineW, (2*lineHWithSpace)+defaultY , lineW, lineH);
    lineRecoveryPass->setGeometry(0, 0, windowSize/13*6, lineH);
    lineRecoveryConfirmPass->setGeometry(defaultLineX, height()+lineHWithSpace, lineW, lineH);
    lineConfirmCode->setGeometry(lineConfirmCodeX, lineConfirmCodeY, lineConfirmCodeW, lineConfirmCodeH);

    buttonClose->setGeometry(buttonCloseX, 0, buttonCloseW, buttonCloseH);
    buttonMinimize->setGeometry(buttonMinimizeX, 0, buttonMinimizeW, buttonMinimizeH);
    buttonSignIn->setGeometry(defaultButtonX, (2*lineHWithSpace)+defaultY, buttonW, buttonH);
    buttonSignUp->setGeometry(defaultButtonX, defaultY+(3*lineHWithSpace), buttonW, buttonH);
    buttonOk->setGeometry(defaultButtonX, defaultY+lineHWithSpace, buttonW, buttonH);
    buttonEye->setGeometry(linePass->width(), 0, buttonEyeW, buttonEyeH);
    buttonEye->setIconSize(QSize(buttonEyeW, buttonEyeH));
    buttonRecoveryEye->setGeometry(lineRecoveryPass->width(), 0, buttonEyeW, buttonEyeH);
    buttonRecoveryEye->setIconSize(QSize(buttonEyeW, buttonEyeH));

    labelForgotPass->setGeometry(defaultLineX, 2*lineHWithSpace + buttonHWithSpace + defaultY, labelForgotPassW, labelForgotPassH);
    labelSignUp->setGeometry(defaultLineX+lineW-labelSignUpW, 2*lineHWithSpace + buttonHWithSpace + defaultY, labelSignUpW, labelSignUpH);
    labelSignIn->setGeometry(defaultLineX+lineW-labelSignInW , defaultY + (3*lineHWithSpace) + buttonHWithSpace, labelSignInW, labelSignInH);
    labelUncorrectNickname->move(labelUncorrectNicknameX, labelUncorrectNicknameY);
    labelErrorBackground->setGeometry(-labelConnectionFailedBackgroundW, labelConnectionFailedBackgroundY,labelConnectionFailedBackgroundW, labelConnectionFailedBackgroundH);
    labelError->setGeometry(0, 0, labelConnectionFailedW, labelConnectionFailedH);
    labelSuccess->setGeometry(labelRegistrationSuccessfulX,labelRegistrationSuccessfulY,labelRegistrationSuccessfulW, labelRegistrationSuccessfulH);
    labelPass->setGeometry(defaultLineX, defaultY+lineHWithSpace, lineW, lineH);
    labelRecoveryPass->setGeometry(defaultLineX, height(), lineW, lineH);

    labelAuthentication->setGeometry(windowSize/3, lineLogY+(lineLogH/2), windowSize, labelAuthentication->height());
    //labelAuthentication->setGeometry(lineLogX, lineLogY, lineLogW, lineLogH);

    preloader->resize(preloaderW, preloaderH);
}

void AuthWindow::mouseMoveEvent(QMouseEvent *event){
    if (mpos.x() >= 0 && event->buttons() && Qt::LeftButton){
        QPoint diff = event->pos() - mpos;
        QPoint newpos = this->pos() + diff;

        this->move(newpos);
    }
}

bool AuthWindow::isOnline(){
    QNetworkAccessManager nam;
    QNetworkRequest req(QUrl("http://www.google.com"));
    QNetworkReply *reply = nam.get(req);
    QEventLoop loop;
    connect(reply, SIGNAL(finished()), &loop, SLOT(quit()));
    loop.exec();

    return reply->bytesAvailable() ? true : false;
}

void AuthWindow::mousePressEvent(QMouseEvent *event){
    mpos = event->pos();
}

void AuthWindow::mouseReleaseEvent(QMouseEvent *){
    mpos = QPoint(-1, -1);
}


bool AuthWindow::eventFilter(QObject *target, QEvent *event){
    static bool inHover;

    if (target == buttonClose){
        if (event->type() == QEvent::HoverEnter)
            buttonClose->setIcon(QIcon(":images/close2.png"));
        else if(event->type() == QEvent::HoverLeave)
            buttonClose->setIcon(QIcon(":images/close1.png"));
    }
    else if(target == buttonMinimize){
        if (event->type() == QEvent::HoverEnter)
            buttonMinimize->setIcon(QIcon(":images/min2.png"));
        else if(event->type() == QEvent::HoverLeave)
            buttonMinimize->setIcon(QIcon(":images/min1.png"));
    }
    else if(target == lineLog){
        if(event->type() == QEvent::HoverEnter && location==LOC_REGISTRATION && nicknameExists){
            labelUncorrectNickname->show();
            inHover = true;
        }
        else if(event->type() == QEvent::HoverLeave && location==LOC_REGISTRATION && nicknameExists){
            labelUncorrectNickname->close();
            inHover = false;
        }
        else if(event->type() == QEvent::MouseMove && inHover && location==LOC_REGISTRATION && nicknameExists){
            QPoint mousePos = QCursor::pos();

            if(labelUncorrectNickname->width()+mousePos.x()-x()+(width()/26)*2 >= this->width())
                labelUncorrectNickname->move(this->width()-labelUncorrectNickname->width()-width()/26, mousePos.y()-y()-labelUncorrectNickname->height()-this->height()/130);
            else
                labelUncorrectNickname->move(mousePos.x()-x()+width()/26, mousePos.y()-y()-labelUncorrectNickname->height()-this->height()/130);

        }
    }

    if(target == lineEmail && event->type() == QEvent::KeyPress){
        if(static_cast<QKeyEvent*>(event)->key() == Qt::Key_Return || static_cast<QKeyEvent*>(event)->key() == Qt::Key_Enter || static_cast<QKeyEvent*>(event)->key() == Qt::Key_Down)
            lineLog->setFocus();
    }
    else if(target == lineLog && event->type() == QEvent::KeyPress){
        if (static_cast<QKeyEvent*>(event)->key() == Qt::Key_Return || static_cast<QKeyEvent*>(event)->key() == Qt::Key_Enter || static_cast<QKeyEvent*>(event)->key() == Qt::Key_Down){
            if(location != LOC_RECOVERY_EMAIL)
                linePass->setFocus();
            else
                buttonOk_released();
        }
        else if(static_cast<QKeyEvent*>(event)->key() == Qt::Key_Up && location == LOC_REGISTRATION)
            lineEmail->setFocus();
    }
    else if(target == linePass && event->type() == QEvent::KeyPress){
        if(static_cast<QKeyEvent*>(event)->key() == Qt::Key_Return || static_cast<QKeyEvent*>(event)->key() == Qt::Key_Enter || static_cast<QKeyEvent*>(event)->key() == Qt::Key_Down){
            if(location == LOC_REGISTRATION)
                lineConfirmPass->setFocus();
            else
                signIn_released();
        }
        else if(static_cast<QKeyEvent*>(event)->key() == Qt::Key_Up)
            lineLog->setFocus();
    }
    else if(target == lineConfirmPass && event->type() == QEvent::KeyPress){
        if(static_cast<QKeyEvent*>(event)->key() == Qt::Key_Return || static_cast<QKeyEvent*>(event)->key() == Qt::Key_Enter)
            signUp_released();
        else if(static_cast<QKeyEvent*>(event)->key() == Qt::Key_Up)
            linePass->setFocus();
    }
    else if(target == lineRecoveryPass && event->type() == QEvent::KeyPress){
        if(static_cast<QKeyEvent*>(event)->key() == Qt::Key_Return || static_cast<QKeyEvent*>(event)->key() == Qt::Key_Enter || static_cast<QKeyEvent*>(event)->key() == Qt::Key_Down)
            lineRecoveryConfirmPass->setFocus();
    }
    else if(target == lineRecoveryConfirmPass && event->type() == QEvent::KeyPress){
        if(static_cast<QKeyEvent*>(event)->key() == Qt::Key_Return || static_cast<QKeyEvent*>(event)->key() == Qt::Key_Enter)
            buttonOk_released();
        else if(static_cast<QKeyEvent*>(event)->key() == Qt::Key_Up)
            lineRecoveryPass->setFocus();
    }
    else if(target == lineConfirmCode && event->type() == QEvent::KeyPress){
        if(static_cast<QKeyEvent*>(event)->key() == Qt::Key_Return || static_cast<QKeyEvent*>(event)->key() == Qt::Key_Enter)
            buttonOk_released();
    }

    if((target == linePass || target==buttonEye) && labelPass->isEnabled() && !isPassEmpty){
        if(event->type()==QEvent::HoverEnter){
            if(!linePass->hasFocus()){
                linePass->setStyleSheet(QString("AuthLineEdit{"
                                                "font-family: Century Gothic;"
                                                "font-size: %1px;"
                                                "background: transparent;"
                                                "border: 1px solid black;"
                                                "border-right: 0px;"
                                                "color: #B5EBEE;"
                                                "}").arg(defaultFontSize));
                if(target==buttonEye)
                    buttonEye->setStyleSheet("background: rgba(123,55,65,50);"
                                             "border: 1px solid black;"
                                             "border-left: 0px;");
                else
                    buttonEye->setStyleSheet("border: 1px solid black;"
                                             "border-left: 0px;");
            }
            else if(target==buttonEye)
                buttonEye->setStyleSheet("background: rgba(123,55,65,50);"
                                         "border: 1px solid #0078d7;"
                                         "border-left: 0px;");
        }
        else if((event->type() == QEvent::HoverLeave && linePass->hasFocus()) || (event->type() == QEvent::FocusIn)){
            linePass->setStyleSheet(QString("AuthLineEdit{"
                                            "font-family: Century Gothic;"
                                            "font-size: %1px;"
                                            "background: transparent;"
                                            "border: 1px solid #0078d7;"
                                            "border-right: 0px;"
                                            "color: #B5EBEE;"
                                            "}").arg(defaultFontSize));
            buttonEye->setStyleSheet("border: 1px solid #0078d7;"
                                     "border-left: 0px;");
        }
        else if((event->type() == QEvent::HoverLeave && !linePass->hasFocus()) || event->type() == QEvent::FocusOut){
            linePass->setStyleSheet(QString("AuthLineEdit{"
                                            "font-family: Century Gothic;"
                                            "font-size: %1px;"
                                            "background: transparent;"
                                            "border: 1px solid gray;"
                                            "border-right: 0px;"
                                            "color: #B5EBEE;"
                                            "}").arg(defaultFontSize));
            buttonEye->setStyleSheet("border: 1px solid gray;"
                                     "border-left: 0px;");
        }
    }
    else if((target == lineRecoveryPass || target==buttonRecoveryEye) && labelPass->isEnabled() && !isRecoveryPassEmpty){
        if(event->type()==QEvent::HoverEnter){
            if(!lineRecoveryPass->hasFocus()){
                lineRecoveryPass->setStyleSheet(QString("AuthLineEdit{"
                                                "font-family: Century Gothic;"
                                                "font-size: %1px;"
                                                "background: transparent;"
                                                "border: 1px solid black;"
                                                "border-right: 0px;"
                                                "color: #B5EBEE;"
                                                "}").arg(defaultFontSize));
                if(target==buttonRecoveryEye)
                    buttonRecoveryEye->setStyleSheet("background: rgba(123,55,65,50);"
                                             "border: 1px solid black;"
                                             "border-left: 0px;");
                else
                    buttonRecoveryEye->setStyleSheet("border: 1px solid black;"
                                             "border-left: 0px;");
            }
            else if(target==buttonRecoveryEye)
                buttonRecoveryEye->setStyleSheet("background: rgba(123,55,65,50);"
                                         "border: 1px solid #0078d7;"
                                         "border-left: 0px;");
        }
        else if((event->type() == QEvent::HoverLeave && lineRecoveryPass->hasFocus()) || (event->type() == QEvent::FocusIn)){
            lineRecoveryPass->setStyleSheet(QString("AuthLineEdit{"
                                            "font-family: Century Gothic;"
                                            "font-size: %1px;"
                                            "background: transparent;"
                                            "border: 1px solid #0078d7;"
                                            "border-right: 0px;"
                                            "color: #B5EBEE;"
                                            "}").arg(defaultFontSize));
            buttonRecoveryEye->setStyleSheet("border: 1px solid #0078d7;"
                                     "border-left: 0px;");
        }
        else if((event->type() == QEvent::HoverLeave && !lineRecoveryPass->hasFocus()) || event->type() == QEvent::FocusOut){
            lineRecoveryPass->setStyleSheet(QString("AuthLineEdit{"
                                            "font-family: Century Gothic;"
                                            "font-size: %1px;"
                                            "background: transparent;"
                                            "border: 1px solid gray;"
                                            "border-right: 0px;"
                                            "color: #B5EBEE;"
                                            "}").arg(defaultFontSize));
            buttonRecoveryEye->setStyleSheet("border: 1px solid gray;"
                                     "border-left: 0px;");
        }
    }

    return QMainWindow::eventFilter(target, event);
}

void AuthWindow::buttonMinimize_released(){
    QPropertyAnimation *animation = new QPropertyAnimation(this, "windowOpacity");
    animation->setEndValue(0.0);
    animation->setDuration(200);
    animation->start(QAbstractAnimation::DeleteWhenStopped);
    connect(animation, SIGNAL(finished()), this, SLOT(showMinimized()));
}

void AuthWindow::changeEvent(QEvent* e){
    if( e->type() == QEvent::WindowStateChange ){
        QWindowStateChangeEvent* event = static_cast<QWindowStateChangeEvent*>(e);

        if(event->oldState() & Qt::WindowMinimized){
            QPropertyAnimation *animation = new QPropertyAnimation(this, "windowOpacity");
            animation->setDuration(150);
            animation->setEndValue(1.0);
            this->showNormal();
            animation->start(QAbstractAnimation::DeleteWhenStopped);
        }
    }
}

void AuthWindow::setPassEnabled(){
    labelPass->setEnabled(true);
    linePass->setEnabled(true);
    buttonEye->setEnabled(true);
    linePass->setStyleSheet(QString("AuthLineEdit{"
                                    "font-family: Century Gothic;"
                                    "font-size: %1px;"
                                    "background: transparent;"
                                    "border: 1px solid gray;"
                                    "border-right: 0px;"
                                    "color: #B5EBEE;"
                                    "}").arg(defaultFontSize));
    buttonEye->setStyleSheet("QPushButton{"
                             "background: transparent; border: 1px solid gray; border-left: 0px;"
                             "}");
}


AuthWindow::~AuthWindow(){
    delete ui;

    delete lineLog;
    delete linePass;
    delete lineConfirmPass;
    delete lineEmail;
    delete lineConfirmCode;
    delete lineRecoveryPass;
    delete lineRecoveryConfirmPass;

    delete buttonSignIn;
    delete buttonSignUp;
    delete buttonOk;
    delete buttonClose;
    delete buttonEye;
    delete buttonRecoveryEye;
    delete buttonMinimize;

    delete labelForgotPass;
    delete labelSignUp;
    delete labelSignIn;
    delete labelUncorrectNickname;
    delete labelError;
    delete labelErrorBackground;
    delete labelSuccess;
    delete labelPass;
    delete labelRecoveryPass;

    delete preloader;
    delete opacity;

    delete timerWaitingAnswer;
    delete timerLabelSuccess;
    delete timerErrorLabel;
}

