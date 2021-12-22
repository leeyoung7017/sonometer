#include "pcm.h"


QByteArray pcm_read(QString FilePath)
{
    /*读取pcm文件数据*/
    QByteArray arr;
    QFile f(FilePath);
    if (!f.open(QIODevice::ReadOnly))
        exit(0);
    arr = f.readAll();
    f.close();
    return arr;
}
