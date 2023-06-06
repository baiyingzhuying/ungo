/********************************************************************************
** Form generated from reading UI file 'chat.ui'
**
** Created by: Qt User Interface Compiler version 6.4.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CHAT_H
#define UI_CHAT_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Chat
{
public:
    QWidget *centralwidget;
    QPushButton *sendButton;
    QLineEdit *chatEdit;
    QPlainTextEdit *chatHistoryEdit;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *Chat)
    {
        if (Chat->objectName().isEmpty())
            Chat->setObjectName("Chat");
        Chat->resize(400, 356);
        centralwidget = new QWidget(Chat);
        centralwidget->setObjectName("centralwidget");
        sendButton = new QPushButton(centralwidget);
        sendButton->setObjectName("sendButton");
        sendButton->setGeometry(QRect(260, 270, 80, 24));
        chatEdit = new QLineEdit(centralwidget);
        chatEdit->setObjectName("chatEdit");
        chatEdit->setGeometry(QRect(140, 270, 113, 23));
        chatHistoryEdit = new QPlainTextEdit(centralwidget);
        chatHistoryEdit->setObjectName("chatHistoryEdit");
        chatHistoryEdit->setGeometry(QRect(140, 10, 201, 251));
        Chat->setCentralWidget(centralwidget);
        menubar = new QMenuBar(Chat);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 400, 21));
        Chat->setMenuBar(menubar);
        statusbar = new QStatusBar(Chat);
        statusbar->setObjectName("statusbar");
        Chat->setStatusBar(statusbar);

        retranslateUi(Chat);

        QMetaObject::connectSlotsByName(Chat);
    } // setupUi

    void retranslateUi(QMainWindow *Chat)
    {
        Chat->setWindowTitle(QCoreApplication::translate("Chat", "MainWindow", nullptr));
        sendButton->setText(QCoreApplication::translate("Chat", "Send", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Chat: public Ui_Chat {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CHAT_H
