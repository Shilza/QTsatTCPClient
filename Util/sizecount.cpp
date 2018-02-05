#include "Util/sizecounting.h"

int getSize(QPixmap image, QString extension){
    QByteArray tempArray;
    QBuffer tempBuffer(&tempArray);
    tempBuffer.open(QIODevice::WriteOnly);
    image.save(&tempBuffer, extension == "image" ? "png" : extension.toStdString().c_str());
    tempBuffer.close();

    return tempArray.size();
}
