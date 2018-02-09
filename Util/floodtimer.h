#ifndef FLOODTIMER_H
#define FLOODTIMER_H

#include <QWidget>
#include <QTimer>

class FloodTimer : public QObject{
    Q_OBJECT
public:
    explicit FloodTimer(QWidget *parent=0);
    ~FloodTimer();
    int remainingTime();
    void start(int time);

private:
    QTimer *timerErrorHide;
    QTimer *timerShow;

signals:
    void errorTimeout();
    void showTimeout();

private slots:
    void emitErrorTimeout();
    void emitShowTimeout();
};

#endif // FLOODTIMER_H
