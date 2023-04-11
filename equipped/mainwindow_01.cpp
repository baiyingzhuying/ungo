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
//        this->close();
        user->show();

    });
    connect(ui->Broad,QOverload<int>::of(&QComboBox::activated),[=](int index){
        if(index==0){
            ROW=9;
            COLLON=9;
        }
        else if(index==1){
            ROW=11;
            COLLON=11;
        }
        else if(index==2){
            ROW=13;
            COLLON=13;
        }

    });
//    if(haveblack){
//        ui->user_black->setText(Black_player);
//        qApp->processEvents();
//    }
//    if(havewhite){
//        ui->user_white->setText(White_player);
//        qApp->processEvents();
//    }

}

MainWindow_01::~MainWindow_01()
{
    delete ui;
}

void MainWindow_01::setWhiteUser(QString &text){
    this->ui->user_white->setText(text);
    qDebug()<<"2";
    Cover->show();
    qApp->processEvents();
}
void MainWindow_01::setBlackUser(QString &text){
    this->ui->user_black->setText(text);
    qDebug()<<"1";
    Cover->show();
    qApp->processEvents();
}



