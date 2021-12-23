#include "chart.h"
#include "ui_chart.h"
#include <QtCharts/QChart>
#include <QtCharts/QChartView>
#include <QtCharts/QLineSeries>
#include <QtCharts/QValueAxis>
#include <QtCharts/QCategoryAxis>
#include <QFont>
#include <QStringList>
#include <QList>
#include <QFile>
#include <QFileDialog>
#include <QAxObject>
#include <QWidget>
#include <QLabel>
#include <QAbstractAxis>
#include "led.h"
#include "search_null.h"
#include "excel.h"


using namespace QtCharts;




chart::chart(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::chart)
{
    ui->setupUi(this);

    /*菜单栏*/
    QMenuBar *mBar = menuBar();
    //添加菜单
    QMenu *pFile = mBar->addMenu("校验");
    //添加菜单项，添加动作
    QAction *pNew = pFile->addAction("测试");
    connect(pNew, &QAction::triggered,
        //Lambda 表达式
        [=](){on_check_triggered();});


    /*spin box*/
    ui->Db->setRange(-10,120);
    ui->Db->setSingleStep(10);


    /*LED*/
    led_init(ui->led,GRAY,14);

    /*tab widget*/
//    ui->search_add_information_test->addTab(ui->search_Widget,"查找");
//    ui->search_add_information_test->addTab(ui->check_2,"添加信息");
//    ui->search_add_information_test->addTab(ui->test,"测试");

    /*给表格table的表头加背景*/
    ui->information_table->horizontalHeader()->setStyleSheet("QHeaderView::section{background:gray;}");
    ui->information_table_test->horizontalHeader()->setStyleSheet("QHeaderView::section{background:gray;}");
    ui->data_table->horizontalHeader()->setStyleSheet("QHeaderView::section{background:gray;}");

    /*坐标测试*/
    QChart *left_dBHz_chart = new QChart();
    QChart *right_dBHz_chart = new QChart();
    asix_dBHz(left_dBHz_chart);
    asix_dBHz(right_dBHz_chart);
    Chart_Title_Config(left_dBHz_chart,"左耳测试");
    Chart_Title_Config(right_dBHz_chart,"右耳测试");
    /*将表格放置QChartView中显示出来*/
    /*在这里需要使用控件 Graphics View 将其提升为 QtCharts::QChartView 后，直接调用即可*/
    ui->left_dBHz_chart_widget->setChart(left_dBHz_chart);
    ui->right_dBHz_chart_widget->setChart(right_dBHz_chart);

    /*AudioFormat音频配置*/
    fmt = new QAudioFormat();
    fmt->setSampleRate(44100);
    fmt->setChannelCount(1);
    fmt->setSampleSize(16);
    fmt->setCodec("audio/pcm");
    fmt->setByteOrder(QAudioFormat::LittleEndian);
    fmt->setSampleType(QAudioFormat::SignedInt);

    //定时器
    timer = new QTimer(this);

    /*网络连接*/
//    my_UdpSocket_Tx = new QUdpSocket();
    my_UdpSocket_Rx = new QUdpSocket();
    my_UdpSocket_Rx->bind(QHostAddress("192.168.1.67"),UDP_PORT_LOCAL_CHART);
    /*接收数据信号与槽函数相关联*/
    connect(my_UdpSocket_Rx, &QUdpSocket::readyRead, this, &chart::ClientReadData);
    /*定时器触发函数*/
    connect(timer, SIGNAL(timeout()), this, SLOT(onTimeout()));
}

chart::~chart()
{
    delete ui;
}

void chart::asix_dBHz(QChart* chart)
{
    QList<QString> str_x = {"125","250","500","1K","2k","4k","8k"};
    QList<QString> str_y = {"120","110","100","90","80","70","60","50","40","30","20","10","0","-10"};
    int value_x[] = {0,1,2,3,4,5,6};
    int value_y[] = {0,1,2,3,4,5,6,7,8,9,10,11,12,13};
    chart->legend()->hide();

    /*表格背景*/
    chart->setTheme(QChart::ChartThemeDark);


    QCategoryAxis *chart_axisX = new QCategoryAxis();
    QCategoryAxis *chart_axisY = new QCategoryAxis();
    /*X轴*/
    Axis_Customize_Config(chart_axisX,0,6,str_x,value_x,"Hz",true);
    /*Y轴*/
    Axis_Customize_Config(chart_axisY,0,13,str_y,value_y,"dBHL",true);


    /*字体配置*/
    QFont *font = new QFont();
    font->setFamily("楷体");
    font->setPixelSize(10);
    chart_axisX->setLabelsFont(*font);
    chart_axisY->setLabelsFont(*font);
    /*坐标轴的位置*/
    Axis_Location_Config(chart,chart_axisX,Qt::AlignBottom,chart_axisY,Qt::AlignLeft);

}



