#ifndef ACCOUNTWIDGET_H
#define ACCOUNTWIDGET_H

#include <QPushButton>
#include <QVBoxLayout>
#include <QEvent>
#include "UI/Widgets/clickablelabel.h"
#include "Util/tcpclient.h"

class AccountWidget : public QWidget
{
    Q_OBJECT
public:
    explicit AccountWidget(QWidget *parent, QPushButton *buttonUserPagePtr);
    const QWidget *getWidget() const;

private:
    bool isWidgetClosed = true;
    QPushButton *buttonUserPagePtr;

    QWidget *mainWidget;
    QVBoxLayout *mainLayout;
    ClickableLabel *buttonUser;
    QPushButton *buttonAccountSettings;
    QPushButton *buttonExit;
    bool eventFilter(QObject *watched, QEvent *event);

signals:
    void lostFocus();
public slots:
    void widgetShow();

private slots:
    void exit();
    void exit(bool isExit);
};

#endif // ACCOUNTWIDGET_H
