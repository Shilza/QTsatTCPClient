#ifndef PRESETTINGS_H
#define PRESETTINGS_H

#include <QVBoxLayout>
#include <QPushButton>

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

signals:

private slots:
    void exit();
};

#endif // PRESETTINGS_H
