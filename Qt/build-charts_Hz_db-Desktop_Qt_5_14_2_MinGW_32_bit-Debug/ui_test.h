/********************************************************************************
** Form generated from reading UI file 'test.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TEST_H
#define UI_TEST_H

#include <qcustomplot/qcustomplot.h>
#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_test
{
public:
    QCustomPlot *widgetData;
    QCustomPlot *widgetFFT;
    QPushButton *ButtonDisplayData;
    QPushButton *ButtonDisplayFFT;

    void setupUi(QWidget *test)
    {
        if (test->objectName().isEmpty())
            test->setObjectName(QString::fromUtf8("test"));
        test->resize(825, 502);
        widgetData = new QCustomPlot(test);
        widgetData->setObjectName(QString::fromUtf8("widgetData"));
        widgetData->setGeometry(QRect(10, 10, 801, 431));
        widgetFFT = new QCustomPlot(widgetData);
        widgetFFT->setObjectName(QString::fromUtf8("widgetFFT"));
        widgetFFT->setGeometry(QRect(0, 0, 801, 431));
        ButtonDisplayData = new QPushButton(test);
        ButtonDisplayData->setObjectName(QString::fromUtf8("ButtonDisplayData"));
        ButtonDisplayData->setGeometry(QRect(290, 460, 75, 23));
        ButtonDisplayFFT = new QPushButton(test);
        ButtonDisplayFFT->setObjectName(QString::fromUtf8("ButtonDisplayFFT"));
        ButtonDisplayFFT->setGeometry(QRect(410, 460, 75, 23));

        retranslateUi(test);

        QMetaObject::connectSlotsByName(test);
    } // setupUi

    void retranslateUi(QWidget *test)
    {
        test->setWindowTitle(QCoreApplication::translate("test", "Form", nullptr));
        ButtonDisplayData->setText(QCoreApplication::translate("test", "\346\230\276\347\244\272", nullptr));
        ButtonDisplayFFT->setText(QCoreApplication::translate("test", "FFT", nullptr));
    } // retranslateUi

};

namespace Ui {
    class test: public Ui_test {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TEST_H
