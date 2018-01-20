#include "globaltextedit.h"
#include <QDebug>

GlobalTextEdit::GlobalTextEdit(QWidget *parent) : QTextEdit(parent){
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setContextMenuPolicy(Qt::CustomContextMenu);
    setAcceptDrops(true);
    connect(this, SIGNAL(textChanged()), SLOT(validator()));
}

void GlobalTextEdit::keyPressEvent(QKeyEvent *event){
    bool previousSpace = false;

    if(this->toPlainText().length() > 0)
        previousSpace = this->toPlainText().at(this->toPlainText().length()-1) == " ";

    if((event->key() == Qt::Key_Return || event->key() == Qt::Key_Enter)){
        if(event->modifiers() != Qt::ControlModifier){
            emit enter();
            return;
        }
        else if(!previousSpace){
            if(this->toPlainText().indexOf('\n')==-1)
                QTextEdit::keyPressEvent(new QKeyEvent(QEvent::KeyPress, Qt::Key_Enter, Qt::NoModifier));
            return;
        }
    }
    else if(event->key() == Qt::Key_Space && previousSpace)
        return;
    else if(event->matches(QKeySequence::Paste)){
        QString tempText = QApplication::clipboard()->text();

        const QMimeData* mime = QApplication::clipboard()->mimeData();
        if(mime->hasImage()){
            emit imageReceived(mime->imageData().value<QPixmap>(), "image");
            return;
        }
        else if(mime->hasText()){
            quint8 maxSize = MAX_GLOBAL_MESSAGE_SIZE-toPlainText().length();

            if(toPlainText().indexOf('\n') == -1){
                if(tempText.indexOf('\n')!=-1){
                    while(tempText.indexOf("  ") != -1)
                        tempText = tempText.remove(tempText.indexOf("  "), 2).insert(tempText.indexOf("  "), " ");

                    tempText = tempText.simplified().insert(tempText.indexOf('\n'), '\n');
                }
                else
                    tempText = tempText.simplified();
            }
            else if(toPlainText().indexOf('\n')!=-1)
                tempText = tempText.simplified();

            if(tempText.length()>maxSize)
                tempText = tempText.left(maxSize);

            QTextCursor cursor = this->textCursor();
            quint8 tempPos = cursor.position();
            setText(this->toPlainText().insert(cursor.position(), tempText));
            cursor.setPosition(tempPos+tempText.length());
            setTextCursor(cursor);
            return;
        }
    }

    QTextEdit::keyPressEvent(event);
}

void GlobalTextEdit::dropEvent(QDropEvent *e){
    QMimeData data;
    data.setText("");

    /*if(e->mimeData()->hasImage()){
        emit imageReceived(e->mimeData()->imageData().value<QPixmap>());
        QTextEdit::dropEvent(new QDropEvent(QPointF(0,0), Qt::IgnoreAction, &data, Qt::LeftButton, Qt::NoModifier));
    }
    else*/
    if(e->mimeData()->hasUrls()){
        for(QUrl a : e->mimeData()->urls()){
            QString extension = a.fileName().split('.').back();
            if(extension == "jpg" || extension=="png" || extension=="bmp" || extension=="jpeg" || extension=="jpe"){
                QPixmap image;
                image.load(a.path().right(a.path().length()-1));

                emit imageReceived(image, extension);
                QTextEdit::dropEvent(new QDropEvent(QPointF(0,0), Qt::IgnoreAction, &data, Qt::LeftButton, Qt::NoModifier));
                break;
            }
        }
    }
    else{
        if(e->mimeData()->hasText())
            e->setAccepted(false);
        QTextEdit::dropEvent(e);
    }
}

void GlobalTextEdit::dragEnterEvent(QDragEnterEvent *e){
    if(e->mimeData()->hasText() && !e->mimeData()->hasUrls())
        e->setAccepted(false);
    QTextEdit::dragEnterEvent(e);
}

void GlobalTextEdit::validator()
{
    static QString lastTextState = this->toPlainText();
    if(toPlainText().length()>MAX_GLOBAL_MESSAGE_SIZE){
        QTextCursor cursor = this->textCursor();
        quint8 tempPos = cursor.position();
        setText(lastTextState);
        cursor.setPosition(tempPos-1);
        setTextCursor(cursor);
    }
    else
        lastTextState = this->toPlainText();
}

