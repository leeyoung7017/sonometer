#ifndef TEST_H
#define TEST_H

#include <QWidget>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "qcustomplot/qcustomplot.h"
#include "chart.h"
#include "FFT.h"
//#include "../FFT/fft1.h"

namespace Ui {
class test;
}

#define N 490
#define Sample  128000
#define FreqStandard 1000

class test : public QWidget
{
    Q_OBJECT

public:
    explicit test(QWidget *parent = nullptr);
    ~test();
    void QCustomplot_Init(QCustomPlot *widget, int x_range, int y_range);
    double GetTHD(double F_data[N], int NumHarmonic);
    double GetFreqDeviation(double F_data[N]);
    double GetSPL(double *data);
private slots:
    void on_ButtonDisplayFFT_clicked();

    void on_ButtonDisplayData_clicked();

private:
    Ui::test *ui;
    double F[N] = { 0 };
};

#endif // TEST_H
