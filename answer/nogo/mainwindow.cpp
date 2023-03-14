#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "dialog.h"

#include <QByteArray>
#include <QFile>
#include <QFileInfo>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->radioButton->setChecked(true);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{

    dialog* dlg=new dialog();
    dlg->show();
    QCoreApplication ::processEvents();
    if (ui->radioButton_2->isChecked())
        dlg->do_first_step();
    if (ui->radioButton_3->isChecked()) {
        QString path("../nogo/board.txt");
        QFile file(path);
        bool openok = file.open(QIODevice ::ReadOnly);
        QString array=file.readAll();
        file.close();
        dlg->reloadgame(array);
    }
}
