/********************************************************************************
** Form generated from reading UI file 'yonghu.ui'
**
** Created by: Qt User Interface Compiler version 6.4.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_YONGHU_H
#define UI_YONGHU_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_YongHu
{
public:
    QGridLayout *gridLayout;
    QWidget *widget;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer;
    QLabel *label;
    QLineEdit *yonghuming;
    QSpacerItem *horizontalSpacer_2;
    QWidget *widget_2;
    QHBoxLayout *horizontalLayout_2;
    QSpacerItem *horizontalSpacer_3;
    QLabel *label_2;
    QLineEdit *mima;
    QSpacerItem *horizontalSpacer_4;
    QWidget *widget_3;
    QHBoxLayout *horizontalLayout_3;
    QSpacerItem *horizontalSpacer_5;
    QPushButton *login_black;
    QPushButton *login_white;
    QPushButton *zhucejian;
    QPushButton *tuichu;
    QSpacerItem *horizontalSpacer_6;

    void setupUi(QWidget *YongHu)
    {
        if (YongHu->objectName().isEmpty())
            YongHu->setObjectName("YongHu");
        YongHu->resize(400, 300);
        gridLayout = new QGridLayout(YongHu);
        gridLayout->setObjectName("gridLayout");
        widget = new QWidget(YongHu);
        widget->setObjectName("widget");
        horizontalLayout = new QHBoxLayout(widget);
        horizontalLayout->setObjectName("horizontalLayout");
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        label = new QLabel(widget);
        label->setObjectName("label");

        horizontalLayout->addWidget(label);

        yonghuming = new QLineEdit(widget);
        yonghuming->setObjectName("yonghuming");

        horizontalLayout->addWidget(yonghuming);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_2);


        gridLayout->addWidget(widget, 0, 0, 1, 1);

        widget_2 = new QWidget(YongHu);
        widget_2->setObjectName("widget_2");
        horizontalLayout_2 = new QHBoxLayout(widget_2);
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_3);

        label_2 = new QLabel(widget_2);
        label_2->setObjectName("label_2");

        horizontalLayout_2->addWidget(label_2);

        mima = new QLineEdit(widget_2);
        mima->setObjectName("mima");
        mima->setEchoMode(QLineEdit::Password);

        horizontalLayout_2->addWidget(mima);

        horizontalSpacer_4 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_4);


        gridLayout->addWidget(widget_2, 1, 0, 1, 1);

        widget_3 = new QWidget(YongHu);
        widget_3->setObjectName("widget_3");
        horizontalLayout_3 = new QHBoxLayout(widget_3);
        horizontalLayout_3->setObjectName("horizontalLayout_3");
        horizontalSpacer_5 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_5);

        login_black = new QPushButton(widget_3);
        login_black->setObjectName("login_black");

        horizontalLayout_3->addWidget(login_black);

        login_white = new QPushButton(widget_3);
        login_white->setObjectName("login_white");

        horizontalLayout_3->addWidget(login_white);

        zhucejian = new QPushButton(widget_3);
        zhucejian->setObjectName("zhucejian");

        horizontalLayout_3->addWidget(zhucejian);

        tuichu = new QPushButton(widget_3);
        tuichu->setObjectName("tuichu");

        horizontalLayout_3->addWidget(tuichu);

        horizontalSpacer_6 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_6);


        gridLayout->addWidget(widget_3, 2, 0, 1, 1);


        retranslateUi(YongHu);

        QMetaObject::connectSlotsByName(YongHu);
    } // setupUi

    void retranslateUi(QWidget *YongHu)
    {
        YongHu->setWindowTitle(QCoreApplication::translate("YongHu", "Form", nullptr));
        label->setText(QCoreApplication::translate("YongHu", "\347\224\250\346\210\267\345\220\215\357\274\232", nullptr));
        label_2->setText(QCoreApplication::translate("YongHu", "\345\257\206\347\240\201\357\274\232", nullptr));
        login_black->setText(QCoreApplication::translate("YongHu", "\351\273\221\346\226\271\347\231\273\345\275\225", nullptr));
        login_white->setText(QCoreApplication::translate("YongHu", "\347\231\275\346\226\271\347\231\273\345\275\225", nullptr));
        zhucejian->setText(QCoreApplication::translate("YongHu", "\346\263\250\345\206\214", nullptr));
        tuichu->setText(QCoreApplication::translate("YongHu", "\351\200\200\345\207\272", nullptr));
    } // retranslateUi

};

namespace Ui {
    class YongHu: public Ui_YongHu {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_YONGHU_H
