#include "yonghu.h"
#include "ui_yonghu.h"
#include"mainwindow_01.h"
#include<QSettings>

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


    QString path ="E:/NoGo/NoGo";
    QSettings * config =new QSettings(path,QSettings::IniFormat);

    //用户名base64加密
    QString uidsec =ui->yonghuming->text();
    QByteArray uidb64 = uidsec.toLocal8Bit().toBase64();
    QString uid = QString::fromLocal8Bit(uidb64);


    //密码base64加密
    QString pwdsec = ui->mima->text();
    QByteArray pwdb64 = pwdsec.toLocal8Bit().toBase64();
    QString pwd = QString::fromLocal8Bit(pwdb64);

    //将信息写入配置文件
    config->beginGroup("config");
    config->setValue("uid",uid);
    config->setValue("pwd",pwd);
    config->endGroup();
//    connect(ui->login,&QPushButton::clicked,this,&Activation::activation);




}

YongHu::~YongHu()
{
    delete ui;
}

