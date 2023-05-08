#include "setting.h"
#include"mainwindow.h"
#include"ui_setting.h"
setting::setting(QWidget *parent):
    QWidget(parent),
    ui(new Ui::setting)
{
    ui->setupUi(this);
    ui->numedit->setValidator(new QIntValidator(1,100,this));
}
setting::~setting() {
    delete ui;
}

