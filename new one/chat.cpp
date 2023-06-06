#include "chat.h"
#include "ui_chat.h"
#include <QtDebug>
#include <QTime>
#include "netting.h"
Chat::Chat(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Chat)
{
    ui->setupUi(this);

    // display welcome infomation
    ui->chatHistoryEdit->appendPlainText(QString("欢迎进入聊天室\n"));
    // read only
    ui->chatHistoryEdit->setReadOnly(true);
    // 焦点移到发送框中
    ui->chatEdit->setFocus();

    this->usernameEdit = new QLineEdit(this);
    this->usernameEdit->setGeometry(10,ui->chatEdit->y(),61,21);
    this->usernameEdit->setText(QString("请输入用户名:"));
    this->usernameEdit->show();
    //qDebug()<<this->usernameEdit->geometry() << " "<< this->ui->chatEdit->geometry();

    // 信号槽
    connect(this->ui->sendButton,&QPushButton::clicked,this,&Chat::send);
}
//发送信息
bool Chat::send(){
    QString text = this->ui->chatEdit->text();
    QString username = this->usernameEdit->text();
    QDateTime current;
    QString time = current.currentDateTime().toString("MMM dd hh:mm::ss");
    QString data = time + " " + username + "\n" + text;
    this->ui->chatEdit->setText("");
    if(text == ""){
        return false;
    }
    //qDebug()<<data;
    this->ui->chatHistoryEdit->appendPlainText(data+"\n");
    emit send_info(text);
    return true;
}

Chat::~Chat()
{
    delete ui;
}
