#ifndef PRESETTINGS_H
#define PRESETTINGS_H

#include <QWidget>
#include <QVBoxLayout>
#include <QPushButton>

class PreSettings : public QWidget
{
    Q_OBJECT
public:
    explicit PreSettings(QWidget *parent = nullptr);

private:
    QVBoxLayout *mainLayout;
    QPushButton *buttonBansHistory;
    QPushButton *buttonExit;
    QPushButton *buttonSettings;

signals:

public slots:
};

#endif // PRESETTINGS_H
