/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.9.9
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QPushButton *pushButton;
    QRadioButton *radioButton_2;
    QRadioButton *radioButton;
    QRadioButton *radioButton_3;
    QLabel *label;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(753, 600);
        MainWindow->setStyleSheet(QStringLiteral("background-color: rgb(196, 204, 255);"));
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QStringLiteral("centralwidget"));
        pushButton = new QPushButton(centralwidget);
        pushButton->setObjectName(QStringLiteral("pushButton"));
        pushButton->setGeometry(QRect(270, 450, 181, 91));
        pushButton->setStyleSheet(QString::fromUtf8("font: 16pt \"\345\215\216\346\226\207\350\241\214\346\245\267\";\n"
""));
        pushButton->setFlat(false);
        radioButton_2 = new QRadioButton(centralwidget);
        radioButton_2->setObjectName(QStringLiteral("radioButton_2"));
        radioButton_2->setGeometry(QRect(250, 250, 400, 100));
        radioButton_2->setStyleSheet(QString::fromUtf8("font: 11pt \"\346\245\267\344\275\223\";\n"
"color: rgb(255, 255, 255);"));
        radioButton = new QRadioButton(centralwidget);
        radioButton->setObjectName(QStringLiteral("radioButton"));
        radioButton->setGeometry(QRect(250, 180, 400, 100));
        radioButton->setStyleSheet(QString::fromUtf8("font: 11pt \"\346\245\267\344\275\223\";"));
        radioButton_3 = new QRadioButton(centralwidget);
        radioButton_3->setObjectName(QStringLiteral("radioButton_3"));
        radioButton_3->setGeometry(QRect(250, 320, 400, 100));
        radioButton_3->setStyleSheet(QString::fromUtf8("font: 11pt \"\346\245\267\344\275\223\";\n"
"color: rgb(138, 138, 138);"));
        label = new QLabel(centralwidget);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(250, 80, 231, 71));
        label->setStyleSheet(QString::fromUtf8("font: 36pt \"\345\215\216\346\226\207\350\241\214\346\245\267\";"));
        label->setAlignment(Qt::AlignCenter);
        MainWindow->setCentralWidget(centralwidget);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QStringLiteral("statusbar"));
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "Welcome to nogo", Q_NULLPTR));
        pushButton->setText(QApplication::translate("MainWindow", "\345\274\200\345\247\213\346\270\270\346\210\217", Q_NULLPTR));
        radioButton_2->setText(QApplication::translate("MainWindow", "\346\210\221\351\200\211\346\213\251\347\231\275\346\226\271\357\274\210\345\220\216\346\211\213\357\274\211", Q_NULLPTR));
        radioButton->setText(QApplication::translate("MainWindow", "\346\210\221\351\200\211\346\213\251\351\273\221\346\226\271\357\274\210\345\205\210\346\211\213\357\274\211", Q_NULLPTR));
        radioButton_3->setText(QApplication::translate("MainWindow", "\347\273\247\347\273\255\344\270\212\344\270\200\345\261\200\346\270\270\346\210\217", Q_NULLPTR));
        label->setText(QApplication::translate("MainWindow", "\344\270\215\345\233\264\346\243\213", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
