#include "mainwindow_01.h"
#include "ui_mainwindow_01.h"
#include"mainwindow.h"
#include"yonghu.h"

MainWindow_01::MainWindow_01(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow_01)
{
    ui->setupUi(this);
}

MainWindow_01::~MainWindow_01()
{
    delete ui;
}

void MainWindow_01::on_StartGame_clicked()
{
    MainWindow * game= new MainWindow;
    this->close();
    game->show();
}


void MainWindow_01::on_YongHu_clicked()
{
    YongHu * user=new YongHu;
    this->close();
    user->show();
}

