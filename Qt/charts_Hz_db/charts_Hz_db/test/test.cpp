#include "test.h"
#include "ui_test.h"


static int i=0;

test::test(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::test)
{
    ui->setupUi(this);



    /*将表格放置QChartView中显示出来*/
    /*在这里需要使用控件 Graphics View 将其提升为 QtCharts::QChartView 后，直接调用即可*/
    ui->chart_view->setChart(chart);
    ui->chart_ret_view->setChart(chart_ret);

    /*坐标轴配置*/
    axis_chart(chart,series);
    axis_chart(chart_ret,series_ret);
    /*表格抬头配置*/
    QFont *title_font = new QFont();
    title_font->setFamily("楷体");
    chart->setTitle("原始数据");
    chart->setTitleFont(*title_font);
    chart_ret->setTitle("返回数据");
    chart_ret->setTitleFont(*title_font);

    /*点数据的添加*/

    chart_ret->addSeries(series_ret);

    /*UDP网口对象*/
    my_udpsocket_tx = new QUdpSocket(this);
    my_udpsocket_rx = new QUdpSocket(this);
    my_udpsocket_rx->bind(QHostAddress::Any,UDP_PORT_LOCAL_TEST);

    /*UDP接收信号与槽函数的关联*/
    connect(my_udpsocket_rx,&QUdpSocket::readyRead,this,&test::receiveData);
}

test::~test()
{
    delete ui;
}

void test::axis_chart(QChart* chart,QSplineSeries *series)
{
    chart->legend()->hide();

    /*表格背景*/
    chart->setTheme(QChart::ChartThemeDark);

    /*坐标轴对象定义*/
    QValueAxis *chart_axisY = new QValueAxis();
    QValueAxis *chart_axisX = new QValueAxis();


    /*X轴*/
    chart_axisX->setRange(0,300);
    chart_axisX->setTickCount(15);
    chart_axisX->setGridLineVisible(true);
    chart_axisX->setTitleText("DbHL");
    chart_axisX->setLabelFormat("%d");
    /*Y轴*/
    chart_axisY->setRange(-128,128);
    chart_axisY->setTickCount(17);
    chart_axisY->setGridLineVisible(true);
    chart_axisY->setTitleText("time");
    chart_axisY->setLabelFormat("%d");


    /*字体配置*/
    QFont *font = new QFont();
    font->setFamily("楷体");
    font->setPixelSize(10);
    chart_axisX->setLabelsFont(*font);
    chart_axisY->setLabelsFont(*font);
    /*坐标轴的位置*/
    chart->addAxis(chart_axisX,Qt::AlignBottom);
    chart->addAxis(chart_axisY,Qt::AlignLeft);
    chart->addSeries(series);
    series->attachAxis(chart_axisX);
    series->attachAxis(chart_axisY);


}

/*删除曲线*/
void test::delete_series(QSplineSeries *series)
{
    series->clear();
}


/*传递数据*/
void test::on_data_button_clicked()
{

    /*读取pcm文件数据*/
    QByteArray arr = pcm_read("C:\\Users\\Administrator\\Documents\\1k_24_4M8.pcm");

//        QList<int> data;
        for(int i = 0; i<160;i++)
        {
//            data[i] = arr.at(i);
//            if(data.at(i)>128)
//            {
//                data[i] = data.at(i) - 256;
//            }

            /*整型转字符串*//*一个数据一个数据十进制的传输*/
            //arr = QString::number(data.at(i),10);


            /*将字符串数据传输到UDP服务端*/
            my_udpsocket_tx->writeDatagram(QString::number(arr.at(i),10).toUtf8()  +" ",QHostAddress("192.168.137.1"),8080);
//            series->setPointsVisible(true);

            series->append(i,arr.at(i));
        }



}

/*接收数据*/
/*
 * 接收的数据分为两个部分：
 *                      1.数据来自仿真耳
 *                      2.数据来自测试耳机
 * 其中两者的数据都是通过在相同的环境下，不同时间采用同一ADC获取的数据，因此具有可比性，查看数据的误差，对数据进行检测，可以检测设备的误差与好坏
*/
void test::receiveData()
{

/*获取字符串*/
    QByteArray datagram;

    while (my_udpsocket_rx->hasPendingDatagrams())
       {

            datagram.resize(my_udpsocket_rx->pendingDatagramSize());
        /*UDP服务端的IP地址和端口号*/
            QHostAddress sender;
            quint16 senderPort;
        /*接收服务端的数据*/
            my_udpsocket_rx->readDatagram(datagram.data(), datagram.size(), &sender, &senderPort);
        /*datagram  为数据存储的内容*/

         }
    /*点使能显示*/
    series_ret->setPointsVisible(true);
    series->setPointsVisible(true);
    if(ui->Audio_Standard->isChecked())
    {
        series_ret->append(i,datagram.toInt());
    }
    else
    {
        series->append(i,datagram.toInt());
    }

    i++;
}

void test::on_clear_clicked()
{
    i=0;
    if(ui->Audio_Standard->isChecked())
    {
        delete_series(series_ret);
    }
    else
    {
        delete_series(series);
    }
}
