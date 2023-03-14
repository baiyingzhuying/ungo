#include "noticewidget.h"
#include "ui_noticewidget.h"

NoticeWidget::NoticeWidget(QString str, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::NoticeWidget)
{
    ui->setupUi(this);
    ui->label->setText(str);
    ui->label->setAlignment(Qt ::AlignCenter);
    this->setWindowFlags(Qt::WindowStaysOnTopHint);

}

NoticeWidget::~NoticeWidget()
{
    delete ui;
}

void NoticeWidget::on_pushButton_clicked()
{
    NoticeWidget ::close();
}
