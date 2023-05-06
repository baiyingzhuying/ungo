#include "aswhite.h"
#include "ui_aswhite.h"

AsWhite::AsWhite(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AsWhite)
{
    ui->setupUi(this);
}

AsWhite::~AsWhite()
{
    delete ui;
}
