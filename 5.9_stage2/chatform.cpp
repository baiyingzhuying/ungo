#include "chatform.h"
#include "ui_chatform.h"
#include"netting.h"
#include"network/networkdata.h"
#include"mainwindow.h"
#include<QMouseEvent>
#include<QPainter>

ChatForm::ChatForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui:: ChatForm)
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
    this->usernameEdit->setText(QString("张三"));
    this->usernameEdit->show();
    qDebug()<<this->usernameEdit->geometry() << " "<< this->ui->chatEdit->geometry();

    // 信号槽
    connect(this->ui->sendButton,&QPushButton::clicked,this,&MainWindow::send);
}

bool ChatForm::send(){
    QString text = this->ui->chatEdit->text();
    QString username = this->usernameEdit->text();
    QDateTime current;
    QString time = current.currentDateTime().toString("MMM dd hh:mm::ss");
    QString data = time + " " + username + "\t" + text;
    this->ui->chatEdit->setText("");
    if(text == ""){
        return false;
    }
    qDebug()<<data;
    this->ui->chatHistoryEdit->appendPlainText(data+"\n");
    return true;
}

ChatForm::~ChatForm()
{
    delete ui;
}
