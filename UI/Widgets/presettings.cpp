#include "presettings.h"
#include <QDebug>

PreSettings::PreSettings(QWidget *parent) : QWidget(parent){
    widget = new QWidget(this);
    setFixedSize(120, 100);

    mainLayout = new QVBoxLayout(widget);
    widget->setLayout(mainLayout);

    buttonBansHistory = new QPushButton(widget);
    buttonExit = new QPushButton(widget);
    buttonSettings = new QPushButton(widget);

    buttonBansHistory->setText("Bans history");
    buttonExit->setText("Exit");
    buttonSettings->setText("Settings");

    setStyleSheet("background: transparent;"
                  "border: 1px solid black;"
                  "border-radius: 2px;");

    QString buttonDefaultStyle = "QPushButton{"
                                 "background: transparent;"
                                 "border: 0px;"
                                 "}"
                                 "QPushButton:hover{"
                                 "background: #D3E9E9;"
                                 "}";

    buttonBansHistory->setStyleSheet(buttonDefaultStyle);
    buttonExit->setStyleSheet(buttonDefaultStyle);
    buttonSettings->setStyleSheet(buttonDefaultStyle);

    buttonBansHistory->setFixedWidth(100);
    buttonExit->setFixedWidth(100);
    buttonSettings->setFixedWidth(100);

    mainLayout->addWidget(buttonExit, 1, Qt::AlignHCenter);
    mainLayout->addWidget(buttonSettings, 1, Qt::AlignHCenter);
    mainLayout->addWidget(buttonBansHistory, 1, Qt::AlignHCenter);

    connect(buttonExit, SIGNAL(released()), SLOT(exit()));
}

QWidget *PreSettings::getWidget(){
    return widget;
}

void PreSettings::exit(){

}
