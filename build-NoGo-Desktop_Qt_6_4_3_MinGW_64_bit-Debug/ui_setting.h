/********************************************************************************
** Form generated from reading UI file 'setting.ui'
**
** Created by: Qt User Interface Compiler version 6.4.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SETTING_H
#define UI_SETTING_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_setting
{
public:
    QLabel *label;
    QPushButton *sure;
    QLineEdit *numedit;

    void setupUi(QWidget *setting)
    {
        if (setting->objectName().isEmpty())
            setting->setObjectName("setting");
        setting->resize(470, 376);
        label = new QLabel(setting);
        label->setObjectName("label");
        label->setGeometry(QRect(90, 100, 91, 41));
        sure = new QPushButton(setting);
        sure->setObjectName("sure");
        sure->setGeometry(QRect(180, 150, 101, 29));
        numedit = new QLineEdit(setting);
        numedit->setObjectName("numedit");
        numedit->setGeometry(QRect(180, 110, 101, 31));

        retranslateUi(setting);

        QMetaObject::connectSlotsByName(setting);
    } // setupUi

    void retranslateUi(QWidget *setting)
    {
        setting->setWindowTitle(QCoreApplication::translate("setting", "Form", nullptr));
        label->setText(QCoreApplication::translate("setting", "\345\200\222\350\256\241\346\227\266\350\256\276\347\275\256\357\274\232", nullptr));
        sure->setText(QCoreApplication::translate("setting", "\347\241\256\350\256\244", nullptr));
        numedit->setText(QCoreApplication::translate("setting", "30", nullptr));
    } // retranslateUi

};

namespace Ui {
    class setting: public Ui_setting {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SETTING_H
