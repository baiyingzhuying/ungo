#include "unready.h"
#include "ui_unready.h"

unready::unready(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::unready)
{
    ui->setupUi(this);
}

unready::~unready()
{
    delete ui;
}
