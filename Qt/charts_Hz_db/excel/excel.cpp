#include "excel.h"
#include <QString>
#include "chart.h"
#include "ui_chart.h"
#include <ui_chart.h>

void excel_WR(QString strFile,QList<QString> str)
{
    QAxObject *excel = new QAxObject();
    /*连接excel控件*/
    if(excel->setControl("Excel.Application")){}/*office的excel*/
    else  excel->setControl("ket.Application");   /*WPS的excel*/

    excel->dynamicCall("SetVisible (bool Visible)","false");//不显示窗体
    excel->setProperty("DisplayAlerts", true);//不显示任何警告信息。如果为true那么在关闭是会出现类似“文件已修改，是否保存”的提示

    QAxObject *work_books = excel->querySubObject("WorkBooks");//获取工作簿集合
    work_books->dynamicCall("Open (const QString&)", strFile); //打开指定文件
    QAxObject *work_book = excel->querySubObject("ActiveWorkBook");//获取当前工作簿
    QAxObject *work_sheets = work_book->querySubObject("WorkSheets");//获取工作表集合
    QAxObject *work_sheet = work_sheets->querySubObject("Item(int)",1);//获取工作表集合的工作表1，即sheet1
    QAxObject *used_range = work_sheet->querySubObject("UsedRange");
    QAxObject *rows = used_range->querySubObject("Rows");
    int row_count = rows->property("Count").toInt();  //获取行数

    QAxObject *cellA;
    //设置标题
    int cellrow=row_count+1;


    for(int i = 0;i<18;i++)
    {
        char a = 65+i;
        QString A= a +QString::number(cellrow);//设置要操作的单元格，如A1
        cellA = work_sheet->querySubObject("Range(QVariant, QVariant)",A);//获取单元格
        cellA->dynamicCall("SetValue(const QVariant&)",QVariant(str.at(i)));//设置单元格的值
    }
  /*
    QAxObject *cellA,*cellB,*cellC,*cellD,*cellE,*cellF,*cellG,*cellH,*cellI,*cellJ,*cellK,*cellL,*cellM,*cellN,*cellO,*cellP,*cellQ,*cellR;
    QString A="A"+QString::number(cellrow);//设置要操作的单元格，如A1
    QString B="B"+QString::number(cellrow);
    QString C="C"+QString::number(cellrow);
    QString D="D"+QString::number(cellrow);
    QString E="E"+QString::number(cellrow);
    QString F="F"+QString::number(cellrow);
    QString G="G"+QString::number(cellrow);
    QString H="H"+QString::number(cellrow);
    QString I="I"+QString::number(cellrow);
    QString J="J"+QString::number(cellrow);
    QString K="K"+QString::number(cellrow);
    QString L="L"+QString::number(cellrow);
    QString M="M"+QString::number(cellrow);
    QString N="M"+QString::number(cellrow);
    QString O="O"+QString::number(cellrow);
    QString P="P"+QString::number(cellrow);
    QString Q="Q"+QString::number(cellrow);
    QString R="R"+QString::number(cellrow);

    cellA = work_sheet->querySubObject("Range(QVariant, QVariant)",A);//获取单元格
    cellB = work_sheet->querySubObject("Range(QVariant, QVariant)",B);
    cellC = work_sheet->querySubObject("Range(QVariant, QVariant)",C);
    cellD = work_sheet->querySubObject("Range(QVariant, QVariant)",D);
    cellE = work_sheet->querySubObject("Range(QVariant, QVariant)",E);
    cellF = work_sheet->querySubObject("Range(QVariant, QVariant)",F);
    cellG = work_sheet->querySubObject("Range(QVariant, QVariant)",G);
    cellH = work_sheet->querySubObject("Range(QVariant, QVariant)",H);
    cellI = work_sheet->querySubObject("Range(QVariant, QVariant)",I);
    cellJ = work_sheet->querySubObject("Range(QVariant, QVariant)",J);
    cellK = work_sheet->querySubObject("Range(QVariant, QVariant)",K);
    cellL = work_sheet->querySubObject("Range(QVariant, QVariant)",L);
    cellM = work_sheet->querySubObject("Range(QVariant, QVariant)",M);
    cellN = work_sheet->querySubObject("Range(QVariant, QVariant)",N);
    cellO = work_sheet->querySubObject("Range(QVariant, QVariant)",O);
    cellP = work_sheet->querySubObject("Range(QVariant, QVariant)",P);
    cellQ = work_sheet->querySubObject("Range(QVariant, QVariant)",Q);
    cellR = work_sheet->querySubObject("Range(QVariant, QVariant)",R);



    cellA->dynamicCall("SetValue(const QVariant&)",QVariant(str.at(0)));//设置单元格的值
    cellB->dynamicCall("SetValue(const QVariant&)",QVariant(str.at(1)));
    cellC->dynamicCall("SetValue(const QVariant&)",QVariant(str.at(2)));
    cellD->dynamicCall("SetValue(const QVariant&)",QVariant(str.at(3)));
    cellE->dynamicCall("SetValue(const QVariant&)",QVariant(str.at(4)));
    cellF->dynamicCall("SetValue(const QVariant&)",QVariant(str.at(5)));
    cellG->dynamicCall("SetValue(const QVariant&)",QVariant(str.at(6)));
    cellH->dynamicCall("SetValue(const QVariant&)",QVariant(str.at(7)));
    cellI->dynamicCall("SetValue(const QVariant&)",QVariant(str.at(8)));
    cellJ->dynamicCall("SetValue(const QVariant&)",QVariant(str.at(9)));
    cellK->dynamicCall("SetValue(const QVariant&)",QVariant(str.at(10)));
    cellL->dynamicCall("SetValue(const QVariant&)",QVariant(str.at(11)));
    cellM->dynamicCall("SetValue(const QVariant&)",QVariant(str.at(12)));
    cellN->dynamicCall("SetValue(const QVariant&)",QVariant(str.at(13)));
    cellO->dynamicCall("SetValue(const QVariant&)",QVariant(str.at(14)));
    cellP->dynamicCall("SetValue(const QVariant&)",QVariant(str.at(15)));
    cellQ->dynamicCall("SetValue(const QVariant&)",QVariant(str.at(16)));
    cellR->dynamicCall("SetValue(const QVariant&)",QVariant(str.at(17)));
*/
    work_book->dynamicCall("Save()");//保存至filepath，注意一定要用QDir::toNativeSeparators将路径中的"/"转换为"\"，不然一定保存不了。
    work_book->dynamicCall("Close()");//关闭工作簿
    excel->dynamicCall("Quit()");//关闭excel
    delete excel;
    excel=NULL;

}

