#include "ready.h"
#include "ui_ready.h"
#include"chat.h"
ready::ready(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ready)
{
    ui->setupUi(this);
}

ready::~ready()
{
    delete ui;
}
