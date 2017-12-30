#include "floodtimer.h"

FloodTimer::FloodTimer(QWidget *parent) : QObject(parent){
    timerErrorHide = new QTimer(this);
    timerErrorHide->setSingleShot(true);
    timerShow = new QTimer(this);
    timerShow->setInterval(10);
    connect(timerErrorHide, SIGNAL(timeout()), this, SLOT(emitErrorTimeout()));
    connect(timerShow, SIGNAL(timeout()), this, SLOT(emitShowTimeout()));
}

int FloodTimer::remainingTime(){
    return timerErrorHide->remainingTime();
}

void FloodTimer::start(int time){
    timerErrorHide->start(time);
    timerShow->start();
}

void FloodTimer::emitErrorTimeout(){
    timerShow->stop();
    emit errorTimeout();
}

void FloodTimer::emitShowTimeout(){
    emit showTimeout();
}

FloodTimer::~FloodTimer(){
    delete timerErrorHide;
    delete timerShow;
}
