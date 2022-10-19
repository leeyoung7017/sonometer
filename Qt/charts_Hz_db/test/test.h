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

#define N 512   //采样点数
#define Sample  512//128000 //采样率
#define FreqStandard 100//1000  //音频频率

class test : public QWidget
{
    Q_OBJECT

public:
    explicit test(QWidget *parent = nullptr);
    ~test();
    void QCustomplot_Init(QCustomPlot *widget, int x_range, int y_range);
    double GetTHD(double F_data[N], int realFreq, int NumHarmonic);
    double *GetFreqDeviation(double F_data[N]);
    double GetSPL(double *data);
    double GetSNR(double data[N],double data_standard[N]);

private slots:
    void on_ButtonDisplayFFT_clicked();

    void on_ButtonDisplayData_clicked();

private:
    Ui::test *ui;
    double F[N] = { 0 };
};

#endif // TEST_H
