/********************************************************************************
** Form generated from reading UI file 'test.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TEST_H
#define UI_TEST_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include <QtCharts/QChartView>

QT_BEGIN_NAMESPACE

class Ui_test
{
public:
    QWidget *centralwidget;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QtCharts::QChartView *chart_view;
    QtCharts::QChartView *chart_ret_view;
    QHBoxLayout *horizontalLayout_2;
    QSpacerItem *horizontalSpacer;
    QCheckBox *Audio_Standard;
    QPushButton *clear;
    QPushButton *data_button;
    QSpacerItem *horizontalSpacer_2;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *test)
    {
        if (test->objectName().isEmpty())
            test->setObjectName(QString::fromUtf8("test"));
        test->resize(800, 600);
        centralwidget = new QWidget(test);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        verticalLayout = new QVBoxLayout(centralwidget);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        chart_view = new QtCharts::QChartView(centralwidget);
        chart_view->setObjectName(QString::fromUtf8("chart_view"));

        horizontalLayout->addWidget(chart_view);

        chart_ret_view = new QtCharts::QChartView(centralwidget);
        chart_ret_view->setObjectName(QString::fromUtf8("chart_ret_view"));

        horizontalLayout->addWidget(chart_ret_view);


        verticalLayout->addLayout(horizontalLayout);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer);

        Audio_Standard = new QCheckBox(centralwidget);
        Audio_Standard->setObjectName(QString::fromUtf8("Audio_Standard"));

        horizontalLayout_2->addWidget(Audio_Standard);

        clear = new QPushButton(centralwidget);
        clear->setObjectName(QString::fromUtf8("clear"));

        horizontalLayout_2->addWidget(clear);

        data_button = new QPushButton(centralwidget);
        data_button->setObjectName(QString::fromUtf8("data_button"));
        QSizePolicy sizePolicy(QSizePolicy::Minimum, QSizePolicy::Maximum);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(data_button->sizePolicy().hasHeightForWidth());
        data_button->setSizePolicy(sizePolicy);

        horizontalLayout_2->addWidget(data_button);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_2);


        verticalLayout->addLayout(horizontalLayout_2);

        test->setCentralWidget(centralwidget);
        statusbar = new QStatusBar(test);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        test->setStatusBar(statusbar);

        retranslateUi(test);

        QMetaObject::connectSlotsByName(test);
    } // setupUi

    void retranslateUi(QMainWindow *test)
    {
        test->setWindowTitle(QCoreApplication::translate("test", "MainWindow", nullptr));
        Audio_Standard->setText(QCoreApplication::translate("test", "CheckBox", nullptr));
        clear->setText(QCoreApplication::translate("test", "\346\270\205\351\231\244\345\235\220\346\240\207", nullptr));
        data_button->setText(QCoreApplication::translate("test", "\344\274\240\351\200\222\346\225\260\346\215\256", nullptr));
    } // retranslateUi

};

namespace Ui {
    class test: public Ui_test {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TEST_H