/*配置轴线：刻度是有规则的*/
/*
 * chart_axis：      轴线变量
 * min、max：        轴线的取值范围
 * TickCount：      主要尺度个数
 * MinorTickCount： 次要尺度个数
 * title：          轴线单位，代表的意义
 * flag：           是否显示表格内线条
*/
void chart::Axis_Config(QValueAxis *chart_axis,qreal min,qreal max,int TickCount,int MinorTickCount,const QString &title,bool flag)
{
    QFont *font = new QFont();
    chart_axis->setTitleFont(*font);
    font->setFamily("楷体");
    chart_axis->setMin(min);
    chart_axis->setMax(max);
    chart_axis->setTickCount(TickCount);
    chart_axis->setGridLineVisible(flag);
    chart_axis->setMinorTickCount(MinorTickCount);
    chart_axis->setTitleText(title);
    chart_axis->setLabelFormat("%d");
}

/*轴线的自定义配置：刻度是自定义的*/
void chart::Axis_Customize_Config(QCategoryAxis *chart_Axis,qreal min,qreal max, QList<QString> str_list,int value[],const QString &title,bool flag)
{
    QFont *font = new QFont();
    font->setFamily("楷体");
    chart_Axis->setRange(min,max);
    chart_Axis->setMin(min);
    chart_Axis->setMax(max);
    /*
    chart_Axis->startValue("0");
    chart_Axis->endValue("13");
    */
    chart_Axis->setStartValue(min);
    chart_Axis->setTitleText(title);
    chart_Axis->setTitleVisible(true);
    chart_Axis->setGridLineVisible(flag);
    chart_Axis->setTickCount(str_list.count());
    chart_Axis->setTitleFont(*font);
    for(int i = 0;i < str_list.count();i++)
    {
        chart_Axis->append(str_list.at(i),value[i]);
    }

    chart_Axis->setLabelsPosition(QCategoryAxis::AxisLabelsPositionOnValue);
}

/*配置坐标主题*/
/*
 * chart：表示制作的坐标系
 * title：表示坐标系的主题
*/
void chart::Chart_Title_Config(QChart *chart,const QString &title)
{
    QFont *title_font = new QFont();
    title_font->setFamily("楷体");
    chart->setTitle(title);
    chart->setTitleFont(*title_font);
}

/*配置轴线所在坐标系的位置*/
/*
 * chart：坐标系
 * chart_axis1/chart_axis2：表示坐标轴
 * alignment1、alignment2：表示坐标轴的位置         Qt::AlignBottom    Qt::AlignLeft  Qt::AlignRight  Qt::AlignTop    Qt::AlignCenter
*/
void chart::Axis_Location_Config(QChart *chart,QValueAxis *chart_axisx,Qt::Alignment alignmentx,QValueAxis *chart_axisy,Qt::Alignment alignmenty)
{

    chart->addAxis(chart_axisx,alignmentx);
    chart->addAxis(chart_axisy,alignmenty);
}


void chart::on_save_clicked()
{
    QString edit[6] = {   ui->name_Edit->text(),
                              ui->sex_Edit->currentText(),
                              QString::number(ui->birth_Edit->date().year()),
                              QString::number(ui->birth_Edit->date().month()),
                              QString::number(ui->birth_Edit->date().day()),
                              ui->note_Edit->toPlainText()};
    ui->information_table_test->setItem(0,0,new QTableWidgetItem(edit[0]));
    ui->information_table_test->setItem(0,1,new QTableWidgetItem(edit[1]));
    ui->information_table_test->setItem(0,2,new QTableWidgetItem(edit[2]+edit[3]+edit[4]));
    ui->information_table_test->setItem(0,3,new QTableWidgetItem(edit[5]));
    data_save *save = new data_save();
    save->show();
}

