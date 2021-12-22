/********************************************************************************
** Form generated from reading UI file 'search_null.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SEARCH_NULL_H
#define UI_SEARCH_NULL_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_search_null
{
public:
    QPushButton *pushButton;
    QLabel *label;

    void setupUi(QDialog *search_null)
    {
        if (search_null->objectName().isEmpty())
            search_null->setObjectName(QString::fromUtf8("search_null"));
        search_null->resize(400, 300);
        pushButton = new QPushButton(search_null);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        pushButton->setGeometry(QRect(160, 190, 61, 21));
        QFont font;
        font.setFamily(QString::fromUtf8("\346\245\267\344\275\223"));
        font.setPointSize(12);
        pushButton->setFont(font);
        label = new QLabel(search_null);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(100, 90, 181, 61));
        label->setFont(font);
        label->setAlignment(Qt::AlignCenter);

        retranslateUi(search_null);

        QMetaObject::connectSlotsByName(search_null);
    } // setupUi

    void retranslateUi(QDialog *search_null)
    {
        search_null->setWindowTitle(QCoreApplication::translate("search_null", "Dialog", nullptr));
        pushButton->setText(QCoreApplication::translate("search_null", "\347\241\256\345\256\232", nullptr));
        label->setText(QCoreApplication::translate("search_null", "\346\234\252\346\237\245\345\210\260\344\270\216\347\224\250\346\210\267\347\233\270\345\205\263\344\277\241\346\201\257", nullptr));
    } // retranslateUi

};

namespace Ui {
    class search_null: public Ui_search_null {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SEARCH_NULL_H
