#ifndef PRESETTINGS_H
#define PRESETTINGS_H

#include <QVBoxLayout>
#include <QPushButton>
#include <Util/tcpclient.h>

class PreSettings : public QWidget
{
    Q_OBJECT
public:
    explicit PreSettings(QWidget *parent = nullptr);
    QWidget* getWidget();

private:
    QWidget* widget;
    QVBoxLayout *mainLayout;
    QPushButton *buttonBansHistory;
    QPushButton *buttonExit;
    QPushButton *buttonSettings;

private slots:
    void exit();
    void loadBansHistory();

signals:
    void showBansHistory();

};

#endif // PRESETTINGS_H
