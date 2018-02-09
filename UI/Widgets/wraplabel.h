#ifndef WRAPLABEL_H
#define WRAPLABEL_H

#include <QLabel>
#include <QKeyEvent>
#include <QApplication>
#include <QClipboard>
#include <QListWidgetItem>

class WrapLabel : public QLabel{
    Q_OBJECT
public:
    explicit WrapLabel(QWidget* parent=0);
    void wrapText(QString text);
    void setItem(QListWidgetItem *item);
    ~WrapLabel();

private:
    QListWidgetItem *item;
    void keyPressEvent(QKeyEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);

signals:
    void select(QListWidgetItem*);
};
#endif // WRAPLABEL_H
