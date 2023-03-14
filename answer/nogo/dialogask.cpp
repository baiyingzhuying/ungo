#include "dialogask.h"
#include "ui_dialogask.h"

DialogAsk::DialogAsk(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogAsk)
{
    ui->setupUi(this);
}

DialogAsk::~DialogAsk()
{
    delete ui;
}

void DialogAsk::on_buttonBox_accepted()
{
    emit acceptload();
    close();
}

void DialogAsk::on_buttonBox_rejected()
{
    emit rejectload();
    close();
}
