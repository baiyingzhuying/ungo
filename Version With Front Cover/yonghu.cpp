#include "yonghu.h"
#include "ui_yonghu.h"
#include"mainwindow_01.h"
YongHu::YongHu(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::YongHu)
{
    ui->setupUi(this);
}

YongHu::~YongHu()
{
    delete ui;
}

void YongHu::on_pushButton_3_clicked()
{
    MainWindow_01 * window_01=new MainWindow_01;
    this->close();
    window_01->show();
}

