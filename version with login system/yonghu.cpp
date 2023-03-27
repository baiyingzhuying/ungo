#include "yonghu.h"
#include "ui_yonghu.h"
#include"mainwindow_01.h"
#include<QSettings>
#include<qapplication.h>
#include<qmessagebox.h>
QString Black_player="";
QString White_player="";
int haveblack=0;
int havewhite=0;


YongHu::YongHu(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::YongHu)
{


    ui->setupUi(this);
    connect(ui->tuichu,&QPushButton::clicked,this,[=](){
        MainWindow_01 * window_01=new MainWindow_01;
        this->close();
        window_01->show();
    });

    //考虑到程序移植问题采用相对路径

    connect(ui->login_black,&QPushButton::clicked,this,&YongHu::login_check_black);
    connect(ui->login_white,&QPushButton::clicked,this,&YongHu::login_check_white);
    connect(ui->zhucejian,&QPushButton::clicked,this,&YongHu::zhuce_check);
}

YongHu::~YongHu()
{
    delete ui;
}

void YongHu::login_check_white(){
    QString configFilePath =QCoreApplication::applicationDirPath()+"/config/user.ini";
    QSettings settings(configFilePath,QSettings::IniFormat);

    QString yhm=ui->yonghuming->text();
    QString mm=ui->mima->text();
//    QStringList userlist = settings.value("users").toStringList();

    if(settings.contains("users/"+yhm)){
        if(mm==settings.value(QString("users/%1").arg(yhm)).toString()){
            QMessageBox::information(this,"提示","登录成功！");
//            this->close();
            White_player=yhm;
            havewhite=1;
        }
        else {
            QMessageBox::critical(this,"Critical","密码错误！");
        }
    }
    else {
            QMessageBox::critical(this,"Critical","用户名不存在！请先注册！");
    }
}

void YongHu::login_check_black(){
    QString configFilePath =QCoreApplication::applicationDirPath()+"/config/user.ini";
    QSettings settings(configFilePath,QSettings::IniFormat);

    QString yhm=ui->yonghuming->text();
    QString mm=ui->mima->text();
//    QStringList userlist = settings.value("users").toStringList();

    if(settings.contains("users/"+yhm)){
        if(mm==settings.value(QString("users/%1").arg(yhm)).toString()){
            QMessageBox::information(this,"提示","登录成功！");
//            this->close();
            Black_player=yhm;
            haveblack=1;
        }
        else {
            QMessageBox::critical(this,"Critical","密码错误！");
        }
    }
    else {
            QMessageBox::critical(this,"Critical","用户名不存在！请先注册！");
    }
}

void YongHu::zhuce_check(){
    QString configFilePath =QCoreApplication::applicationDirPath()+"/config/user.ini";
    QSettings settings(configFilePath,QSettings::IniFormat);

    QString yhm=ui->yonghuming->text();
    QString mm=ui->mima->text();
//    QStringList userlist = settings.value("users").toStringList();

    if(settings.contains("users/"+yhm)) QMessageBox::information(this,"提示","用户名已存在！！！");
    else {
        settings.setValue("users/"+yhm,mm);
        settings.sync();
        QMessageBox::information(this,"提示","注册成功！");
    }
}





