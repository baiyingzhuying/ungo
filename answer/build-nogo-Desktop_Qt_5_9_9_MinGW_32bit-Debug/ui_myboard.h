/********************************************************************************
** Form generated from reading UI file 'myboard.ui'
**
** Created by: Qt User Interface Compiler version 5.9.9
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MYBOARD_H
#define UI_MYBOARD_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHeaderView>

QT_BEGIN_NAMESPACE

class Ui_myboard
{
public:

    void setupUi(QDialog *myboard)
    {
        if (myboard->objectName().isEmpty())
            myboard->setObjectName(QStringLiteral("myboard"));
        myboard->resize(400, 300);

        retranslateUi(myboard);

        QMetaObject::connectSlotsByName(myboard);
    } // setupUi

    void retranslateUi(QDialog *myboard)
    {
        myboard->setWindowTitle(QApplication::translate("myboard", "Dialog", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class myboard: public Ui_myboard {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MYBOARD_H
