/********************************************************************************
** Form generated from reading UI file 'netting.ui'
**
** Created by: Qt User Interface Compiler version 6.4.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_NETTING_H
#define UI_NETTING_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_netting
{
public:
    QWidget *layoutWidget;
    QGridLayout *gridLayout;
    QLineEdit *nameshow;
    QLineEdit *PORTEdit;
    QLineEdit *IPEdit;
    QLineEdit *clientGetEdit;
    QLineEdit *nameEdit;
    QPushButton *reSetButton;
    QPushButton *StartAsWhite;
    QPushButton *showClientButton;
    QLineEdit *clientSendEdit;
    QPushButton *clientSendButton;
    QPushButton *name_setting;
    QPushButton *reStartButton;
    QLineEdit *serverSendEdit;
    QLabel *connectLabel;
    QLabel *lastOneLabel;
    QPushButton *getButton_2;
    QPushButton *StartAsBlack;
    QPushButton *reConnectButton;
    QPushButton *getButton_1;
    QPushButton *pushButton;
    QLineEdit *serverGetEdit;
    QPushButton *serverSendButton;
    QLineEdit *messhow;

    void setupUi(QWidget *netting)
    {
        if (netting->objectName().isEmpty())
            netting->setObjectName("netting");
        netting->resize(788, 319);
        layoutWidget = new QWidget(netting);
        layoutWidget->setObjectName("layoutWidget");
        layoutWidget->setGeometry(QRect(30, 60, 526, 278));
        gridLayout = new QGridLayout(layoutWidget);
        gridLayout->setObjectName("gridLayout");
        gridLayout->setContentsMargins(0, 0, 0, 0);
        nameshow = new QLineEdit(layoutWidget);
        nameshow->setObjectName("nameshow");

        gridLayout->addWidget(nameshow, 9, 1, 1, 4);

        PORTEdit = new QLineEdit(layoutWidget);
        PORTEdit->setObjectName("PORTEdit");
        PORTEdit->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(PORTEdit, 1, 1, 1, 2);

        IPEdit = new QLineEdit(layoutWidget);
        IPEdit->setObjectName("IPEdit");
        IPEdit->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(IPEdit, 1, 0, 1, 1);

        clientGetEdit = new QLineEdit(layoutWidget);
        clientGetEdit->setObjectName("clientGetEdit");

        gridLayout->addWidget(clientGetEdit, 4, 0, 1, 1);

        nameEdit = new QLineEdit(layoutWidget);
        nameEdit->setObjectName("nameEdit");

        gridLayout->addWidget(nameEdit, 7, 0, 1, 4);

        reSetButton = new QPushButton(layoutWidget);
        reSetButton->setObjectName("reSetButton");

        gridLayout->addWidget(reSetButton, 1, 3, 1, 1);

        StartAsWhite = new QPushButton(layoutWidget);
        StartAsWhite->setObjectName("StartAsWhite");

        gridLayout->addWidget(StartAsWhite, 8, 2, 1, 3);

        showClientButton = new QPushButton(layoutWidget);
        showClientButton->setObjectName("showClientButton");

        gridLayout->addWidget(showClientButton, 1, 4, 1, 1);

        clientSendEdit = new QLineEdit(layoutWidget);
        clientSendEdit->setObjectName("clientSendEdit");

        gridLayout->addWidget(clientSendEdit, 6, 0, 1, 1);

        clientSendButton = new QPushButton(layoutWidget);
        clientSendButton->setObjectName("clientSendButton");

        gridLayout->addWidget(clientSendButton, 6, 1, 1, 1);

        name_setting = new QPushButton(layoutWidget);
        name_setting->setObjectName("name_setting");

        gridLayout->addWidget(name_setting, 7, 4, 1, 1);

        reStartButton = new QPushButton(layoutWidget);
        reStartButton->setObjectName("reStartButton");

        gridLayout->addWidget(reStartButton, 2, 4, 1, 1);

        serverSendEdit = new QLineEdit(layoutWidget);
        serverSendEdit->setObjectName("serverSendEdit");

        gridLayout->addWidget(serverSendEdit, 6, 2, 1, 2);

        connectLabel = new QLabel(layoutWidget);
        connectLabel->setObjectName("connectLabel");
        connectLabel->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(connectLabel, 2, 0, 1, 1);

        lastOneLabel = new QLabel(layoutWidget);
        lastOneLabel->setObjectName("lastOneLabel");
        lastOneLabel->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(lastOneLabel, 2, 2, 1, 2);

        getButton_2 = new QPushButton(layoutWidget);
        getButton_2->setObjectName("getButton_2");

        gridLayout->addWidget(getButton_2, 4, 4, 1, 1);

        StartAsBlack = new QPushButton(layoutWidget);
        StartAsBlack->setObjectName("StartAsBlack");

        gridLayout->addWidget(StartAsBlack, 8, 0, 1, 2);

        reConnectButton = new QPushButton(layoutWidget);
        reConnectButton->setObjectName("reConnectButton");

        gridLayout->addWidget(reConnectButton, 2, 1, 1, 1);

        getButton_1 = new QPushButton(layoutWidget);
        getButton_1->setObjectName("getButton_1");

        gridLayout->addWidget(getButton_1, 4, 1, 1, 1);

        pushButton = new QPushButton(layoutWidget);
        pushButton->setObjectName("pushButton");

        gridLayout->addWidget(pushButton, 9, 0, 1, 1);

        serverGetEdit = new QLineEdit(layoutWidget);
        serverGetEdit->setObjectName("serverGetEdit");

        gridLayout->addWidget(serverGetEdit, 4, 2, 1, 2);

        serverSendButton = new QPushButton(layoutWidget);
        serverSendButton->setObjectName("serverSendButton");

        gridLayout->addWidget(serverSendButton, 6, 4, 1, 1);

        messhow = new QLineEdit(layoutWidget);
        messhow->setObjectName("messhow");

        gridLayout->addWidget(messhow, 0, 0, 1, 5);


        retranslateUi(netting);

        QMetaObject::connectSlotsByName(netting);
    } // setupUi

    void retranslateUi(QWidget *netting)
    {
        netting->setWindowTitle(QCoreApplication::translate("netting", "Form", nullptr));
        PORTEdit->setText(QCoreApplication::translate("netting", "16667", nullptr));
        IPEdit->setText(QCoreApplication::translate("netting", "10.47.145.75", nullptr));
        reSetButton->setText(QCoreApplication::translate("netting", "ReSet", nullptr));
        StartAsWhite->setText(QCoreApplication::translate("netting", "\346\211\247\347\231\275\345\205\210\350\241\214", nullptr));
        showClientButton->setText(QCoreApplication::translate("netting", "ShowClients", nullptr));
        clientSendButton->setText(QCoreApplication::translate("netting", "ClientSend", nullptr));
        name_setting->setText(QCoreApplication::translate("netting", "nameset", nullptr));
        reStartButton->setText(QCoreApplication::translate("netting", "RestartServer", nullptr));
        connectLabel->setText(QCoreApplication::translate("netting", "Connection fail", nullptr));
        lastOneLabel->setText(QCoreApplication::translate("netting", "LastOne: ", nullptr));
        getButton_2->setText(QCoreApplication::translate("netting", "ServerGet", nullptr));
        StartAsBlack->setText(QCoreApplication::translate("netting", "\346\211\247\351\273\221\345\205\210\350\241\214", nullptr));
        reConnectButton->setText(QCoreApplication::translate("netting", "Reconnect", nullptr));
        getButton_1->setText(QCoreApplication::translate("netting", "CilentGet", nullptr));
        pushButton->setText(QCoreApplication::translate("netting", "\347\224\250\346\210\267\345\220\215\347\247\260", nullptr));
        serverSendButton->setText(QCoreApplication::translate("netting", "ServerSend", nullptr));
    } // retranslateUi

};

namespace Ui {
    class netting: public Ui_netting {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_NETTING_H
