#include "zhuce.h"
#include "ui_zhuce.h"
#include"yonghu.h"
zhuce::zhuce(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::zhuce)
{
    ui->setupUi(this);


}

zhuce::~zhuce()
{
    delete ui;
}
