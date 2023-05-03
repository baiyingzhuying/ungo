#include"netting.h"
#include"network/networkdata.h"
#include"mainwindow.h"
#include"ui_netting.h"
#include"ui_ready.h"

netting::netting(QWidget *parent):
    QWidget(parent),
    ui(new Ui::netting)
{
    ui->setupUi(this);
    // 本地 IP，所有电脑都可以用这个 IP 指向自己
    IP = "127.0.0.1";
    // 端口，不要太简单，要避免和别的软件冲突
    PORT = 16667;

    this->ui->IPEdit->setText(IP);
    this->ui->PORTEdit->setText(QString::number(PORT));

    // 创建一个服务端
    this->server = new NetworkServer(this);

    lastOne = nullptr;
    // 创建一个客户端

    this->socket = new NetworkSocket(new QTcpSocket(),this);
    this->ui->nameshow->setReadOnly(true);
    connect(this->socket->base(),&QTcpSocket::connected,this,[&](){
        this->ui->connectLabel->setText("connection succeed");
        id=1;//作为客户端,如果是0那么是服务器
        real_ip=0;
    });
    connect(this->ui->StartAsBlack,&QPushButton::clicked,this,&netting::AsBlackClicked);
    connect(this->ui->StartAsWhite,&QPushButton::clicked,this,&netting::AsWhiteClicked);
    connect(this->socket,&NetworkSocket::receive,this,&netting::receieveDataFromServer);
    connect(this->server,&NetworkServer::receive,this,&netting::receieveData);
    connect(this->socket,&NetworkSocket::receive,this,&netting::recdata);
    connect(this->server,&NetworkServer::receive,this,&netting::recdata_AsServer);
    connect(this->ui->clientSendButton,&QPushButton::clicked,this,&netting::onClientSendButtonClicked);
    connect(this->ui->serverSendButton,&QPushButton::clicked,this,&netting::onServerSendButtonClicked);
    connect(this->ui->showClientButton,&QPushButton::clicked,this,[&](){qDebug()<<clients;});
    connect(this->ui->reSetButton,&QPushButton::clicked,this,&netting::reSet);
    connect(this->ui->reConnectButton,&QPushButton::clicked,this,&netting::reConnect);
    connect(this->ui->reStartButton,&QPushButton::clicked,this,&netting::reStart);
    connect(this->ui->name_setting,&QPushButton::clicked,this,&netting::namesetting);
    connect(re->ui->disagree,&QPushButton::clicked,this,[=](){
        if(id==1) {
            this->socket->send(NetworkData(OPCODE::REJECT_OP,this->ui->nameEdit->text(),"c"));
            this->re->close();
        }else{
            this->server->send(lastOne,NetworkData(OPCODE::REJECT_OP,this->ui->nameEdit->text(),"s"));
            this->re->close();
        }
    });
    // 客户端向 IP:PORT 连接，不会连到自己
    this->socket->hello(IP,PORT);
    // 阻塞等待，2000ms超时
    this->socket->base()->waitForConnected(2000);
}
netting::~netting() {
    delete ui;
}
void netting::receieveData(QTcpSocket* client, NetworkData data)
{
    qDebug()<<"Server get a data: "<<client<<" "<<data.encode();
    lastOne=client;
    // 获得地址的字符串表示，调试用
    QString ptrStr = QString("0x%1").arg((quintptr)client,
                                         QT_POINTER_SIZE, 16, QChar('0'));
    this->ui->lastOneLabel->setText("LastOne: "+ptrStr);
    this->clients.insert(client);
    this->ui->serverGetEdit->setText(data.data1);
    //qDebug()<<"qwq"<<(data.op==OPCODE::READY_OP);
    //qDebug()<<id<<sendid;
    lastOne=client;
    clients.insert(client);
    switch(data.op) {
    case OPCODE::GIVEUP_END_OP:
    case OPCODE::GIVEUP_OP:
    case OPCODE::READY_OP:
        qDebug()<<"ready";
        if(id==sendid) {
            if(data.data2=='w'){
                re->ui->lineEdit->setText("对方希望执白先行，同意开始游戏吗？");
                re->show();
                connect(re->ui->agree,&QPushButton::clicked,this,[=](){
                    mw->show();
                    re->close();
                    this->close();

                    if(id==1) {
                        this->socket->send(NetworkData(OPCODE::READY_OP,this->ui->nameEdit->text(),"hhhh"));
                    }else {
                        this->server->send(lastOne,NetworkData(OPCODE::READY_OP,this->ui->nameEdit->text(),"hhhh"));
                    }
                });
            }else if(data.data2=='b'){
                re->ui->lineEdit->setText("对方希望执黑先行，同意开始游戏吗？");
                re->show();
                connect(re->ui->agree,&QPushButton::clicked,this,[=](){
                    mw->show();
                    re->close();
                    this->close();

                    if(id==1) {
                        this->socket->send(NetworkData(OPCODE::READY_OP,this->ui->nameEdit->text(),"hhhh"));
                    }else {
                        this->server->send(lastOne,NetworkData(OPCODE::READY_OP,this->ui->nameEdit->text(),"hhhh"));
                    }
                });
            }
        }else if(id!=sendid){

                mw->show();
                this->close();

        }
    case OPCODE::LEAVE_OP:
    case OPCODE::CHAT_OP:
    case OPCODE::MOVE_OP:
    case OPCODE::REJECT_OP:
        if(id==sendid) {
            this->ui->messhow->setText(QString("Your invitation has been rejected."));
        }else {
            this->ui->messhow->setText(QString("You have rejected an invitation"));
        }
    case OPCODE::SUICIDE_END_OP:
    case OPCODE::TIMEOUT_END_OP:
    default: break;
    }
}

