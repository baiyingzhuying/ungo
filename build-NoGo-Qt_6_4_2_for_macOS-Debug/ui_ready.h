/********************************************************************************
** Form generated from reading UI file 'ready.ui'
**
** Created by: Qt User Interface Compiler version 6.4.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_READY_H
#define UI_READY_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ready
{
public:
    QPushButton *agree;
    QPushButton *disagree;
    QLineEdit *lineEdit;

    void setupUi(QWidget *ready)
    {
        if (ready->objectName().isEmpty())
            ready->setObjectName("ready");
        ready->resize(400, 300);
        agree = new QPushButton(ready);
        agree->setObjectName("agree");
        agree->setGeometry(QRect(60, 160, 93, 29));
        disagree = new QPushButton(ready);
        disagree->setObjectName("disagree");
        disagree->setGeometry(QRect(230, 160, 93, 29));
        lineEdit = new QLineEdit(ready);
        lineEdit->setObjectName("lineEdit");
        lineEdit->setGeometry(QRect(72, 60, 241, 41));

        retranslateUi(ready);

        QMetaObject::connectSlotsByName(ready);
    } // setupUi

    void retranslateUi(QWidget *ready)
    {
        ready->setWindowTitle(QCoreApplication::translate("ready", "Form", nullptr));
        agree->setText(QCoreApplication::translate("ready", "\345\220\214\346\204\217", nullptr));
        disagree->setText(QCoreApplication::translate("ready", "\344\270\215\345\220\214\346\204\217", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ready: public Ui_ready {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_READY_H
