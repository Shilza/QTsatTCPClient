#ifndef AFFIXCONTAINER_H
#define AFFIXCONTAINER_H

#include <QDir>
#include <QEvent>
#include <QPushButton>
#include <QHBoxLayout>
#include <QFileDialog>
#include <QPropertyAnimation>

class AffixContainer : public QWidget
{
    Q_OBJECT

public:
    explicit AffixContainer(QWidget *parent);
    QPushButton *getButtonAffix();
    QPushButton *getAffixWidgetContaiter() const;

private:
    QPushButton *affixWidgetContainer;
    QHBoxLayout *affixLayout;
    QPushButton *buttonPhotos;
    QPushButton *buttonVideos;
    QPushButton *buttonAudios;
    QPushButton *buttonDocuments;
    QPushButton *buttonAffix;

    bool eventFilter(QObject *target, QEvent *event);

private slots:
    void selectImage();
    void selectSong();

signals:
    void attachmentIsComing(QVariant affix, QString extension);
};

#endif // AFFIXCONTAINER_H
