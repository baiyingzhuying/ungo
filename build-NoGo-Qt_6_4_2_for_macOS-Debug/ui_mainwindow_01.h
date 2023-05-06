/********************************************************************************
** Form generated from reading UI file 'mainwindow_01.ui'
**
** Created by: Qt User Interface Compiler version 6.4.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_01_H
#define UI_MAINWINDOW_01_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow_01
{
public:
    QWidget *centralwidget;
    QFrame *BackGround;
    QPushButton *StartGame;
    QPushButton *help;
    QPushButton *ourteam;
    QPushButton *login;
    QWidget *widget_3;
    QVBoxLayout *verticalLayout;
    QWidget *widget;
    QHBoxLayout *horizontalLayout;
    QToolButton *toolButton;
    QLabel *user_white;
    QWidget *widget_2;
    QHBoxLayout *horizontalLayout_2;
    QToolButton *toolButton_2;
    QLabel *user_black;
    QComboBox *Broad;
    QPushButton *net_setting;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow_01)
    {
        if (MainWindow_01->objectName().isEmpty())
            MainWindow_01->setObjectName("MainWindow_01");
        MainWindow_01->resize(972, 711);
        centralwidget = new QWidget(MainWindow_01);
        centralwidget->setObjectName("centralwidget");
        BackGround = new QFrame(centralwidget);
        BackGround->setObjectName("BackGround");
        BackGround->setGeometry(QRect(0, 0, 961, 771));
        BackGround->setStyleSheet(QString::fromUtf8("#BackGround{\n"
"	border-image: url(:/new/prefix1/newback01.jpg);\n"
"\n"
"}"));
        BackGround->setFrameShape(QFrame::StyledPanel);
        BackGround->setFrameShadow(QFrame::Raised);
        StartGame = new QPushButton(BackGround);
        StartGame->setObjectName("StartGame");
        StartGame->setGeometry(QRect(670, 490, 161, 41));
        StartGame->setStyleSheet(QString::fromUtf8("color: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, stop:0 rgba(0, 0, 0, 255), stop:1 rgba(255, 255, 255, 255));"));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/picture/visitor.png"), QSize(), QIcon::Normal, QIcon::Off);
        StartGame->setIcon(icon);
        StartGame->setIconSize(QSize(300, 100));
        help = new QPushButton(BackGround);
        help->setObjectName("help");
        help->setGeometry(QRect(690, 300, 111, 41));
        help->setStyleSheet(QString::fromUtf8("border-image: url(:/new/prefix1/image/bottons.qrc);"));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/picture/help.png"), QSize(), QIcon::Normal, QIcon::Off);
        help->setIcon(icon1);
        help->setIconSize(QSize(300, 40));
        ourteam = new QPushButton(BackGround);
        ourteam->setObjectName("ourteam");
        ourteam->setGeometry(QRect(670, 580, 161, 41));
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/picture/ourteam.png"), QSize(), QIcon::Normal, QIcon::Off);
        ourteam->setIcon(icon2);
        ourteam->setIconSize(QSize(150, 40));
        login = new QPushButton(BackGround);
        login->setObjectName("login");
        login->setGeometry(QRect(670, 390, 161, 41));
        QIcon icon3;
        icon3.addFile(QString::fromUtf8(":/picture/login.png"), QSize(), QIcon::Normal, QIcon::Off);
        login->setIcon(icon3);
        login->setIconSize(QSize(150, 40));
        login->setAutoDefault(false);
        widget_3 = new QWidget(BackGround);
        widget_3->setObjectName("widget_3");
        widget_3->setGeometry(QRect(20, 20, 230, 108));
        verticalLayout = new QVBoxLayout(widget_3);
        verticalLayout->setObjectName("verticalLayout");
        widget = new QWidget(widget_3);
        widget->setObjectName("widget");
        horizontalLayout = new QHBoxLayout(widget);
        horizontalLayout->setObjectName("horizontalLayout");
        toolButton = new QToolButton(widget);
        toolButton->setObjectName("toolButton");

        horizontalLayout->addWidget(toolButton);

        user_white = new QLabel(widget);
        user_white->setObjectName("user_white");

        horizontalLayout->addWidget(user_white);


        verticalLayout->addWidget(widget);

        widget_2 = new QWidget(widget_3);
        widget_2->setObjectName("widget_2");
        horizontalLayout_2 = new QHBoxLayout(widget_2);
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        toolButton_2 = new QToolButton(widget_2);
        toolButton_2->setObjectName("toolButton_2");

        horizontalLayout_2->addWidget(toolButton_2);

        user_black = new QLabel(widget_2);
        user_black->setObjectName("user_black");

        horizontalLayout_2->addWidget(user_black);


        verticalLayout->addWidget(widget_2);

        Broad = new QComboBox(BackGround);
        Broad->addItem(QString());
        Broad->addItem(QString());
        Broad->addItem(QString());
        Broad->setObjectName("Broad");
        Broad->setGeometry(QRect(830, 70, 101, 41));
        Broad->setStyleSheet(QString::fromUtf8(""));
        Broad->setFrame(true);
        net_setting = new QPushButton(BackGround);
        net_setting->setObjectName("net_setting");
        net_setting->setGeometry(QRect(700, 450, 93, 29));
        help->raise();
        StartGame->raise();
        ourteam->raise();
        login->raise();
        widget_3->raise();
        Broad->raise();
        net_setting->raise();
        MainWindow_01->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow_01);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 972, 26));
        MainWindow_01->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow_01);
        statusbar->setObjectName("statusbar");
        MainWindow_01->setStatusBar(statusbar);

        retranslateUi(MainWindow_01);

        Broad->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(MainWindow_01);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow_01)
    {
        MainWindow_01->setWindowTitle(QCoreApplication::translate("MainWindow_01", "MainWindow", nullptr));
        StartGame->setText(QString());
        help->setText(QString());
        ourteam->setText(QString());
        login->setText(QString());
        toolButton->setText(QCoreApplication::translate("MainWindow_01", "\347\231\275\346\226\271\357\274\232", nullptr));
        user_white->setText(QString());
        toolButton_2->setText(QCoreApplication::translate("MainWindow_01", "\351\273\221\346\226\271\357\274\232", nullptr));
        user_black->setText(QString());
        Broad->setItemText(0, QCoreApplication::translate("MainWindow_01", "9x9", nullptr));
        Broad->setItemText(1, QCoreApplication::translate("MainWindow_01", "11x11", nullptr));
        Broad->setItemText(2, QCoreApplication::translate("MainWindow_01", "13x13", nullptr));

        net_setting->setText(QCoreApplication::translate("MainWindow_01", "setting", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow_01: public Ui_MainWindow_01 {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_01_H
