#include "login_success.h"
#include "ui_login_success.h"

login_success::login_success(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::login_success)
{
    ui->setupUi(this);
}

login_success::~login_success()
{
    delete ui;
}