void chart::on_clear_clicked()
{
    ui->name_Edit->clear();
    ui->note_Edit->clear();
}


/*通过网口传递数据，包括测试音与频率，同时还包括音频单通道测试，左右耳的区分*/
int chart::on_test_botton_clicked()
{
    QByteArray data0;
//    wavctrl wav;
    QByteArray audio_wav;

//    audio_wav = wav_decode_init("C:\\Users\\Administrator\\Documents\\"+ui->Hz->currentText()+".wav",&wav);
//    for(int i=0;i<wav.datasize;i++)
//    {
//        data0.append(audio_wav.at(wav.datastart+i));
//    }

    //完成进入标准模式的功能
    data0.append(1-1);

    data0.append('H');
    data0.append('Z');
    switch (ui->Hz->currentIndex()) {
        case 0:
            data0.append((125>>8)&0xff);//1*125
            data0.append((125)&0xff);//1*125
            break;
        case 1:
            data0.append((250>>8)&0xff);//1*125
            data0.append((250)&0xff);//1*125
            break;
        case 2:
            data0.append((500>>8)&0xff);//1*125
            data0.append((500)&0xff);//1*125
            break;
        case 3:
            data0.append((1000>>8)&0xff);//1*125
            data0.append((1000)&0xff);//1*125
            break;
        case 4:
            data0.append((2000>>8)&0xff);//1*125
            data0.append((2000)&0xff);//1*125
            break;
        case 5:
            data0.append((4000>>8)&0xff);//1*125
            data0.append((4000)&0xff);//1*125
            break;
        case 6:
            data0.append((8000>>8)&0xff);//1*125
            data0.append((8000)&0xff);//1*125
            break;
        default:
            break;
    }

    data0.append('D');
    data0.append('B');
    data0.append((ui->Db->value()>>8)&0xff);
    data0.append((ui->Db->value())&0xff);
    data0.append(ui->ear_choose->currentIndex()+1);

    //传输数据
    my_UdpSocket_Rx->writeDatagram(data0,QHostAddress("192.168.1.30"),UDP_PORT_LOCAL_CHART);
    led_init(ui->led,RED,14);
    data0.clear();
    //开启定时器,定时完成表示完成相应的数据未接收到反馈
    timer->start(WAIT_TIME_MS);
    return 0;
}


/*保存获取的数据*/
void chart::on_data_test_save_clicked()
{
    QString filepath = "F:\\USST\\Undergraduate\\Senior2\\Qt\\information.xlsx";
    QList<QString> str;
    for(int i = 0;i<4;i++)
    {
        str.insert(i,ui->information_table_test->item(0,i)->text().toUtf8());
    }
    for(int i = 0;i<7;i++)
    {
        str.insert(i+4,ui->data_table->item(0,i)->text().toUtf8());
    }
    for(int i = 0;i<7;i++)
    {
         str.insert(i+11,ui->data_table->item(1,i)->text().toUtf8());
    }
    excel_WR(filepath,str);
    data_save *data_save_Dialog = new data_save();
    data_save_Dialog->show();
}
/*左耳画点*/
void chart::draw_point_left_ear(int x,int y)
{

    QAbstractAxis *axis_Y = ui->left_dBHz_chart_widget->chart()->axes(Qt::Vertical).at(0);
    QAbstractAxis *axis_X = ui->left_dBHz_chart_widget->chart()->axes(Qt::Horizontal).at(0);
    series_left->append(x,y);
    series_left->setPointsVisible(true);
    series_left->setPointLabelsColor(Qt::red);
    ui->left_dBHz_chart_widget->chart()->addSeries(series_left);
    series_left->attachAxis(axis_Y);
    series_left->attachAxis(axis_X);
    update();
}
/*右耳画点*/
void chart::draw_point_right_ear(int x, int y)
{
    QAbstractAxis *axis_Y = ui->right_dBHz_chart_widget->chart()->axes(Qt::Vertical).at(0);
    QAbstractAxis *axis_X = ui->right_dBHz_chart_widget->chart()->axes(Qt::Horizontal).at(0);
    series_right->setPointsVisible(true);
    series_right->setPointLabelsColor(Qt::red);
    ui->right_dBHz_chart_widget->chart()->addSeries(series_right);
    series_right->attachAxis(axis_Y);
    series_right->attachAxis(axis_X);
    series_right->append(x,y);
    update();
}
/*清除坐标点*/
void chart::clear_point_ears(void)
{
    series_left->clear();
    series_right->clear();
}
/*查找信息*/
void chart::on_search_Button_clicked()
{
    int i;
    QList<QString> str;
    QString name = ui->search_Edit->text().toUtf8();
    //查找信息
    QString filepath = "F:\\USST\\Undergraduate\\Senior2\\Qt\\information.xlsx";
    str = excel_RD(filepath,name);
    //如果不存在，就弹出窗口
    if(str.isEmpty())   {search_null *search = new search_null(); search->show();}
    //如果存在，就显示
   else
    {
        clear_point_ears();
       for(i=0;i<4;i++)
       {
           ui->information_table->setItem(0,i,new QTableWidgetItem(str.at(i)));
           ui->information_table_test->setItem(0,i,new QTableWidgetItem(str.at(i)));
       }
       for(i=0;i<7;i++)
       {
           ui->data_table->setItem(0,i,new QTableWidgetItem(str.at(i+4)));
           ui->data_table->setItem(1,i,new QTableWidgetItem(str.at(i+11)));
           draw_point_left_ear(i,(120-str.at(i+4).toInt())/10);
           draw_point_right_ear(i,(120-str.at(i+11).toInt())/10);
       }
    }
}
/*测试前清空坐标*/
void chart::on_clear_botton_clicked()
{
    clear_point_ears();
}

