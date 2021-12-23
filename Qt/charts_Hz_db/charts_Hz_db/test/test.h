#ifndef TEST_H
#define TEST_H

#include <QMainWindow>
#include <QtCharts/QChart>
#include <QtCharts/QChartView>
#include <QtCharts/QLineSeries>
#include <QtCharts/QValueAxis>
#include <QtCharts/QCategoryAxis>
#include <QtCharts/QDateTimeAxis>
#include <QtCharts/QSplineSeries>
#include <QFileDialog>
#include <QFile>
#include <QtCharts/QChartView>
#include <QUdpSocket>
#include <QHostAddress>
#include <math.h>
#include "pcm.h"
#include <QCloseEvent>
#include "chart.h"

#define UDP_PORT_LOCAL_TEST 6678

namespace Ui {
class test;
}
using namespace QtCharts;
using namespace std;

class test : public QMainWindow
{
    Q_OBJECT

public:
    explicit test(QWidget *parent = nullptr);
    ~test();

    /*表格对象定义*/
    QChart *chart = new QChart();
    QChart *chart_ret = new QChart();

    QUdpSocket *my_udpsocket_tx;
    QUdpSocket *my_udpsocket_rx;

    QSplineSeries  *series = new QSplineSeries();
    QSplineSeries *series_ret = new QSplineSeries();


    void axis_chart(QChart* chart, QSplineSeries *series);
    void Axis_Config(QValueAxis *chart_axis,qreal min,qreal max,int TickCount,int MinorTickCount,const QString &title,bool flag);
    void Axis_Customize_Config(QCategoryAxis *chart_Axis,qreal min,qreal max, QList<QString> str_list,int value[],const QString &title,bool flag);
    void Axis_Location_Config(QChart *chart,QValueAxis *chart_axisx,Qt::Alignment alignmentx,QValueAxis *chart_axisy, Qt::Alignment alignmenty);
    void Chart_Title_Config(QChart *chart,const QString &title);
    void delete_series(QSplineSeries *series);

protected:
    void closeEvent(QCloseEvent *event);//窗口关闭触发事件

private slots:
    void on_data_button_clicked();
    void receiveData();

    void on_clear_clicked();

private:
    Ui::test *ui;
};

#endif // TEST_H
