#include "presettings.h"

PreSettings::PreSettings(QWidget *parent) : QWidget(parent){
    mainLayout = new QVBoxLayout(this);
    setLayout(mainLayout);

    buttonBansHistory = new QPushButton(this);
    buttonExit = new QPushButton(this);
    buttonSettings = new QPushButton(this);

    buttonBansHistory->setText("Bans history");
    buttonExit->setText("Exit");
    buttonSettings->setText("Settings");

    mainLayout->addWidget(buttonExit);
    mainLayout->addWidget(buttonSettings);
    mainLayout->addWidget(buttonBansHistory);
}
