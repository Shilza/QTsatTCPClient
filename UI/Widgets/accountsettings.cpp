#include "accountsettings.h"
#include <QBitMap>

AccountSettings::AccountSettings(QWidget *parent) : QWidget(parent){
    close();

    const QString defaultLineStyle = "QLineEdit{"
                                     "border: 0px;"
                                     "border-bottom: 1px solid gray;"
                                     "}"
                                     "QLineEdit:hover{"
                                     "border-bottom: 1px solid blue;"
                                     "}"
                                     "QLineEdit:focus{"
                                     "border-bottom: 1px solid blue;"
                                     "}";

    const QString defaultButtonsStyle = "QPushButton{"
                                        "border: 1px solid black;"
                                        "border-radius: 6px;"
                                        "}"
                                        "QPushButton:hover{"
                                        "border-color: #028F92;"
                                        "}"
                                        "QPushButton:focus:pressed{"
                                        "background: #EDEDED;"
                                        "}";

    const QString defaultLabelStyle = "border: 0px;"
                                      "color: gray;";

    mainWidget = new QWidget(this);
    mainLayout = new QGridLayout(mainWidget);

    buttonAvatar = new QPushButton(mainWidget);
    buttonAvatarChanging = new QPushButton("Change avatar", mainWidget);

    labelNickname = new QLabel("Nickname", mainWidget);
    lineNewNickname = new QLineEdit(mainWidget);

    labelAboutMe = new QLabel("About me", mainWidget);
    lineAboutMe = new QLineEdit(mainWidget);

    widgetPassword = new QWidget(mainWidget);
    layoutPassword = new QHBoxLayout(widgetPassword);
    labelPassword = new QLabel("Password", widgetPassword);
    buttonEye = new QPushButton(widgetPassword);
    lineOldPassword = new QLineEdit(mainWidget);
    lineNewPassword = new QLineEdit(mainWidget);
    lineConfirmNewPassword = new QLineEdit(mainWidget);

    buttonBlackList = new QPushButton("Black list", mainWidget);
    buttonActivityHistory = new QPushButton("Activity list", mainWidget);

    QWidget *temp = new QWidget(mainWidget);
    temp->setStyleSheet("border: 0px;");

    mainWidget->setStyleSheet("background: white;"
                              "border: 0px;"
                              "border-right: 1px solid gray;");
    mainWidget->setLayout(mainLayout);
    mainLayout->setContentsMargins(30, 10, 30, 10);


    buttonAvatar->setFixedSize(50, 50);
    buttonAvatar->setIconSize(buttonAvatar->size());
    buttonAvatar->setMask(QRegion(0, 0, buttonAvatar->width(), buttonAvatar->height(), QRegion::Ellipse));
    buttonAvatar->setStyleSheet("background: black;"
                                "border: 1px solid red;"
                                "border-radius: 25px;");
    buttonAvatar->setCursor(Qt::PointingHandCursor);

    buttonAvatarChanging->setFixedSize(100, 30);
    buttonAvatarChanging->setCursor(Qt::PointingHandCursor);
    buttonAvatarChanging->setStyleSheet("QPushButton{"
                                        "border: 1px solid black;"
                                        "border-radius: 2px;"
                                        "}"
                                        "QPushButton:hover{"
                                        "border-color: blue;"
                                        "}"
                                        "QPushButton:focus:pressed{"
                                        "background: #D3E9E9;"
                                        "border-color: blue;"
                                        "}");

    labelNickname->setStyleSheet(defaultLabelStyle);
    labelNickname->setContentsMargins(0, 10, 0, 0);
    lineNewNickname->setValidator(new QRegExpValidator(QRegExp("^(\\d|[A-z]|[_.]){3,12}$")));
    lineNewNickname->setStyleSheet(defaultLineStyle);
    lineNewNickname->setFixedWidth(140);

    labelAboutMe->setStyleSheet(defaultLabelStyle);
    labelAboutMe->setContentsMargins(0, 10, 0, 0);
    lineAboutMe->setStyleSheet(defaultLineStyle);
    lineAboutMe->setFixedWidth(140);
    lineAboutMe->setValidator(new QRegExpValidator(QRegExp("^(\\d|\\w){3,50}$")));

    widgetPassword->setLayout(layoutPassword);
    widgetPassword->setStyleSheet("border: 0px;");
    layoutPassword->addWidget(labelPassword);
    layoutPassword->addWidget(buttonEye, 0, Qt::AlignBottom);
    layoutPassword->setContentsMargins(0, 10, 0, 0);

    buttonEye->setFixedSize(20, 20);
    buttonEye->setIcon(QIcon(":images/eye.png"));
    buttonEye->setIconSize(buttonEye->size());
    buttonEye->setStyleSheet("QPushButton{background: transparent; border: 0px;}"
                             "QPushButton:hover{background: #D3E9E9;}");
    buttonEye->setCursor(Qt::PointingHandCursor);

    labelPassword->setStyleSheet(defaultLabelStyle);

    lineOldPassword->setStyleSheet(defaultLineStyle);
    lineOldPassword->setPlaceholderText("Enter old password");
    lineOldPassword->setEchoMode(QLineEdit::Password);
    lineOldPassword->setFixedWidth(140);
    lineOldPassword->setValidator(new QRegExpValidator(QRegExp("^(\\d|[A-z]|[._]){6,32}$")));
    lineNewPassword->setStyleSheet(defaultLineStyle);
    lineNewPassword->setPlaceholderText("Enter new password");
    lineNewPassword->setEchoMode(QLineEdit::Password);
    lineNewPassword->setFixedWidth(140);
    lineNewPassword->setValidator(new QRegExpValidator(QRegExp("^(\\d|[A-z]|[._]){6,32}$")));
    lineConfirmNewPassword->setStyleSheet(defaultLineStyle);
    lineConfirmNewPassword->setPlaceholderText("Confirm new password");
    lineConfirmNewPassword->setEchoMode(QLineEdit::Password);
    lineConfirmNewPassword->setFixedWidth(140);
    lineConfirmNewPassword->setValidator(new QRegExpValidator(QRegExp("^(\\d|[A-z]|[._]){6,32}$")));

    buttonBlackList->setStyleSheet(defaultButtonsStyle);
    buttonBlackList->setFixedSize(80, 25);

    buttonActivityHistory->setStyleSheet(defaultButtonsStyle);
    buttonActivityHistory->setFixedSize(80, 25);

    mainLayout->addWidget(buttonAvatar, 0, 0, 1, -1, Qt::AlignTop | Qt::AlignHCenter);
    mainLayout->addWidget(buttonAvatarChanging, 1, 0, 1, -1, Qt::AlignTop | Qt::AlignHCenter);

    mainLayout->addWidget(labelNickname, 2, 0, 1, 1, Qt::AlignTop | Qt::AlignLeft);
    mainLayout->addWidget(lineNewNickname, 3, 0, 1, 1, Qt::AlignTop | Qt::AlignLeft);

    mainLayout->addWidget(labelAboutMe, 4, 0, 1, 1, Qt::AlignTop | Qt::AlignLeft);
    mainLayout->addWidget(lineAboutMe, 5, 0, 1, 1, Qt::AlignTop | Qt::AlignLeft);

    mainLayout->addWidget(widgetPassword, 6, 0, 1, 1, Qt::AlignTop | Qt::AlignLeft);
    mainLayout->addWidget(lineOldPassword, 7, 0, 1, 1, Qt::AlignTop | Qt::AlignLeft);
    mainLayout->addWidget(lineNewPassword, 8, 0, 1, 1, Qt::AlignTop | Qt::AlignLeft);
    mainLayout->addWidget(lineConfirmNewPassword, 9, 0, 1, 1, Qt::AlignTop | Qt::AlignLeft);

    mainLayout->addWidget(buttonBlackList, 3, 1, 1, 1, Qt::AlignTop | Qt::AlignRight);
    mainLayout->addWidget(buttonActivityHistory, 4, 1, 1, 1, Qt::AlignTop | Qt::AlignRight);

    mainLayout->addWidget(temp, 10, 0, 6, -1);

    lineNewNickname->installEventFilter(this);
    lineAboutMe->installEventFilter(this);
    lineOldPassword->installEventFilter(this);
    lineNewPassword->installEventFilter(this);
    lineConfirmNewPassword->installEventFilter(this);

    connect(buttonAvatarChanging, SIGNAL(released()), SLOT(avatarChanging()));
    connect(buttonEye, SIGNAL(released()), SLOT(setPassEchoMode()));
    connect(&(TCPClient::getInstance()), SIGNAL(nicknameReceived(QString)), SLOT(setNickname(QString)));
}

