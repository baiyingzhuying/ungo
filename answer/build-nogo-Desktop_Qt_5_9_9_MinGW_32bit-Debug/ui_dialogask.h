/********************************************************************************
** Form generated from reading UI file 'dialogask.ui'
**
** Created by: Qt User Interface Compiler version 5.9.9
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DIALOGASK_H
#define UI_DIALOGASK_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>

QT_BEGIN_NAMESPACE

class Ui_DialogAsk
{
public:
    QDialogButtonBox *buttonBox;
    QLabel *label;

    void setupUi(QDialog *DialogAsk)
    {
        if (DialogAsk->objectName().isEmpty())
            DialogAsk->setObjectName(QStringLiteral("DialogAsk"));
        DialogAsk->resize(400, 300);
        buttonBox = new QDialogButtonBox(DialogAsk);
        buttonBox->setObjectName(QStringLiteral("buttonBox"));
        buttonBox->setGeometry(QRect(30, 240, 341, 32));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);
        label = new QLabel(DialogAsk);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(60, 90, 251, 71));

        retranslateUi(DialogAsk);
        QObject::connect(buttonBox, SIGNAL(accepted()), DialogAsk, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), DialogAsk, SLOT(reject()));

        QMetaObject::connectSlotsByName(DialogAsk);
    } // setupUi

    void retranslateUi(QDialog *DialogAsk)
    {
        DialogAsk->setWindowTitle(QApplication::translate("DialogAsk", "Save", Q_NULLPTR));
        label->setText(QApplication::translate("DialogAsk", "<html><head/><body><p align=\"center\">\346\230\257\345\220\246\351\234\200\350\246\201\345\255\230\347\233\230</p><p align=\"center\">\357\274\210\345\267\262\347\273\217\345\256\214\347\273\223\347\232\204\346\270\270\346\210\217\346\227\240\346\263\225\345\255\230\345\202\250\357\274\211</p></body></html>", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class DialogAsk: public Ui_DialogAsk {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DIALOGASK_H
