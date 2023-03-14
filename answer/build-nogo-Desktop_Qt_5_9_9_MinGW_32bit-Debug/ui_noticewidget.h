/********************************************************************************
** Form generated from reading UI file 'noticewidget.ui'
**
** Created by: Qt User Interface Compiler version 5.9.9
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_NOTICEWIDGET_H
#define UI_NOTICEWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_NoticeWidget
{
public:
    QLabel *label;
    QPushButton *pushButton;

    void setupUi(QWidget *NoticeWidget)
    {
        if (NoticeWidget->objectName().isEmpty())
            NoticeWidget->setObjectName(QStringLiteral("NoticeWidget"));
        NoticeWidget->resize(400, 300);
        NoticeWidget->setStyleSheet(QStringLiteral(""));
        label = new QLabel(NoticeWidget);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(80, 38, 211, 71));
        label->setStyleSheet(QString::fromUtf8("font: 10pt \"\345\256\213\344\275\223\";"));
        label->setAlignment(Qt::AlignCenter);
        pushButton = new QPushButton(NoticeWidget);
        pushButton->setObjectName(QStringLiteral("pushButton"));
        pushButton->setGeometry(QRect(145, 210, 112, 34));
        pushButton->setStyleSheet(QString::fromUtf8("font: 10pt \"\345\256\213\344\275\223\";\n"
"background-color: rgb(198, 198, 198);"));

        retranslateUi(NoticeWidget);

        QMetaObject::connectSlotsByName(NoticeWidget);
    } // setupUi

    void retranslateUi(QWidget *NoticeWidget)
    {
        NoticeWidget->setWindowTitle(QApplication::translate("NoticeWidget", "Tips", Q_NULLPTR));
        label->setText(QString());
        pushButton->setText(QApplication::translate("NoticeWidget", "\345\245\275\347\232\204", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class NoticeWidget: public Ui_NoticeWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_NOTICEWIDGET_H