QWidget *AccountSettings::getMainWidget() const{
    return mainWidget;
}

void AccountSettings::avatarChanging(){
    static QString lastPath = QDir::homePath();
    int size=0;

    QString temp = QFileDialog::getOpenFileName(this, QObject::tr("Choose an image"), lastPath, QObject::tr("Image file (*.png *.jpg *.jpeg *.jpe *.bmp);;Все файлы (*.*)"));
    if(temp != ""){
        QString extension = temp.split('.').back();
        lastPath = temp;
        avatarImage = QPixmap(temp);
        size = getSize(avatarImage, extension);

        if(size > MAX_AFFIX_SIZE){
            emit attachmentToLarge();
            avatarImage = QPixmap();
            return;
        }

        buttonAvatar->setIcon(QIcon(avatarImage));

        /*
        QJsonObject request;
        request.insert("Target", "Post");
        request.insert("Extension", extension);
        request.insert("Location", "Avatar");
        request.insert("Size", size);
        FTPClient::getInstance().send(request);
        */
        //emit imageReceived(image, extension);
    }
}

void AccountSettings::setAvatarImage(QPixmap image){
    //TODO
}

void AccountSettings::setAvatarImage(){
    buttonAvatar->setIcon(QIcon(avatarImage));
}

void AccountSettings::setNickname(QString nickname){
    lineNewNickname->setText(nickname);
}

