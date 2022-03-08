#ifndef TEST_H
#define TEST_H

#include <QWidget>
#include "qcustomplot/qcustomplot.h"
#include "chart.h"

namespace Ui {
class test;
}

class test : public QWidget
{
    Q_OBJECT

public:
    explicit test(QWidget *parent = nullptr);
    ~test();
    void QCustomplot_Init(QCustomPlot *widget, int x_range, int y_range);
private slots:
    void on_ButtonDisplayFFT_clicked();

    void on_ButtonDisplayData_clicked();

private:
    Ui::test *ui;
};

#endif // TEST_H