/*网口通信接收数据*/
int chart::ClientReadData()
{
    QString flag = ui->ear_choose->currentText().toUtf8();
    QByteArray buffer_arr;
    QHostAddress *host = nullptr;
    quint16 *port = nullptr;
    /*接收到数据，关闭定时器*/
    timer->stop();

    /*客户机发送信号时发送的信号为OK和NO*/
    while (my_UdpSocket_Rx->hasPendingDatagrams())
    {
        buffer_arr.resize(my_UdpSocket_Rx->pendingDatagramSize());
        my_UdpSocket_Rx->readDatagram(buffer_arr.data(),buffer_arr.size(),host,port);
        int y = ui->Db->value();
        y = (120 - y)/10;
        int x = ui->Hz->currentIndex();
        if(buffer_arr == "OK")
        {
            if(flag == "左耳")
            {
                ui->data_table->setItem(0,x,new QTableWidgetItem(ui->Db->text()));
                draw_point_left_ear(x,y);

            }
            if(flag == "右耳")
            {
                ui->data_table->setItem(1,x,new QTableWidgetItem(ui->Db->text()));
                draw_point_right_ear(x,y);
            }
            //如果传回反应
            led_init(ui->led,GREEN,14);
            return 0;
        }
        else
        {
             led_init(ui->led,GRAY,14);
             return 1;
        }


    }
    return 0;
}


/*校验设备*/
void chart::on_check_triggered()
{
    QByteArray data0;
    test *check_test = new test();
    check_test->show();

    data0.append(1);    //传输指令完成校准模式的切换
    //传输数据
    my_UdpSocket_Rx->writeDatagram(data0,QHostAddress("192.168.1.30"),UDP_PORT_LOCAL_CHART);
    data0.clear();  //清空指令等待下次传输
}

void chart::on_call_botton_pressed()
{
    char buf[4096] = {0};
    audio_in = new QAudioInput(*fmt);
    audio_out = new QAudioOutput(*fmt);
    QIODevice *in_io = audio_in->start();
    for(;;)
    {
        in_io->read(buf,4096);
        my_UdpSocket_Rx->writeDatagram(buf,QHostAddress("192.168.1.30"),UDP_PORT_LOCAL_CHART);
    }
}

void chart::onTimeout()
{
    led_init(ui->led,GRAY,14);
}

void chart::on_call_botton_released()
{
    audio_in->stop();
}



//延时函数
void chart::delay(int msec)
{
    QTime n = QTime::currentTime();
    QTime now;
    do{
        now = QTime::currentTime();
    }while(n.msecsTo(now)<=msec);
}