void netting::receieveDataFromServer(NetworkData data)
{
    qDebug()<<"Client get a data: "<<data.encode();
    this->ui->clientGetEdit->setText(data.data1);
    qDebug()<<"qwq"<<(data.op==OPCODE::READY_OP);
    qDebug()<<id<<sendid;

    qDebug() << (data.op==OPCODE::READY_OP);
    switch(data.op) {
    case OPCODE::GIVEUP_END_OP:
    case OPCODE::GIVEUP_OP:
    case OPCODE::READY_OP:
        qDebug()<<"ready";
        if(real_ip==sendid) {
            if(data.data2=='w'){
                re->ui->lineEdit->setText("对方希望执白先行，同意开始游戏吗？");
                re->show();
                connect(re->ui->agree,&QPushButton::clicked,this,[=](){
                    mw->show();
                    re->close();
                    this->close();

                    if(id==1) {
                        this->socket->send(NetworkData(OPCODE::READY_OP,this->ui->nameEdit->text(),"hhhh"));
                    }else {
                        this->server->send(lastOne,NetworkData(OPCODE::READY_OP,this->ui->nameEdit->text(),"hhhh"));
                    }
                });
            }else if(data.data2=='b'){
                re->ui->lineEdit->setText("对方希望执黑先行，同意开始游戏吗？");
                re->show();
                connect(re->ui->agree,&QPushButton::clicked,this,[=](){
                    mw->show();
                    re->close();
                    this->close();
                    if(id==1) {
                        this->socket->send(NetworkData(OPCODE::READY_OP,this->ui->nameEdit->text(),"hhhhh"));
                    }else {
                        this->server->send(lastOne,NetworkData(OPCODE::READY_OP,this->ui->nameEdit->text(),"hhhhhh"));
                    }
                });
            }
        }else {
            mw->show();
            this->close();
        }
    case OPCODE::LEAVE_OP:
    case OPCODE::CHAT_OP:
    case OPCODE::MOVE_OP:
    case OPCODE::REJECT_OP:
        if(id==1) this->socket->send(NetworkData(OPCODE::REJECT_OP,this->ui->nameEdit->text(),"hhhhh"));
        else this->server->send(lastOne,NetworkData(OPCODE::REJECT_OP,this->ui->nameEdit->text(),"hhhhh"));
        if(real_ip==sendid) {
            this->ui->messhow->setText(QString("Your invitation has been rejected."));
        }else {
            this->ui->messhow->setText(QString("You have rejected an invitation"));
        }
    case OPCODE::SUICIDE_END_OP:
    case OPCODE::TIMEOUT_END_OP:
    default: break;
    }

    // recdata(data);
}

