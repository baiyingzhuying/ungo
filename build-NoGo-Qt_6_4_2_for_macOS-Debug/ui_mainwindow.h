/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.4.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLCDNumber>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QPushButton *quitButton;
    QPushButton *restart;
    QWidget *widget;
    QLabel *label;
    QLCDNumber *lcdNumber;
    QWidget *time;
    QLabel *label_2;
    QWidget *restart_2;
    QPushButton *startButton;
    QWidget *widget_2;
    QWidget *widget_3;
    QLabel *label_3;
    QLabel *label_4;
    QLabel *label_5;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(1049, 699);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        quitButton = new QPushButton(centralwidget);
        quitButton->setObjectName("quitButton");
        quitButton->setGeometry(QRect(840, 100, 91, 41));
        restart = new QPushButton(centralwidget);
        restart->setObjectName("restart");
        restart->setGeometry(QRect(840, 240, 93, 51));
        widget = new QWidget(centralwidget);
        widget->setObjectName("widget");
        widget->setGeometry(QRect(820, 470, 361, 261));
        widget->setStyleSheet(QString::fromUtf8("images: url(:/new/prefix1/miku.png)\n"
""));
        label = new QLabel(widget);
        label->setObjectName("label");
        label->setGeometry(QRect(-10, -80, 461, 401));
        label->setPixmap(QPixmap(QString::fromUtf8(":/new/prefix1/miku.png")));
        lcdNumber = new QLCDNumber(centralwidget);
        lcdNumber->setObjectName("lcdNumber");
        lcdNumber->setGeometry(QRect(870, 330, 71, 31));
        lcdNumber->setProperty("value", QVariant(30.000000000000000));
        time = new QWidget(centralwidget);
        time->setObjectName("time");
        time->setGeometry(QRect(840, 330, 31, 41));
        time->setStyleSheet(QString::fromUtf8("image:url(:/new/prefix1/time.png)"));
        label_2 = new QLabel(time);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(0, 20, 58, 191));
        label_2->setPixmap(QPixmap(QString::fromUtf8(":/new/prefix1/time.png")));
        restart_2 = new QWidget(centralwidget);
        restart_2->setObjectName("restart_2");
        restart_2->setGeometry(QRect(830, 230, 120, 80));
        restart_2->setStyleSheet(QString::fromUtf8("images:url(:/new/prefix1/restart.png)"));
        startButton = new QPushButton(centralwidget);
        startButton->setObjectName("startButton");
        startButton->setGeometry(QRect(840, 160, 93, 51));
        widget_2 = new QWidget(centralwidget);
        widget_2->setObjectName("widget_2");
        widget_2->setGeometry(QRect(820, 150, 120, 80));
        widget_2->setStyleSheet(QString::fromUtf8("images:url(:/new/prefix1/start.png)"));
        widget_3 = new QWidget(centralwidget);
        widget_3->setObjectName("widget_3");
        widget_3->setGeometry(QRect(830, 80, 120, 80));
        widget_3->setStyleSheet(QString::fromUtf8("images:url(:/new/prefix1/give-up.png)"));
        label_3 = new QLabel(centralwidget);
        label_3->setObjectName("label_3");
        label_3->setGeometry(QRect(860, 110, 71, 21));
        label_3->setPixmap(QPixmap(QString::fromUtf8(":/new/prefix1/give-up.png")));
        label_4 = new QLabel(centralwidget);
        label_4->setObjectName("label_4");
        label_4->setGeometry(QRect(860, 170, 61, 21));
        label_4->setPixmap(QPixmap(QString::fromUtf8(":/new/prefix1/start.png")));
        label_5 = new QLabel(centralwidget);
        label_5->setObjectName("label_5");
        label_5->setGeometry(QRect(860, 250, 71, 31));
        label_5->setPixmap(QPixmap(QString::fromUtf8(":/new/prefix1/restart.png")));
        MainWindow->setCentralWidget(centralwidget);
        label_5->raise();
        label_4->raise();
        label_3->raise();
        restart_2->raise();
        widget_2->raise();
        widget_3->raise();
        quitButton->raise();
        restart->raise();
        widget->raise();
        lcdNumber->raise();
        time->raise();
        startButton->raise();
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 1049, 36));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        quitButton->setText(QString());
        restart->setText(QString());
        label->setText(QString());
        label_2->setText(QString());
        startButton->setText(QString());
        label_3->setText(QString());
        label_4->setText(QString());
        label_5->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
