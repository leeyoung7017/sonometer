#ifndef EXCEL_H
#define EXCEL_H

#include "QFileDialog"
#include "QAxObject"
#include "search_null.h"
#include "ui_search_null.h"


QList<QString> excel_RD(QString strFile,QString Name_COMPARE);
void excel_WR(QString strFile,QList<QString> str);

#endif // EXCEL_H
