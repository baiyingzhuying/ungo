/********************************************************************************
** Form generated from reading UI file 'dialog.ui'
**
** Created by: Qt User Interface Compiler version 5.9.9
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DIALOG_H
#define UI_DIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_dialog
{
public:
    QLabel *label;
    QPushButton *pushButton;
    QPushButton *pushButton_2;

    void setupUi(QDialog *dialog)
    {
        if (dialog->objectName().isEmpty())
            dialog->setObjectName(QStringLiteral("dialog"));
        dialog->resize(1400, 1102);
        dialog->setStyleSheet(QStringLiteral("background-color: rgb(215, 215, 255);"));
        label = new QLabel(dialog);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(45, 92, 921, 961));
        label->setStyleSheet(QStringLiteral("image:url(:/Image/Image/photonew.jpg)"));
        pushButton = new QPushButton(dialog);
        pushButton->setObjectName(QStringLiteral("pushButton"));
        pushButton->setGeometry(QRect(1120, 560, 150, 150));
        pushButton->setStyleSheet(QString::fromUtf8("QPushButton{\n"
"	font: 16pt \"\345\215\216\346\226\207\350\241\214\346\245\267\";\n"
"border-radius:75px;\n"
"background-color: rgb(254, 255, 172);\n"
"}"));
        pushButton_2 = new QPushButton(dialog);
        pushButton_2->setObjectName(QStringLiteral("pushButton_2"));
        pushButton_2->setGeometry(QRect(1120, 350, 150, 150));
        pushButton_2->setStyleSheet(QString::fromUtf8("QPushButton{\n"
"	font: 16pt \"\345\215\216\346\226\207\350\241\214\346\245\267\";\n"
"border-radius:75px;\n"
"background-color: rgb(254, 255, 172);\n"
"}"));

        retranslateUi(dialog);

        QMetaObject::connectSlotsByName(dialog);
    } // setupUi

    void retranslateUi(QDialog *dialog)
    {
        dialog->setWindowTitle(QApplication::translate("dialog", "Game", Q_NULLPTR));
        label->setText(QString());
        pushButton->setText(QApplication::translate("dialog", "\351\200\200\345\207\272", Q_NULLPTR));
        pushButton_2->setText(QApplication::translate("dialog", "\345\255\230\347\233\230", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class dialog: public Ui_dialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DIALOG_H
