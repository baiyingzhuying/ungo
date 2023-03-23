#include "mainwindow_01.h"
#include "ui_mainwindow_01.h"
#include"mainwindow.h"
#include"yonghu.h"

MainWindow_01::MainWindow_01(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow_01)
{
    ui->setupUi(this);
    connect(ui->StartGame,&QPushButton::clicked,this,[=](){
        MainWindow * game= new MainWindow;
        this->close();
        game->show();

    });
    connect(ui->login,&QPushButton::clicked,this,[=](){
        YongHu * user=new YongHu;
        this->close();
        user->show();


    });

}

MainWindow_01::~MainWindow_01()
{
    delete ui;
}




