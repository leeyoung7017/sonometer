#ifndef CHART_H
#define CHART_H

#include <QMainWindow>
#include <iostream>
#include <QtCharts/QChart>
#include <QtCharts/QChartView>
#include <QtCharts/QLineSeries>
#include <QtCharts/QValueAxis>
#include <QtCharts/QCategoryAxis>
#include <QStringList>
#include <QList>
#include <QFile>
#include "data_save.h"
#include <QAxObject>
#include <QWidget>
#include "excel.h"
#include <QUdpSocket>
#include <QAudioFormat>
#include <QAudioInput>
#include <QAudioOutput>
#include <QMenuBar>
#include "test.h"
#include "wav.h"
#include <QThread>
#include <QTimer>
#include <QTime>

#define UDP_PORT_LOCAL_CHART 8080
#define LENGTH_DATA 490
extern unsigned int BufferData[LENGTH_DATA];
QT_BEGIN_NAMESPACE
namespace Ui { class chart; }
using namespace QtCharts;
using namespace std;
QT_END_NAMESPACE

#define GRAY 0
#define RED 1
#define GREEN 2
#define WAIT_TIME_MS 5000

class chart : public QMainWindow
{
    Q_OBJECT

public:

    QLineSeries *series_left = new QLineSeries();
    QLineSeries *series_right = new QLineSeries();

    /*网口对象*/
//    QUdpSocket *my_UdpSocket_Tx;
    QUdpSocket *my_UdpSocket_Rx;

    chart(QWidget *parent = nullptr);
    void Axis_Config(QValueAxis *chart_axis,qreal min,qreal max,int TickCount,int MinorTickCount,const QString &title,bool flag);
    void Axis_Customize_Config(QCategoryAxis *chart_Axis,qreal min,qreal max, QList<QString> str_list,int value[],const QString &title,bool flag);
    void Axis_Location_Config(QChart *chart,QValueAxis *chart_axisx,Qt::Alignment alignmentx,QValueAxis *chart_axisy, Qt::Alignment alignmenty);
    void Chart_Title_Config(QChart *chart,const QString &title);
    void asix_dBHz(QChart* chart);



    void Excel_opera(void);

    void search_information_widget();

    void draw_point_left_ear(int x,int y);
    void draw_point_right_ear(int x,int y);
    void clear_point_ears(void);

    void delay(int msec);
    //clear *clear_dialog;
    ~chart();


private slots:

    void on_save_clicked();

    void on_clear_clicked();

    int on_test_botton_clicked();

    void on_data_test_save_clicked();

    void on_search_Button_clicked();

    void on_clear_botton_clicked();

    void onTimeout();

    int ClientReadData();

    void on_check_triggered();

    void on_call_botton_pressed();

    void on_call_botton_released();

private:
    Ui::chart *ui;
    QAudioDeviceInfo info = QAudioDeviceInfo::defaultInputDevice();
    QAudioFormat *fmt;
    QAudioInput *audio_in;
    QAudioOutput *audio_out;
    QTimer *timer;

};
#endif // CHART_H