void netting::onClientSendButtonClicked()
{
    this->socket->send(NetworkData(OPCODE::CHAT_OP,this->ui->clientSendEdit->text(),"send by client"));
}
//ready op
void netting::AsWhiteClicked() {
    qDebug()<<"white";
    if(id==1){
        qDebug()<<"white";
        this->socket->send(NetworkData(OPCODE::READY_OP,this->ui->nameEdit->text(),"w"));
    }
    else {
        if(lastOne){
            this->server->send(lastOne,NetworkData(OPCODE::READY_OP,this->ui->nameEdit->text(),"w"));

        }
    }
}
void netting::AsBlackClicked() {
    qDebug()<<"black";
    if(id==1){
        this->socket->send(NetworkData(OPCODE::READY_OP,this->ui->nameEdit->text(),"b"));

    }else {
        if(lastOne){
            this->server->send(lastOne,NetworkData(OPCODE::READY_OP,this->ui->nameEdit->text(),"b"));
        }
    }
}
//
void netting::onServerSendButtonClicked()
{
    if(lastOne)
        this->server->send(lastOne,NetworkData(OPCODE::CHAT_OP,this->ui->serverSendEdit->text(),"send by server"));
}

void netting::reStart()
{
    qDebug()<<"restart the server.";
    this->ui->lastOneLabel->setText("LastOne: ");
    this->ui->connectLabel->setText("disconnect");
    id=0;
    disconnect(this->server,&NetworkServer::receive,this,&netting::receieveData);
    clients.clear();
    delete this->server;
    this->server = new NetworkServer(this);
    // 端口相当于传信息的窗户，收的人要在这守着
    this->server->listen(QHostAddress::Any,PORT);
    lastOne = nullptr;
    connect(this->server,&NetworkServer::receive,this,&netting::receieveData);
}

void netting::reConnect()
{
    qDebug()<<"client reconnect to the server.";
    this->ui->connectLabel->setText("connection fail");

    this->socket->bye();
    this->socket->hello(IP,PORT);
    if(!this->socket->base()->waitForConnected(3000)){
        qDebug()<<"reconnect fail";
    }
    else{
        socket->send(NetworkData(OPCODE::CHAT_OP, "", ""));
    }
}

void netting::reSet()
{
    this->ui->connectLabel->setText("connection fail");
    IP=this->ui->IPEdit->text();
    PORT=this->ui->PORTEdit->text().toInt();
    this->reStart();
    this->reConnect();
}
void netting::namesetting() {
    nameE=this->ui->nameEdit->text();
    if(nameE.contains(QRegularExpression("[\\s]+"))){
        QString str="该名称非法，请进行修改!";
        this->ui->nameshow->setText(str);
    }else{
    this->ui->nameshow->setText(nameE);
    }
}
bool netting::goin() {
    re->hide();
    mw->show();
}
bool netting::refusal() {
    if(id==sendid) {
    re->ui->lineEdit->setText("对方拒绝了你的游戏请求");
    re->ui->agree->setText("再试一次");
    re->ui->disagree->setText("关闭");
    }
}
void netting::recdata(NetworkData data) {

}
void netting::recdata_AsServer(QTcpSocket* client, NetworkData data) {

}

