#include "chart.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    chart w;
    w.show();
    return a.exec();
}
