#include "accountsettings.h"

AccountSettings::AccountSettings(QWidget *parent) : QWidget(parent){
    close();

    QString defaultLineStyle = "QLineEdit{"
                               "border: 0px;"
                               "border-bottom: 1px solid gray;"
                               "}"
                               "QLineEdit:hover{"
                               "border-bottom: 1px solid blue;"
                               "}"
                               "QLineEdit:focus{"
                               "border-bottom: 1px solid blue;"
                               "}";

    QString defaultLabelStyle = "border: 0px;"
                                "color: gray;";

    mainWidget = new QWidget(this);
    mainLayout = new QVBoxLayout(mainWidget);

    buttonAvatar = new QPushButton(mainWidget);
    buttonAvatarChanging = new QPushButton("Change avatar", mainWidget);

    labelNickname = new QLabel(mainWidget);
    lineNewNickname = new QLineEdit(mainWidget);

    labelAboutMe = new QLabel(mainWidget);
    lineAboutMe = new QLineEdit(mainWidget);

    labelPassword = new QLabel(mainWidget);
    lineOldPassword = new QLineEdit(mainWidget);
    lineNewPassword = new QLineEdit(mainWidget);
    lineConfirmNewPassword = new QLineEdit(mainWidget);

    QWidget *temp = new QWidget(mainWidget);
    temp->setStyleSheet("border: 0px;");

    mainWidget->setStyleSheet("background: white;"
                              "border: 0px;"
                              "border-right: 1px solid gray;");
    mainWidget->setLayout(mainLayout);
    mainLayout->setContentsMargins(20, 10, 20, 10);

    buttonAvatar->setFixedSize(50, 50);
    buttonAvatar->setStyleSheet("background: black;"
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
    labelNickname->setText("Nickname");
    lineNewNickname->setStyleSheet(defaultLineStyle);

    labelAboutMe->setStyleSheet(defaultLabelStyle);
    labelAboutMe->setText("About me");
    labelAboutMe->setContentsMargins(0, 10, 0, 0);
    lineAboutMe->setStyleSheet(defaultLineStyle);

    labelPassword->setStyleSheet(defaultLabelStyle);
    labelPassword->setText("Password");
    labelPassword->setContentsMargins(0, 10, 0, 0);
    lineOldPassword->setStyleSheet(defaultLineStyle);
    lineOldPassword->setPlaceholderText("Enter old password");
    lineOldPassword->setEchoMode(QLineEdit::Password);
    lineNewPassword->setStyleSheet(defaultLineStyle);
    lineNewPassword->setPlaceholderText("Enter new password");
    lineNewPassword->setEchoMode(QLineEdit::Password);
    lineConfirmNewPassword->setStyleSheet(defaultLineStyle);
    lineConfirmNewPassword->setPlaceholderText("Confirm new password");
    lineConfirmNewPassword->setEchoMode(QLineEdit::Password);

    mainLayout->addWidget(buttonAvatar, 0, Qt::AlignTop | Qt::AlignHCenter);
    mainLayout->addWidget(buttonAvatarChanging, 0, Qt::AlignTop | Qt::AlignHCenter);

    mainLayout->addWidget(labelNickname, 0, Qt::AlignTop | Qt::AlignLeft);
    mainLayout->addWidget(lineNewNickname, 0, Qt::AlignTop | Qt::AlignLeft);

    mainLayout->addWidget(labelAboutMe, 0, Qt::AlignTop | Qt::AlignLeft);
    mainLayout->addWidget(lineAboutMe, 0, Qt::AlignTop | Qt::AlignLeft);

    mainLayout->addWidget(labelPassword, 0, Qt::AlignTop | Qt::AlignLeft);
    mainLayout->addWidget(lineOldPassword, 0, Qt::AlignTop | Qt::AlignLeft);
    mainLayout->addWidget(lineNewPassword, 0, Qt::AlignTop | Qt::AlignLeft);
    mainLayout->addWidget(lineConfirmNewPassword, 0, Qt::AlignTop | Qt::AlignLeft);

    mainLayout->addWidget(temp, 6);

    connect(buttonAvatarChanging, SIGNAL(released()), SLOT(avatarChanging()));
    connect(&(TCPClient::getInstance()), SIGNAL(nicknameReceived(QString)), SLOT(setNickname(QString)));
}

QWidget *AccountSettings::getMainWidget() const{
    return mainWidget;
}

void AccountSettings::avatarChanging(){
    static QString lastPath = QDir::homePath();
    QString temp = QFileDialog::getOpenFileName(this, QObject::tr("Choose an image"), lastPath, QObject::tr("Image file (*.png *.jpg *.jpeg *.jpe *.bmp);;Все файлы (*.*)"));
    if(temp != ""){
        lastPath = temp;
    }
}

void AccountSettings::setNickname(QString nickname){
    lineNewNickname->setText(nickname);
}
