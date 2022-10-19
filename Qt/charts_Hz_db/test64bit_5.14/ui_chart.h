/********************************************************************************
** Form generated from reading UI file 'chart.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CHART_H
#define UI_CHART_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDateEdit>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QSplitter>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include <qchartview.h>

QT_BEGIN_NAMESPACE

class Ui_chart
{
public:
    QAction *check;
    QWidget *centralwidget;
    QHBoxLayout *horizontalLayout_2;
    QSplitter *splitter;
    QWidget *verticalLayoutWidget_2;
    QVBoxLayout *chart_2;
    QtCharts::QChartView *left_dBHz_chart_widget;
    QSpacerItem *verticalSpacer;
    QtCharts::QChartView *right_dBHz_chart_widget;
    QTabWidget *tabWidget;
    QWidget *tab_3;
    QWidget *search_Widget;
    QTableWidget *information_table;
    QLineEdit *search_Edit;
    QPushButton *search_Button;
    QWidget *tab_4;
    QWidget *check_2;
    QWidget *verticalLayoutWidget;
    QVBoxLayout *verticalLayout;
    QGridLayout *gridLayout;
    QComboBox *sex_Edit;
    QLineEdit *name_Edit;
    QLabel *name_label;
    QLabel *birth_label;
    QLabel *sex_label;
    QDateEdit *birth_Edit;
    QHBoxLayout *horizontalLayout;
    QLabel *note_label;
    QTextEdit *note_Edit;
    QHBoxLayout *horizontalLayout_4;
    QSpacerItem *horizontalSpacer;
    QPushButton *save;
    QSpacerItem *horizontalSpacer_4;
    QPushButton *clear;
    QSpacerItem *horizontalSpacer_3;
    QWidget *tab_5;
    QWidget *test;
    QWidget *gridLayoutWidget;
    QGridLayout *gridLayout_2;
    QLabel *led;
    QComboBox *Hz;
    QLabel *label;
    QSpinBox *Db;
    QPushButton *test_botton;
    QPushButton *call_botton;
    QComboBox *ear_choose;
    QLabel *label_2;
    QLabel *ear_label;
    QPushButton *clear_botton;
    QPushButton *data_test_save;
    QLabel *label_3;
    QLabel *label_5;
    QHBoxLayout *horizontalLayout_3;
    QLineEdit *timeEdit;
    QLabel *label_6;
    QPushButton *test_over;
    QSplitter *splitter_2;
    QTableWidget *information_table_test;
    QTableWidget *data_table;
    QLabel *label_4;

    void setupUi(QMainWindow *chart)
    {
        if (chart->objectName().isEmpty())
            chart->setObjectName(QString::fromUtf8("chart"));
        chart->resize(1029, 777);
        check = new QAction(chart);
        check->setObjectName(QString::fromUtf8("check"));
        check->setCheckable(true);
        centralwidget = new QWidget(chart);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        horizontalLayout_2 = new QHBoxLayout(centralwidget);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        splitter = new QSplitter(centralwidget);
        splitter->setObjectName(QString::fromUtf8("splitter"));
        splitter->setOrientation(Qt::Horizontal);
        verticalLayoutWidget_2 = new QWidget(splitter);
        verticalLayoutWidget_2->setObjectName(QString::fromUtf8("verticalLayoutWidget_2"));
        chart_2 = new QVBoxLayout(verticalLayoutWidget_2);
        chart_2->setObjectName(QString::fromUtf8("chart_2"));
        chart_2->setContentsMargins(0, 0, 0, 0);
        left_dBHz_chart_widget = new QtCharts::QChartView(verticalLayoutWidget_2);
        left_dBHz_chart_widget->setObjectName(QString::fromUtf8("left_dBHz_chart_widget"));

        chart_2->addWidget(left_dBHz_chart_widget);

        verticalSpacer = new QSpacerItem(20, 20, QSizePolicy::Minimum, QSizePolicy::Fixed);

        chart_2->addItem(verticalSpacer);

        right_dBHz_chart_widget = new QtCharts::QChartView(verticalLayoutWidget_2);
        right_dBHz_chart_widget->setObjectName(QString::fromUtf8("right_dBHz_chart_widget"));

        chart_2->addWidget(right_dBHz_chart_widget);

        splitter->addWidget(verticalLayoutWidget_2);
        tabWidget = new QTabWidget(splitter);
        tabWidget->setObjectName(QString::fromUtf8("tabWidget"));
        tab_3 = new QWidget();
        tab_3->setObjectName(QString::fromUtf8("tab_3"));
        search_Widget = new QWidget(tab_3);
        search_Widget->setObjectName(QString::fromUtf8("search_Widget"));
        search_Widget->setGeometry(QRect(10, 10, 551, 737));
        information_table = new QTableWidget(search_Widget);
        if (information_table->columnCount() < 4)
            information_table->setColumnCount(4);
        QFont font;
        font.setFamily(QString::fromUtf8("\346\245\267\344\275\223"));
        font.setPointSize(12);
        font.setBold(true);
        font.setWeight(75);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        __qtablewidgetitem->setFont(font);
        information_table->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        __qtablewidgetitem1->setFont(font);
        information_table->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        __qtablewidgetitem2->setFont(font);
        information_table->setHorizontalHeaderItem(2, __qtablewidgetitem2);
        QTableWidgetItem *__qtablewidgetitem3 = new QTableWidgetItem();
        __qtablewidgetitem3->setFont(font);
        information_table->setHorizontalHeaderItem(3, __qtablewidgetitem3);
        if (information_table->rowCount() < 1)
            information_table->setRowCount(1);
        QTableWidgetItem *__qtablewidgetitem4 = new QTableWidgetItem();
        __qtablewidgetitem4->setFont(font);
        information_table->setVerticalHeaderItem(0, __qtablewidgetitem4);
        QFont font1;
        font1.setFamily(QString::fromUtf8("\346\245\267\344\275\223"));
        font1.setPointSize(12);
        QTableWidgetItem *__qtablewidgetitem5 = new QTableWidgetItem();
        __qtablewidgetitem5->setFont(font1);
        information_table->setItem(0, 0, __qtablewidgetitem5);
        QTableWidgetItem *__qtablewidgetitem6 = new QTableWidgetItem();
        __qtablewidgetitem6->setFont(font1);
        information_table->setItem(0, 1, __qtablewidgetitem6);
        QTableWidgetItem *__qtablewidgetitem7 = new QTableWidgetItem();
        __qtablewidgetitem7->setFont(font1);
        information_table->setItem(0, 2, __qtablewidgetitem7);
        QTableWidgetItem *__qtablewidgetitem8 = new QTableWidgetItem();
        __qtablewidgetitem8->setTextAlignment(Qt::AlignCenter);
        __qtablewidgetitem8->setFont(font1);
        information_table->setItem(0, 3, __qtablewidgetitem8);
        information_table->setObjectName(QString::fromUtf8("information_table"));
        information_table->setGeometry(QRect(0, 10, 419, 192));
        QSizePolicy sizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(information_table->sizePolicy().hasHeightForWidth());
        information_table->setSizePolicy(sizePolicy);
        information_table->setMaximumSize(QSize(16777215, 16777215));
        information_table->setLayoutDirection(Qt::LeftToRight);
        information_table->setLineWidth(5);
        search_Edit = new QLineEdit(search_Widget);
        search_Edit->setObjectName(QString::fromUtf8("search_Edit"));
        search_Edit->setGeometry(QRect(430, 20, 108, 22));
        QSizePolicy sizePolicy1(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(search_Edit->sizePolicy().hasHeightForWidth());
        search_Edit->setSizePolicy(sizePolicy1);
        search_Button = new QPushButton(search_Widget);
        search_Button->setObjectName(QString::fromUtf8("search_Button"));
        search_Button->setGeometry(QRect(460, 50, 80, 20));
        sizePolicy1.setHeightForWidth(search_Button->sizePolicy().hasHeightForWidth());
        search_Button->setSizePolicy(sizePolicy1);
        search_Button->setFocusPolicy(Qt::StrongFocus);
        search_Button->setContextMenuPolicy(Qt::DefaultContextMenu);
        search_Button->setLayoutDirection(Qt::LeftToRight);
        search_Button->setAutoDefault(false);
        search_Button->setFlat(false);
        search_Edit->raise();
        search_Button->raise();
        information_table->raise();
        tabWidget->addTab(tab_3, QString());
        tab_4 = new QWidget();
        tab_4->setObjectName(QString::fromUtf8("tab_4"));
        check_2 = new QWidget(tab_4);
        check_2->setObjectName(QString::fromUtf8("check_2"));
        check_2->setGeometry(QRect(20, 20, 421, 737));
        verticalLayoutWidget = new QWidget(check_2);
        verticalLayoutWidget->setObjectName(QString::fromUtf8("verticalLayoutWidget"));
        verticalLayoutWidget->setGeometry(QRect(10, 10, 430, 261));
        verticalLayout = new QVBoxLayout(verticalLayoutWidget);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        gridLayout = new QGridLayout();
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        sex_Edit = new QComboBox(verticalLayoutWidget);
        sex_Edit->addItem(QString());
        sex_Edit->addItem(QString());
        sex_Edit->setObjectName(QString::fromUtf8("sex_Edit"));

        gridLayout->addWidget(sex_Edit, 0, 3, 1, 1);

        name_Edit = new QLineEdit(verticalLayoutWidget);
        name_Edit->setObjectName(QString::fromUtf8("name_Edit"));

        gridLayout->addWidget(name_Edit, 0, 1, 1, 1);

        name_label = new QLabel(verticalLayoutWidget);
        name_label->setObjectName(QString::fromUtf8("name_label"));

        gridLayout->addWidget(name_label, 0, 0, 1, 1);

        birth_label = new QLabel(verticalLayoutWidget);
        birth_label->setObjectName(QString::fromUtf8("birth_label"));

        gridLayout->addWidget(birth_label, 0, 4, 1, 1);

        sex_label = new QLabel(verticalLayoutWidget);
        sex_label->setObjectName(QString::fromUtf8("sex_label"));

        gridLayout->addWidget(sex_label, 0, 2, 1, 1);

        birth_Edit = new QDateEdit(verticalLayoutWidget);
        birth_Edit->setObjectName(QString::fromUtf8("birth_Edit"));

        gridLayout->addWidget(birth_Edit, 0, 5, 1, 1);


        verticalLayout->addLayout(gridLayout);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        note_label = new QLabel(verticalLayoutWidget);
        note_label->setObjectName(QString::fromUtf8("note_label"));

        horizontalLayout->addWidget(note_label);

        note_Edit = new QTextEdit(verticalLayoutWidget);
        note_Edit->setObjectName(QString::fromUtf8("note_Edit"));
        QSizePolicy sizePolicy2(QSizePolicy::Expanding, QSizePolicy::Fixed);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(note_Edit->sizePolicy().hasHeightForWidth());
        note_Edit->setSizePolicy(sizePolicy2);

        horizontalLayout->addWidget(note_Edit);


        verticalLayout->addLayout(horizontalLayout);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        horizontalSpacer = new QSpacerItem(80, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer);

        save = new QPushButton(verticalLayoutWidget);
        save->setObjectName(QString::fromUtf8("save"));
        sizePolicy1.setHeightForWidth(save->sizePolicy().hasHeightForWidth());
        save->setSizePolicy(sizePolicy1);

        horizontalLayout_4->addWidget(save);

        horizontalSpacer_4 = new QSpacerItem(56, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer_4);

        clear = new QPushButton(verticalLayoutWidget);
        clear->setObjectName(QString::fromUtf8("clear"));
        sizePolicy1.setHeightForWidth(clear->sizePolicy().hasHeightForWidth());
        clear->setSizePolicy(sizePolicy1);

        horizontalLayout_4->addWidget(clear);

        horizontalSpacer_3 = new QSpacerItem(80, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer_3);


        verticalLayout->addLayout(horizontalLayout_4);

        tabWidget->addTab(tab_4, QString());
        tab_5 = new QWidget();
        tab_5->setObjectName(QString::fromUtf8("tab_5"));
        test = new QWidget(tab_5);
        test->setObjectName(QString::fromUtf8("test"));
        test->setGeometry(QRect(10, 20, 441, 737));
        gridLayoutWidget = new QWidget(test);
        gridLayoutWidget->setObjectName(QString::fromUtf8("gridLayoutWidget"));
        gridLayoutWidget->setGeometry(QRect(60, 430, 320, 142));
        gridLayout_2 = new QGridLayout(gridLayoutWidget);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        gridLayout_2->setContentsMargins(0, 0, 0, 0);
        led = new QLabel(gridLayoutWidget);
        led->setObjectName(QString::fromUtf8("led"));
        led->setLayoutDirection(Qt::RightToLeft);
        led->setFrameShadow(QFrame::Sunken);
        led->setAlignment(Qt::AlignCenter);

        gridLayout_2->addWidget(led, 2, 2, 1, 1);

        Hz = new QComboBox(gridLayoutWidget);
        Hz->addItem(QString());
        Hz->addItem(QString());
        Hz->addItem(QString());
        Hz->addItem(QString());
        Hz->addItem(QString());
        Hz->addItem(QString());
        Hz->addItem(QString());
        Hz->addItem(QString());
        Hz->addItem(QString());
        Hz->setObjectName(QString::fromUtf8("Hz"));
        Hz->setFont(font1);
        Hz->setEditable(false);
        Hz->setInsertPolicy(QComboBox::InsertAtBottom);
        Hz->setIconSize(QSize(15, 15));
        Hz->setFrame(true);

        gridLayout_2->addWidget(Hz, 2, 1, 1, 1);

        label = new QLabel(gridLayoutWidget);
        label->setObjectName(QString::fromUtf8("label"));
        label->setFont(font1);

        gridLayout_2->addWidget(label, 2, 0, 1, 1);

        Db = new QSpinBox(gridLayoutWidget);
        Db->setObjectName(QString::fromUtf8("Db"));
        Db->setFont(font1);
        Db->setContextMenuPolicy(Qt::DefaultContextMenu);
        Db->setLayoutDirection(Qt::LeftToRight);
        Db->setAlignment(Qt::AlignCenter);

        gridLayout_2->addWidget(Db, 1, 1, 1, 1);

        test_botton = new QPushButton(gridLayoutWidget);
        test_botton->setObjectName(QString::fromUtf8("test_botton"));
        test_botton->setFont(font1);

        gridLayout_2->addWidget(test_botton, 3, 1, 1, 1);

        call_botton = new QPushButton(gridLayoutWidget);
        call_botton->setObjectName(QString::fromUtf8("call_botton"));
        call_botton->setFont(font1);

        gridLayout_2->addWidget(call_botton, 0, 2, 1, 1);

        ear_choose = new QComboBox(gridLayoutWidget);
        ear_choose->addItem(QString());
        ear_choose->addItem(QString());
        ear_choose->setObjectName(QString::fromUtf8("ear_choose"));
        ear_choose->setFont(font1);

        gridLayout_2->addWidget(ear_choose, 0, 1, 1, 1);

        label_2 = new QLabel(gridLayoutWidget);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setFont(font1);

        gridLayout_2->addWidget(label_2, 1, 0, 1, 1);

        ear_label = new QLabel(gridLayoutWidget);
        ear_label->setObjectName(QString::fromUtf8("ear_label"));
        ear_label->setFont(font1);

        gridLayout_2->addWidget(ear_label, 0, 0, 1, 1);

        clear_botton = new QPushButton(gridLayoutWidget);
        clear_botton->setObjectName(QString::fromUtf8("clear_botton"));
        clear_botton->setFont(font1);

        gridLayout_2->addWidget(clear_botton, 3, 0, 1, 1);

        data_test_save = new QPushButton(gridLayoutWidget);
        data_test_save->setObjectName(QString::fromUtf8("data_test_save"));
        QSizePolicy sizePolicy3(QSizePolicy::Maximum, QSizePolicy::Maximum);
        sizePolicy3.setHorizontalStretch(0);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(data_test_save->sizePolicy().hasHeightForWidth());
        data_test_save->setSizePolicy(sizePolicy3);
        data_test_save->setFont(font1);

        gridLayout_2->addWidget(data_test_save, 3, 2, 1, 1);

        label_3 = new QLabel(gridLayoutWidget);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setFont(font1);

        gridLayout_2->addWidget(label_3, 1, 2, 1, 1);

        label_5 = new QLabel(gridLayoutWidget);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        label_5->setFont(font1);

        gridLayout_2->addWidget(label_5, 4, 0, 1, 1);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        timeEdit = new QLineEdit(gridLayoutWidget);
        timeEdit->setObjectName(QString::fromUtf8("timeEdit"));
        timeEdit->setLayoutDirection(Qt::LeftToRight);
        timeEdit->setAlignment(Qt::AlignCenter);

        horizontalLayout_3->addWidget(timeEdit);

        label_6 = new QLabel(gridLayoutWidget);
        label_6->setObjectName(QString::fromUtf8("label_6"));
        label_6->setFont(font1);

        horizontalLayout_3->addWidget(label_6);


        gridLayout_2->addLayout(horizontalLayout_3, 4, 1, 1, 1);

        test_over = new QPushButton(gridLayoutWidget);
        test_over->setObjectName(QString::fromUtf8("test_over"));
        sizePolicy3.setHeightForWidth(test_over->sizePolicy().hasHeightForWidth());
        test_over->setSizePolicy(sizePolicy3);
        test_over->setFont(font1);

        gridLayout_2->addWidget(test_over, 4, 2, 1, 1);

        splitter_2 = new QSplitter(test);
        splitter_2->setObjectName(QString::fromUtf8("splitter_2"));
        splitter_2->setGeometry(QRect(0, 10, 441, 384));
        splitter_2->setOrientation(Qt::Vertical);
        information_table_test = new QTableWidget(splitter_2);
        if (information_table_test->columnCount() < 4)
            information_table_test->setColumnCount(4);
        QTableWidgetItem *__qtablewidgetitem9 = new QTableWidgetItem();
        __qtablewidgetitem9->setFont(font);
        information_table_test->setHorizontalHeaderItem(0, __qtablewidgetitem9);
        QTableWidgetItem *__qtablewidgetitem10 = new QTableWidgetItem();
        __qtablewidgetitem10->setFont(font);
        information_table_test->setHorizontalHeaderItem(1, __qtablewidgetitem10);
        QTableWidgetItem *__qtablewidgetitem11 = new QTableWidgetItem();
        __qtablewidgetitem11->setFont(font);
        information_table_test->setHorizontalHeaderItem(2, __qtablewidgetitem11);
        QTableWidgetItem *__qtablewidgetitem12 = new QTableWidgetItem();
        __qtablewidgetitem12->setFont(font);
        information_table_test->setHorizontalHeaderItem(3, __qtablewidgetitem12);
        if (information_table_test->rowCount() < 1)
            information_table_test->setRowCount(1);
        QTableWidgetItem *__qtablewidgetitem13 = new QTableWidgetItem();
        __qtablewidgetitem13->setFont(font);
        information_table_test->setVerticalHeaderItem(0, __qtablewidgetitem13);
        QBrush brush(QColor(0, 0, 0, 255));
        brush.setStyle(Qt::NoBrush);
        QTableWidgetItem *__qtablewidgetitem14 = new QTableWidgetItem();
        __qtablewidgetitem14->setFont(font1);
        __qtablewidgetitem14->setBackground(brush);
        information_table_test->setItem(0, 0, __qtablewidgetitem14);
        QTableWidgetItem *__qtablewidgetitem15 = new QTableWidgetItem();
        __qtablewidgetitem15->setFont(font1);
        information_table_test->setItem(0, 1, __qtablewidgetitem15);
        QTableWidgetItem *__qtablewidgetitem16 = new QTableWidgetItem();
        __qtablewidgetitem16->setFont(font1);
        information_table_test->setItem(0, 2, __qtablewidgetitem16);
        QTableWidgetItem *__qtablewidgetitem17 = new QTableWidgetItem();
        __qtablewidgetitem17->setTextAlignment(Qt::AlignCenter);
        __qtablewidgetitem17->setFont(font1);
        information_table_test->setItem(0, 3, __qtablewidgetitem17);
        information_table_test->setObjectName(QString::fromUtf8("information_table_test"));
        sizePolicy.setHeightForWidth(information_table_test->sizePolicy().hasHeightForWidth());
        information_table_test->setSizePolicy(sizePolicy);
        information_table_test->setMaximumSize(QSize(16777215, 16777215));
        information_table_test->setLayoutDirection(Qt::LeftToRight);
        information_table_test->setLineWidth(5);
        splitter_2->addWidget(information_table_test);
        data_table = new QTableWidget(splitter_2);
        if (data_table->columnCount() < 10)
            data_table->setColumnCount(10);
        QTableWidgetItem *__qtablewidgetitem18 = new QTableWidgetItem();
        __qtablewidgetitem18->setFont(font);
        data_table->setHorizontalHeaderItem(0, __qtablewidgetitem18);
        QTableWidgetItem *__qtablewidgetitem19 = new QTableWidgetItem();
        __qtablewidgetitem19->setFont(font);
        data_table->setHorizontalHeaderItem(1, __qtablewidgetitem19);
        QTableWidgetItem *__qtablewidgetitem20 = new QTableWidgetItem();
        __qtablewidgetitem20->setFont(font);
        data_table->setHorizontalHeaderItem(2, __qtablewidgetitem20);
        QTableWidgetItem *__qtablewidgetitem21 = new QTableWidgetItem();
        __qtablewidgetitem21->setFont(font);
        data_table->setHorizontalHeaderItem(3, __qtablewidgetitem21);
        QTableWidgetItem *__qtablewidgetitem22 = new QTableWidgetItem();
        __qtablewidgetitem22->setFont(font);
        data_table->setHorizontalHeaderItem(4, __qtablewidgetitem22);
        QTableWidgetItem *__qtablewidgetitem23 = new QTableWidgetItem();
        __qtablewidgetitem23->setFont(font);
        data_table->setHorizontalHeaderItem(5, __qtablewidgetitem23);
        QTableWidgetItem *__qtablewidgetitem24 = new QTableWidgetItem();
        __qtablewidgetitem24->setFont(font);
        data_table->setHorizontalHeaderItem(6, __qtablewidgetitem24);
        QTableWidgetItem *__qtablewidgetitem25 = new QTableWidgetItem();
        __qtablewidgetitem25->setFont(font);
        data_table->setHorizontalHeaderItem(7, __qtablewidgetitem25);
        QTableWidgetItem *__qtablewidgetitem26 = new QTableWidgetItem();
        __qtablewidgetitem26->setFont(font);
        data_table->setHorizontalHeaderItem(8, __qtablewidgetitem26);
        QTableWidgetItem *__qtablewidgetitem27 = new QTableWidgetItem();
        __qtablewidgetitem27->setFont(font);
        data_table->setHorizontalHeaderItem(9, __qtablewidgetitem27);
        if (data_table->rowCount() < 2)
            data_table->setRowCount(2);
        QTableWidgetItem *__qtablewidgetitem28 = new QTableWidgetItem();
        __qtablewidgetitem28->setFont(font1);
        data_table->setVerticalHeaderItem(0, __qtablewidgetitem28);
        QTableWidgetItem *__qtablewidgetitem29 = new QTableWidgetItem();
        __qtablewidgetitem29->setFont(font1);
        data_table->setVerticalHeaderItem(1, __qtablewidgetitem29);
        data_table->setObjectName(QString::fromUtf8("data_table"));
        sizePolicy.setHeightForWidth(data_table->sizePolicy().hasHeightForWidth());
        data_table->setSizePolicy(sizePolicy);
        data_table->setMaximumSize(QSize(16777215, 16777215));
        data_table->setLayoutDirection(Qt::LeftToRight);
        data_table->setLineWidth(5);
        splitter_2->addWidget(data_table);
        label_4 = new QLabel(test);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setGeometry(QRect(150, 600, 161, 51));
        QFont font2;
        font2.setFamily(QString::fromUtf8("\346\245\267\344\275\223"));
        font2.setPointSize(20);
        label_4->setFont(font2);
        tabWidget->addTab(tab_5, QString());
        splitter->addWidget(tabWidget);

        horizontalLayout_2->addWidget(splitter);

        chart->setCentralWidget(centralwidget);

        retranslateUi(chart);

        tabWidget->setCurrentIndex(2);
        search_Button->setDefault(false);


        QMetaObject::connectSlotsByName(chart);
    } // setupUi

    void retranslateUi(QMainWindow *chart)
    {
        chart->setWindowTitle(QCoreApplication::translate("chart", "chart", nullptr));
        check->setText(QCoreApplication::translate("chart", "\346\240\241\351\252\214", nullptr));
        QTableWidgetItem *___qtablewidgetitem = information_table->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("chart", "\345\247\223\345\220\215", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = information_table->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("chart", "\346\200\247\345\210\253", nullptr));
        QTableWidgetItem *___qtablewidgetitem2 = information_table->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QCoreApplication::translate("chart", "\345\207\272\347\224\237\346\227\245\346\234\237", nullptr));
        QTableWidgetItem *___qtablewidgetitem3 = information_table->horizontalHeaderItem(3);
        ___qtablewidgetitem3->setText(QCoreApplication::translate("chart", "\345\244\207\346\263\250", nullptr));
        QTableWidgetItem *___qtablewidgetitem4 = information_table->verticalHeaderItem(0);
        ___qtablewidgetitem4->setText(QCoreApplication::translate("chart", "1", nullptr));

        const bool __sortingEnabled = information_table->isSortingEnabled();
        information_table->setSortingEnabled(false);
        information_table->setSortingEnabled(__sortingEnabled);

        search_Edit->setText(QCoreApplication::translate("chart", "\350\276\223\345\205\245\350\246\201\346\237\245\346\211\276\347\232\204\345\247\223\345\220\215", nullptr));
        search_Button->setText(QCoreApplication::translate("chart", "\346\237\245\346\211\276", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_3), QCoreApplication::translate("chart", "\346\237\245\346\211\276", nullptr));
        sex_Edit->setItemText(0, QCoreApplication::translate("chart", "\347\224\267", nullptr));
        sex_Edit->setItemText(1, QCoreApplication::translate("chart", "\345\245\263", nullptr));

        name_label->setText(QCoreApplication::translate("chart", "\345\247\223\345\220\215\357\274\232", nullptr));
        birth_label->setText(QCoreApplication::translate("chart", "\345\207\272\347\224\237\346\227\245\346\234\237\357\274\232", nullptr));
        sex_label->setText(QCoreApplication::translate("chart", "\346\200\247\345\210\253\357\274\232", nullptr));
        note_label->setText(QCoreApplication::translate("chart", "\345\244\207\346\263\250\357\274\232", nullptr));
        note_Edit->setHtml(QCoreApplication::translate("chart", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'SimSun'; font-size:11.25pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:9pt;\">\350\257\267\345\241\253\345\206\231\350\277\207\346\225\217\345\217\262\343\200\201\347\227\205\345\217\262\347\255\211\345\220\204\347\247\215\345\275\261\345\223\215\350\257\212\346\226\255\347\273\223\346\236\234\347\232\204\345\233\240\347\264\240...</span></p>\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-size:9pt;\"><br /></p></body></html>", nullptr));
        save->setText(QCoreApplication::translate("chart", "\344\277\235\345\255\230", nullptr));
        clear->setText(QCoreApplication::translate("chart", "\346\270\205\347\251\272", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_4), QCoreApplication::translate("chart", "\346\267\273\345\212\240\344\277\241\346\201\257", nullptr));
        led->setText(QCoreApplication::translate("chart", "led", nullptr));
        Hz->setItemText(0, QCoreApplication::translate("chart", "20Hz", nullptr));
        Hz->setItemText(1, QCoreApplication::translate("chart", "100Hz", nullptr));
        Hz->setItemText(2, QCoreApplication::translate("chart", "500Hz", nullptr));
        Hz->setItemText(3, QCoreApplication::translate("chart", "1KHz", nullptr));
        Hz->setItemText(4, QCoreApplication::translate("chart", "2KHz", nullptr));
        Hz->setItemText(5, QCoreApplication::translate("chart", "4KHz", nullptr));
        Hz->setItemText(6, QCoreApplication::translate("chart", "8KHz", nullptr));
        Hz->setItemText(7, QCoreApplication::translate("chart", "16KHz", nullptr));
        Hz->setItemText(8, QCoreApplication::translate("chart", "20KHz", nullptr));

        label->setText(QCoreApplication::translate("chart", "\351\242\221\347\216\207\357\274\232", nullptr));
        test_botton->setText(QCoreApplication::translate("chart", "\346\265\213\350\257\225", nullptr));
        call_botton->setText(QCoreApplication::translate("chart", "\351\200\232\350\257\235", nullptr));
        ear_choose->setItemText(0, QCoreApplication::translate("chart", "\345\267\246\350\200\263", nullptr));
        ear_choose->setItemText(1, QCoreApplication::translate("chart", "\345\217\263\350\200\263", nullptr));

        label_2->setText(QCoreApplication::translate("chart", "\346\265\213\350\257\225\351\237\263\345\274\272\345\272\246\357\274\232", nullptr));
        ear_label->setText(QCoreApplication::translate("chart", "\345\215\225\345\243\260\351\201\223\346\265\213\350\257\225\357\274\232", nullptr));
        clear_botton->setText(QCoreApplication::translate("chart", "\346\270\205\351\231\244\345\235\220\346\240\207", nullptr));
        data_test_save->setText(QCoreApplication::translate("chart", "\346\225\260\346\215\256\344\277\235\345\255\230", nullptr));
        label_3->setText(QCoreApplication::translate("chart", "DB HL", nullptr));
        label_5->setText(QCoreApplication::translate("chart", " \346\227\266\351\227\264\357\274\232", nullptr));
        timeEdit->setText(QCoreApplication::translate("chart", "1", nullptr));
        label_6->setText(QCoreApplication::translate("chart", "s", nullptr));
        test_over->setText(QCoreApplication::translate("chart", "\346\265\213\350\257\225\347\273\223\346\235\237", nullptr));
        QTableWidgetItem *___qtablewidgetitem5 = information_table_test->horizontalHeaderItem(0);
        ___qtablewidgetitem5->setText(QCoreApplication::translate("chart", "\345\247\223\345\220\215", nullptr));
        QTableWidgetItem *___qtablewidgetitem6 = information_table_test->horizontalHeaderItem(1);
        ___qtablewidgetitem6->setText(QCoreApplication::translate("chart", "\346\200\247\345\210\253", nullptr));
        QTableWidgetItem *___qtablewidgetitem7 = information_table_test->horizontalHeaderItem(2);
        ___qtablewidgetitem7->setText(QCoreApplication::translate("chart", "\345\207\272\347\224\237\346\227\245\346\234\237", nullptr));
        QTableWidgetItem *___qtablewidgetitem8 = information_table_test->horizontalHeaderItem(3);
        ___qtablewidgetitem8->setText(QCoreApplication::translate("chart", "\345\244\207\346\263\250", nullptr));
        QTableWidgetItem *___qtablewidgetitem9 = information_table_test->verticalHeaderItem(0);
        ___qtablewidgetitem9->setText(QCoreApplication::translate("chart", "1", nullptr));

        const bool __sortingEnabled1 = information_table_test->isSortingEnabled();
        information_table_test->setSortingEnabled(false);
        information_table_test->setSortingEnabled(__sortingEnabled1);

        QTableWidgetItem *___qtablewidgetitem10 = data_table->horizontalHeaderItem(0);
        ___qtablewidgetitem10->setText(QCoreApplication::translate("chart", "20Hz", nullptr));
        QTableWidgetItem *___qtablewidgetitem11 = data_table->horizontalHeaderItem(1);
        ___qtablewidgetitem11->setText(QCoreApplication::translate("chart", "250Hz", nullptr));
        QTableWidgetItem *___qtablewidgetitem12 = data_table->horizontalHeaderItem(2);
        ___qtablewidgetitem12->setText(QCoreApplication::translate("chart", "100Hz", nullptr));
        QTableWidgetItem *___qtablewidgetitem13 = data_table->horizontalHeaderItem(3);
        ___qtablewidgetitem13->setText(QCoreApplication::translate("chart", "500Hz", nullptr));
        QTableWidgetItem *___qtablewidgetitem14 = data_table->horizontalHeaderItem(4);
        ___qtablewidgetitem14->setText(QCoreApplication::translate("chart", "1KHz", nullptr));
        QTableWidgetItem *___qtablewidgetitem15 = data_table->horizontalHeaderItem(5);
        ___qtablewidgetitem15->setText(QCoreApplication::translate("chart", "2KHz", nullptr));
        QTableWidgetItem *___qtablewidgetitem16 = data_table->horizontalHeaderItem(6);
        ___qtablewidgetitem16->setText(QCoreApplication::translate("chart", "4KHz", nullptr));
        QTableWidgetItem *___qtablewidgetitem17 = data_table->horizontalHeaderItem(7);
        ___qtablewidgetitem17->setText(QCoreApplication::translate("chart", "8Khz", nullptr));
        QTableWidgetItem *___qtablewidgetitem18 = data_table->horizontalHeaderItem(8);
        ___qtablewidgetitem18->setText(QCoreApplication::translate("chart", "16KHz", nullptr));
        QTableWidgetItem *___qtablewidgetitem19 = data_table->horizontalHeaderItem(9);
        ___qtablewidgetitem19->setText(QCoreApplication::translate("chart", "20KHz", nullptr));
        QTableWidgetItem *___qtablewidgetitem20 = data_table->verticalHeaderItem(0);
        ___qtablewidgetitem20->setText(QCoreApplication::translate("chart", "\345\267\246\350\200\263", nullptr));
        QTableWidgetItem *___qtablewidgetitem21 = data_table->verticalHeaderItem(1);
        ___qtablewidgetitem21->setText(QCoreApplication::translate("chart", "\345\217\263\350\200\263", nullptr));
        label_4->setText(QCoreApplication::translate("chart", "\345\207\206\345\244\207\346\265\213\350\257\225", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_5), QCoreApplication::translate("chart", "\346\265\213\350\257\225", nullptr));
    } // retranslateUi

};

namespace Ui {
    class chart: public Ui_chart {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CHART_H