QList<QString> excel_RD(QString strFile,QString Name_COMPARE)
{
    QAxObject excel("Excel.Application"); //加载Excel驱动
    excel.setProperty("Visible", false);//不显示Excel界面，如果为true会看到启动的Excel界面
    QAxObject *work_books = excel.querySubObject("WorkBooks");
    work_books->dynamicCall("Open (const QString&)", strFile); //打开指定文件
    QAxObject *work_book = excel.querySubObject("ActiveWorkBook");
    QString ExcelName,Name;
    QList<QString> str;
    static int row_count = 0;
    QAxObject *work_sheet = work_book->querySubObject("Sheets(int)", 1); //设置为 获取第一页 数据
    QAxObject *used_range = work_sheet->querySubObject("UsedRange");
    QAxObject *rows = used_range->querySubObject("Rows");
    row_count = rows->property("Count").toInt();  //获取行数


    //获取第一行第一列数据
    for(int i = 1;i<=row_count;i++)
    {
        Name = work_sheet->querySubObject("Cells(int,int)", i,1)->property("Value").toString();
        if(Name == Name_COMPARE)
        {
            for(int j = 1;j<=18;j++)
            {
                str.insert(j-1,work_sheet->querySubObject("Cells(int,int)", i,j)->property("Value").toString());
            }
        }
        else
        {
            continue;
        }
    }

    //获取表格中需要的数据，此处是从第三行第二列获取数据，具体原因看下图理解，根据自己的需求获取信息
    work_book->dynamicCall("Save()");
    work_book->dynamicCall("Close(Boolean)", false);  //关闭文件
    excel.dynamicCall("Quit(void)");  //退出
    return str;

}
