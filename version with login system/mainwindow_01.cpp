#include "mainwindow_01.h"
#include "ui_mainwindow_01.h"
#include"mainwindow.h"
#include"yonghu.h"

MainWindow_01::MainWindow_01(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow_01)
{
//    Black_player="";
//    White_player="";
//    haveblack=0;
//    havewhite=0;
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
//    if(haveblack){
//        ui->user_black->setText(White_player);
//    }
//    if(havewhite){
//        ui->user_white->setText(Black_player);
//    }

}

MainWindow_01::~MainWindow_01()
{
    delete ui;
}



