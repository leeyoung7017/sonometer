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
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_test
{
public:
    QPushButton *ButtonDisplayData;
    QPushButton *ButtonDisplayFFT;
    QCustomPlot *widgetFFT;
    QGroupBox *groupBox;
    QWidget *formLayoutWidget;
    QFormLayout *formLayout;
    QLabel *label_6;
    QLabel *label_spl;
    QLabel *label_2;
    QLabel *label_3;
    QLabel *label_5;
    QLabel *label;
    QLineEdit *FreqEdit;
    QLineEdit *THDEdit;
    QLineEdit *SNREdit;
    QLineEdit *SPLEdit0;
    QLineEdit *SPLEdit;
    QLineEdit *lineEdit_6;
    QSpacerItem *verticalSpacer;
    QSpacerItem *verticalSpacer_2;
    QSpacerItem *verticalSpacer_3;
    QSpacerItem *verticalSpacer_4;
    QSpacerItem *verticalSpacer_5;
    QSpacerItem *verticalSpacer_6;
    QSpacerItem *verticalSpacer_7;
    QSpacerItem *verticalSpacer_8;
    QSpacerItem *verticalSpacer_9;
    QSpacerItem *verticalSpacer_10;

    void setupUi(QWidget *test)
    {
        if (test->objectName().isEmpty())
            test->setObjectName(QString::fromUtf8("test"));
        test->resize(825, 502);
        ButtonDisplayData = new QPushButton(test);
        ButtonDisplayData->setObjectName(QString::fromUtf8("ButtonDisplayData"));
        ButtonDisplayData->setGeometry(QRect(400, 410, 75, 23));
        ButtonDisplayFFT = new QPushButton(test);
        ButtonDisplayFFT->setObjectName(QString::fromUtf8("ButtonDisplayFFT"));
        ButtonDisplayFFT->setGeometry(QRect(520, 410, 75, 23));
        widgetFFT = new QCustomPlot(test);
        widgetFFT->setObjectName(QString::fromUtf8("widgetFFT"));
        widgetFFT->setGeometry(QRect(200, 10, 621, 381));
        groupBox = new QGroupBox(test);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        groupBox->setGeometry(QRect(10, 20, 181, 251));
        QFont font;
        font.setFamily(QString::fromUtf8("\346\245\267\344\275\223"));
        groupBox->setFont(font);
        formLayoutWidget = new QWidget(groupBox);
        formLayoutWidget->setObjectName(QString::fromUtf8("formLayoutWidget"));
        formLayoutWidget->setGeometry(QRect(10, 20, 161, 211));
        formLayout = new QFormLayout(formLayoutWidget);
        formLayout->setObjectName(QString::fromUtf8("formLayout"));
        formLayout->setContentsMargins(0, 0, 0, 0);
        label_6 = new QLabel(formLayoutWidget);
        label_6->setObjectName(QString::fromUtf8("label_6"));
        QFont font1;
        font1.setFamily(QString::fromUtf8("\346\245\267\344\275\223"));
        font1.setPointSize(9);
        label_6->setFont(font1);

        formLayout->setWidget(10, QFormLayout::LabelRole, label_6);

        label_spl = new QLabel(formLayoutWidget);
        label_spl->setObjectName(QString::fromUtf8("label_spl"));
        label_spl->setFont(font1);

        formLayout->setWidget(8, QFormLayout::LabelRole, label_spl);

        label_2 = new QLabel(formLayoutWidget);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setFont(font1);

        formLayout->setWidget(6, QFormLayout::LabelRole, label_2);

        label_3 = new QLabel(formLayoutWidget);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setFont(font1);

        formLayout->setWidget(4, QFormLayout::LabelRole, label_3);

        label_5 = new QLabel(formLayoutWidget);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        label_5->setFont(font1);

        formLayout->setWidget(2, QFormLayout::LabelRole, label_5);

        label = new QLabel(formLayoutWidget);
        label->setObjectName(QString::fromUtf8("label"));
        label->setFont(font1);

        formLayout->setWidget(0, QFormLayout::LabelRole, label);

        FreqEdit = new QLineEdit(formLayoutWidget);
        FreqEdit->setObjectName(QString::fromUtf8("FreqEdit"));

        formLayout->setWidget(0, QFormLayout::FieldRole, FreqEdit);

        THDEdit = new QLineEdit(formLayoutWidget);
        THDEdit->setObjectName(QString::fromUtf8("THDEdit"));

        formLayout->setWidget(2, QFormLayout::FieldRole, THDEdit);

        SNREdit = new QLineEdit(formLayoutWidget);
        SNREdit->setObjectName(QString::fromUtf8("SNREdit"));

        formLayout->setWidget(4, QFormLayout::FieldRole, SNREdit);

        SPLEdit0 = new QLineEdit(formLayoutWidget);
        SPLEdit0->setObjectName(QString::fromUtf8("SPLEdit0"));

        formLayout->setWidget(6, QFormLayout::FieldRole, SPLEdit0);

        SPLEdit = new QLineEdit(formLayoutWidget);
        SPLEdit->setObjectName(QString::fromUtf8("SPLEdit"));

        formLayout->setWidget(8, QFormLayout::FieldRole, SPLEdit);

        lineEdit_6 = new QLineEdit(formLayoutWidget);
        lineEdit_6->setObjectName(QString::fromUtf8("lineEdit_6"));

        formLayout->setWidget(10, QFormLayout::FieldRole, lineEdit_6);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        formLayout->setItem(1, QFormLayout::LabelRole, verticalSpacer);

        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        formLayout->setItem(1, QFormLayout::FieldRole, verticalSpacer_2);

        verticalSpacer_3 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        formLayout->setItem(3, QFormLayout::LabelRole, verticalSpacer_3);

        verticalSpacer_4 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        formLayout->setItem(3, QFormLayout::FieldRole, verticalSpacer_4);

        verticalSpacer_5 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        formLayout->setItem(5, QFormLayout::LabelRole, verticalSpacer_5);

        verticalSpacer_6 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        formLayout->setItem(5, QFormLayout::FieldRole, verticalSpacer_6);

        verticalSpacer_7 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        formLayout->setItem(7, QFormLayout::LabelRole, verticalSpacer_7);

        verticalSpacer_8 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        formLayout->setItem(7, QFormLayout::FieldRole, verticalSpacer_8);

        verticalSpacer_9 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        formLayout->setItem(9, QFormLayout::LabelRole, verticalSpacer_9);

        verticalSpacer_10 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        formLayout->setItem(9, QFormLayout::FieldRole, verticalSpacer_10);


        retranslateUi(test);

        QMetaObject::connectSlotsByName(test);
    } // setupUi

    void retranslateUi(QWidget *test)
    {
        test->setWindowTitle(QCoreApplication::translate("test", "Form", nullptr));
        ButtonDisplayData->setText(QCoreApplication::translate("test", "\346\230\276\347\244\272", nullptr));
        ButtonDisplayFFT->setText(QCoreApplication::translate("test", "FFT", nullptr));
        groupBox->setTitle(QCoreApplication::translate("test", "\345\220\254\345\212\233\350\256\241\351\237\263\351\242\221\344\277\241\345\217\267\345\210\206\346\236\220\347\263\273\347\273\237", nullptr));
        label_6->setText(QCoreApplication::translate("test", "\346\216\251\350\224\275\345\231\252\345\243\260\347\272\247", nullptr));
        label_spl->setText(QCoreApplication::translate("test", "\345\243\260\345\216\213\347\272\247\350\257\257\345\267\256(dB)", nullptr));
        label_2->setText(QCoreApplication::translate("test", "\350\241\260\345\207\217\346\241\243\350\257\257\345\267\256(dB)", nullptr));
        label_3->setText(QCoreApplication::translate("test", "\344\277\241\345\231\252\346\257\224(dB)", nullptr));
        label_5->setText(QCoreApplication::translate("test", "\350\260\220\346\263\242\345\244\261\347\234\237(%)", nullptr));
        label->setText(QCoreApplication::translate("test", "\351\242\221\347\216\207\350\257\257\345\267\256(%)", nullptr));
    } // retranslateUi

};

namespace Ui {
    class test: public Ui_test {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TEST_H
