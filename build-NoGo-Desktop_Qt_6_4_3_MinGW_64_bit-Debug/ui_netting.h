/********************************************************************************
** Form generated from reading UI file 'netting.ui'
**
** Created by: Qt User Interface Compiler version 6.4.3
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
    QLineEdit *serverSendEdit;
    QLineEdit *clientSendEdit;
    QLineEdit *PORTEdit;
    QPushButton *StartAsBlack;
    QLineEdit *nameEdit;
    QPushButton *getButton_2;
    QPushButton *StartAsWhite;
    QPushButton *reStartButton;
    QLineEdit *serverGetEdit;
    QPushButton *showClientButton;
    QPushButton *serverSendButton;
    QPushButton *getButton_1;
    QLineEdit *IPEdit;
    QPushButton *name_setting;
    QLineEdit *clientGetEdit;
    QLabel *lastOneLabel;
    QLineEdit *nameshow;
    QPushButton *reSetButton;
    QLabel *connectLabel;
    QPushButton *clientSendButton;
    QPushButton *reConnectButton;
    QPushButton *pushButton;
    QPushButton *byebye;
    QLineEdit *messhow;

    void setupUi(QWidget *netting)
    {
        if (netting->objectName().isEmpty())
            netting->setObjectName("netting");
        netting->resize(696, 433);
        layoutWidget = new QWidget(netting);
        layoutWidget->setObjectName("layoutWidget");
        layoutWidget->setGeometry(QRect(30, 60, 526, 283));
        gridLayout = new QGridLayout(layoutWidget);
        gridLayout->setObjectName("gridLayout");
        gridLayout->setContentsMargins(0, 0, 0, 0);
        serverSendEdit = new QLineEdit(layoutWidget);
        serverSendEdit->setObjectName("serverSendEdit");

        gridLayout->addWidget(serverSendEdit, 6, 2, 1, 2);

        clientSendEdit = new QLineEdit(layoutWidget);
        clientSendEdit->setObjectName("clientSendEdit");

        gridLayout->addWidget(clientSendEdit, 6, 0, 1, 1);

        PORTEdit = new QLineEdit(layoutWidget);
        PORTEdit->setObjectName("PORTEdit");
        PORTEdit->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(PORTEdit, 1, 1, 1, 2);

        StartAsBlack = new QPushButton(layoutWidget);
        StartAsBlack->setObjectName("StartAsBlack");

        gridLayout->addWidget(StartAsBlack, 8, 0, 1, 2);

        nameEdit = new QLineEdit(layoutWidget);
        nameEdit->setObjectName("nameEdit");

        gridLayout->addWidget(nameEdit, 7, 0, 1, 4);

        getButton_2 = new QPushButton(layoutWidget);
        getButton_2->setObjectName("getButton_2");

        gridLayout->addWidget(getButton_2, 4, 4, 1, 1);

        StartAsWhite = new QPushButton(layoutWidget);
        StartAsWhite->setObjectName("StartAsWhite");

        gridLayout->addWidget(StartAsWhite, 8, 2, 1, 3);

        reStartButton = new QPushButton(layoutWidget);
        reStartButton->setObjectName("reStartButton");

        gridLayout->addWidget(reStartButton, 2, 4, 1, 1);

        serverGetEdit = new QLineEdit(layoutWidget);
        serverGetEdit->setObjectName("serverGetEdit");

        gridLayout->addWidget(serverGetEdit, 4, 2, 1, 2);

        showClientButton = new QPushButton(layoutWidget);
        showClientButton->setObjectName("showClientButton");

        gridLayout->addWidget(showClientButton, 1, 4, 1, 1);

        serverSendButton = new QPushButton(layoutWidget);
        serverSendButton->setObjectName("serverSendButton");

        gridLayout->addWidget(serverSendButton, 6, 4, 1, 1);

        getButton_1 = new QPushButton(layoutWidget);
        getButton_1->setObjectName("getButton_1");

        gridLayout->addWidget(getButton_1, 4, 1, 1, 1);

        IPEdit = new QLineEdit(layoutWidget);
        IPEdit->setObjectName("IPEdit");
        IPEdit->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(IPEdit, 1, 0, 1, 1);

        name_setting = new QPushButton(layoutWidget);
        name_setting->setObjectName("name_setting");

        gridLayout->addWidget(name_setting, 7, 4, 1, 1);

        clientGetEdit = new QLineEdit(layoutWidget);
        clientGetEdit->setObjectName("clientGetEdit");

        gridLayout->addWidget(clientGetEdit, 4, 0, 1, 1);

        lastOneLabel = new QLabel(layoutWidget);
        lastOneLabel->setObjectName("lastOneLabel");
        lastOneLabel->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(lastOneLabel, 2, 2, 1, 2);

        nameshow = new QLineEdit(layoutWidget);
        nameshow->setObjectName("nameshow");

        gridLayout->addWidget(nameshow, 9, 1, 1, 4);

        reSetButton = new QPushButton(layoutWidget);
        reSetButton->setObjectName("reSetButton");

        gridLayout->addWidget(reSetButton, 1, 3, 1, 1);

        connectLabel = new QLabel(layoutWidget);
        connectLabel->setObjectName("connectLabel");
        connectLabel->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(connectLabel, 2, 0, 1, 1);

        clientSendButton = new QPushButton(layoutWidget);
        clientSendButton->setObjectName("clientSendButton");

        gridLayout->addWidget(clientSendButton, 6, 1, 1, 1);

        reConnectButton = new QPushButton(layoutWidget);
        reConnectButton->setObjectName("reConnectButton");

        gridLayout->addWidget(reConnectButton, 2, 1, 1, 1);

        pushButton = new QPushButton(layoutWidget);
        pushButton->setObjectName("pushButton");

        gridLayout->addWidget(pushButton, 9, 0, 1, 1);

        byebye = new QPushButton(layoutWidget);
        byebye->setObjectName("byebye");

        gridLayout->addWidget(byebye, 0, 0, 1, 1);

        messhow = new QLineEdit(layoutWidget);
        messhow->setObjectName("messhow");

        gridLayout->addWidget(messhow, 0, 1, 1, 4);


        retranslateUi(netting);

        QMetaObject::connectSlotsByName(netting);
    } // setupUi

    void retranslateUi(QWidget *netting)
    {
        netting->setWindowTitle(QCoreApplication::translate("netting", "Form", nullptr));
        PORTEdit->setText(QCoreApplication::translate("netting", "16667", nullptr));
        StartAsBlack->setText(QCoreApplication::translate("netting", "\346\211\247\351\273\221\345\205\210\350\241\214", nullptr));
        getButton_2->setText(QCoreApplication::translate("netting", "ServerGet", nullptr));
        StartAsWhite->setText(QCoreApplication::translate("netting", "\346\211\247\347\231\275\345\205\210\350\241\214", nullptr));
        reStartButton->setText(QCoreApplication::translate("netting", "RestartServer", nullptr));
        showClientButton->setText(QCoreApplication::translate("netting", "ShowClients", nullptr));
        serverSendButton->setText(QCoreApplication::translate("netting", "ServerSend", nullptr));
        getButton_1->setText(QCoreApplication::translate("netting", "CilentGet", nullptr));
        IPEdit->setText(QCoreApplication::translate("netting", "10.47.145.75", nullptr));
        name_setting->setText(QCoreApplication::translate("netting", "nameset", nullptr));
        lastOneLabel->setText(QCoreApplication::translate("netting", "LastOne: ", nullptr));
        reSetButton->setText(QCoreApplication::translate("netting", "ReSet", nullptr));
        connectLabel->setText(QCoreApplication::translate("netting", "Connection fail", nullptr));
        clientSendButton->setText(QCoreApplication::translate("netting", "ClientSend", nullptr));
        reConnectButton->setText(QCoreApplication::translate("netting", "Reconnect", nullptr));
        pushButton->setText(QCoreApplication::translate("netting", "\347\224\250\346\210\267\345\220\215\347\247\260", nullptr));
        byebye->setText(QCoreApplication::translate("netting", "\346\272\234\344\272\206\346\272\234\344\272\206", nullptr));
    } // retranslateUi

};

namespace Ui {
    class netting: public Ui_netting {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_NETTING_H
