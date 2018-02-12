#include "image.h"

Image::Image(QString extension, QWidget *parent) : Attachment(parent){

    this->extension = extension;
}

void Image::fill(QByteArray data){
    image.loadFromData(data, extension.toStdString().c_str());
}

void Image::open(){

}
