/********************************************************************************
** Form generated from reading UI file 'data_save.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DATA_SAVE_H
#define UI_DATA_SAVE_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_data_save
{
public:
    QPushButton *pushButton;
    QLabel *label;

    void setupUi(QDialog *data_save)
    {
        if (data_save->objectName().isEmpty())
            data_save->setObjectName(QString::fromUtf8("data_save"));
        data_save->resize(400, 300);
        pushButton = new QPushButton(data_save);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        pushButton->setGeometry(QRect(160, 180, 71, 31));
        QFont font;
        font.setFamily(QString::fromUtf8("\346\245\267\344\275\223"));
        font.setPointSize(12);
        pushButton->setFont(font);
        label = new QLabel(data_save);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(110, 100, 171, 41));
        QFont font1;
        font1.setFamily(QString::fromUtf8("\346\245\267\344\275\223"));
        font1.setPointSize(14);
        label->setFont(font1);
        label->setAlignment(Qt::AlignCenter);

        retranslateUi(data_save);

        QMetaObject::connectSlotsByName(data_save);
    } // setupUi

    void retranslateUi(QDialog *data_save)
    {
        data_save->setWindowTitle(QCoreApplication::translate("data_save", "Dialog", nullptr));
        pushButton->setText(QCoreApplication::translate("data_save", "\347\241\256\345\256\232", nullptr));
        label->setText(QCoreApplication::translate("data_save", "\345\267\262\344\277\235\345\255\230", nullptr));
    } // retranslateUi

};

namespace Ui {
    class data_save: public Ui_data_save {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DATA_SAVE_H