void AccountSettings::setPassEchoMode(){
    static bool isEnabled = false;
    if(isEnabled){
        lineOldPassword->setEchoMode(QLineEdit::Password);
        lineNewPassword->setEchoMode(QLineEdit::Password);
        lineConfirmNewPassword->setEchoMode(QLineEdit::Password);
    }
    else{
        lineOldPassword->setEchoMode(QLineEdit::Normal);
        lineNewPassword->setEchoMode(QLineEdit::Normal);
        lineConfirmNewPassword->setEchoMode(QLineEdit::Normal);
    }
    isEnabled = !isEnabled;
}

bool AccountSettings::eventFilter(QObject *watched, QEvent *event){
    if(watched == lineNewNickname){
        if(event->type() == QEvent::KeyRelease &&(
                    static_cast<QKeyEvent*>(event)->key() == Qt::Key_Return ||
                    static_cast<QKeyEvent*>(event)->key() == Qt::Key_Enter ||
                    static_cast<QKeyEvent*>(event)->key() == Qt::Key_Down))
            lineAboutMe->setFocus();
    }
    else if(watched == lineAboutMe){
        if(event->type() == QEvent::KeyRelease &&(
                    static_cast<QKeyEvent*>(event)->key() == Qt::Key_Return ||
                    static_cast<QKeyEvent*>(event)->key() == Qt::Key_Enter ||
                    static_cast<QKeyEvent*>(event)->key() == Qt::Key_Down))
            lineOldPassword->setFocus();
        else if(event->type() == QEvent::KeyRelease && static_cast<QKeyEvent*>(event)->key() == Qt::Key_Up)
            lineNewNickname->setFocus();
    }
    else if(watched == lineOldPassword){
        if(event->type() == QEvent::KeyRelease &&(
                    static_cast<QKeyEvent*>(event)->key() == Qt::Key_Return ||
                    static_cast<QKeyEvent*>(event)->key() == Qt::Key_Enter ||
                    static_cast<QKeyEvent*>(event)->key() == Qt::Key_Down))
            lineNewPassword->setFocus();
        else if(event->type() == QEvent::KeyRelease && static_cast<QKeyEvent*>(event)->key() == Qt::Key_Up)
            lineAboutMe->setFocus();
    }
    else if(watched == lineNewPassword){
        if(event->type() == QEvent::KeyRelease &&(
                    static_cast<QKeyEvent*>(event)->key() == Qt::Key_Return ||
                    static_cast<QKeyEvent*>(event)->key() == Qt::Key_Enter ||
                    static_cast<QKeyEvent*>(event)->key() == Qt::Key_Down))
            lineConfirmNewPassword->setFocus();
        else if(event->type() == QEvent::KeyRelease && static_cast<QKeyEvent*>(event)->key() == Qt::Key_Up)
            lineOldPassword->setFocus();
    }
    else if(watched == lineConfirmNewPassword){
        if(event->type() == QEvent::KeyRelease && static_cast<QKeyEvent*>(event)->key() == Qt::Key_Up)
            lineNewPassword->setFocus();
    }
    return QWidget::eventFilter(watched, event);
}
