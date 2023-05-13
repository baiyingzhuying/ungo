#include"netting.h"
#include"network/networkdata.h"
#include"mainwindow.h"
#include"ui_netting.h"
#include"ui_ready.h"
#include<QMouseEvent>
#include"ui_mainwindow.h"
#include<QPainter>
#include"mainwindow.h"
#include"mainwindow_01.h"
#include"QDateTime"
#include"chat.h"
#include "ui_chat.h"
#include <QtDebug>
#include <QTime>
netting::netting(QWidget *parent):
    QWidget(parent),
    ui(new Ui::netting)
{

    ui->setupUi(this);
    // 本地 IP，所有电脑都可以用这个 IP 指向自己
    IP = "10.47.188.51";
    // 端口，不要太简单，要避免和别的软件冲突
    PORT = 16667;
    this->ui->IPEdit->setText(IP);
    this->ui->PORTEdit->setText(QString::number(PORT));

    // 创建一个服务端
    this->server = new NetworkServer(this);

    lastOne = nullptr;
    // 创建一个客户端
    memset(items,0,sizeof(items));
    this->socket = new NetworkSocket(new QTcpSocket(),this);
    this->ui->nameshow->setReadOnly(true);
    connect(this->socket->base(),&QTcpSocket::connected,this,[&](){
        this->ui->connectLabel->setText("connection succeed");
        id=1;//作为客户端,如果是0那么是服务器
    });
    connect(chat,SIGNAL(send_info(QString)),this,SLOT(send_OP(QString)));//聊天
    connect(this->ui->StartAsBlack,&QPushButton::clicked,this,&netting::AsBlackClicked);//执黑先行
    connect(this->ui->StartAsWhite,&QPushButton::clicked,this,&netting::AsWhiteClicked);//执白先行
    connect(this->socket,&NetworkSocket::receive,this,&netting::receieveDataFromServer);//客户端接收信息
    connect(this->server,&NetworkServer::receive,this,&netting::receieveData);//服务器接收信息
    connect(this->ui->clientSendButton,&QPushButton::clicked,this,&netting::onClientSendButtonClicked);//客户端发送信息
    connect(this->ui->serverSendButton,&QPushButton::clicked,this,&netting::onServerSendButtonClicked);//服务器发送信息
    connect(this->ui->showClientButton,&QPushButton::clicked,this,[&](){qDebug()<<clients;});//显示链接列表
    connect(this->ui->reSetButton,&QPushButton::clicked,this,&netting::reSet);//重新设置
    connect(this->ui->reConnectButton,&QPushButton::clicked,this,&netting::reConnect);//重连
    connect(this->ui->reStartButton,&QPushButton::clicked,this,&netting::reStart);//重开
    connect(this->ui->name_setting,&QPushButton::clicked,this,&netting::namesetting);//设置名称
    //leave_op
    connect(this->ui->byebye,&QPushButton::clicked,this,[=](){
        if(id==1) {
            this->socket->send(NetworkData(OPCODE::LEAVE_OP,this->nameE,""));
            this->socket->bye();}
        if(id==0) {
            this->server->send(lastOne,NetworkData(OPCODE::LEAVE_OP,this->nameE,""));
        }
    });
    //reject_op
    connect(re->ui->disagree,&QPushButton::clicked,this,[=](){
        if(id==1) {
            this->socket->send(NetworkData(OPCODE::REJECT_OP,this->nameE,"c"));
            this->socket->bye();
            this->re->close();
        }else{
            this->server->send(lastOne,NetworkData(OPCODE::REJECT_OP,this->nameE,"s"));
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
//服务器端的所有操作,编号为0
void netting::receieveData(QTcpSocket* client, NetworkData data)
{

    int x,y;
   // qint64 rec_time=0;
    //qint64 time_now_=0;
    QChar zy;
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
    QDateTime current;
    QString time = current.currentDateTime().toString("MMM dd hh:mm::ss");
    QString info;
    timee=QDateTime::currentDateTime();
    timee.toString("yyy-MM-dd hh:mm::ss");
    switch(data.op) {
    case OPCODE::GIVEUP_END_OP:
        if(!havesend_end_op){
            this->server->send(lastOne,NetworkData(OPCODE::GIVEUP_END_OP,this->nameE,""));
            havesend_end_op=true;
            color=0;
        }
        info = time + " " + "Opponent" + " " +"GIVEUP_END_OP "+data.data1+ " "+data.data2+"\n";
        break;
    case OPCODE::GIVEUP_OP:
        //qDebug()<<real_color<<you_give_up;
        received_give_up_op=true;
        if(received_give_up_op==true) {
            game->ui->report->setText("对方已经认输，你已经赢了");
            game->ui->report->show();
            color=0;
        }
        if(real_color==1&&!you_give_up) {

            if(!havesend_end_op){
                this->server->send(lastOne,NetworkData(OPCODE::GIVEUP_END_OP,this->nameE,""));
                havesend_end_op=true;
                color=0;
            }
        }else if(real_color==2&&!you_give_up){

            if(!havesend_end_op){
                this->server->send(lastOne,NetworkData(OPCODE::GIVEUP_END_OP,this->nameE,""));
                havesend_end_op=true;
                color=0;
            }
        }
        info = time + " " + "Opponent" + " " +"GIVEUP_OP "+data.data1+ " "+data.data2+"\n";
        break;
    case OPCODE::READY_OP:
        memset(items,0,sizeof(items));
        already_connected=true;
        qDebug()<<already_connected;
        game->time_now=game->remaining_time=5;
        //qDebug()<<"ready";
        //qDebug()<<id<<sendid;
        if(id!=sendid) {
            if(data.data2=='w'){
                re->ui->lineEdit->setText("对方希望执白先行，同意开始游戏吗？");
                re->show();
                connect(re->ui->agree,&QPushButton::clicked,this,[=](){
//                    Chat * chat=new Chat;
                    chat->show();
                    your_turn=true;
                    re->close();
                    this->close();
                    color=1;
                    real_color=1;
                    your_turn=true;
                    this->server->send(lastOne,NetworkData(OPCODE::READY_OP,this->ui->nameEdit->text(),"b"));

                });
            }else if(data.data2=='b'){
                re->ui->lineEdit->setText("对方希望执黑先行，同意开始游戏吗？");
                re->show();
                connect(re->ui->agree,&QPushButton::clicked,this,[=](){
//                    Chat * chat=new Chat;
                    chat->show();
                    re->close();
                    this->close();
                    color=2;
                    real_color=2;
                    this->server->send(lastOne,NetworkData(OPCODE::READY_OP,this->ui->nameEdit->text(),"w"));
                });
            }
        }else if(id==sendid){
            already_start=true;
//            Chat * chat=new Chat;
            chat->show();
        }
        info = time + " " + "Opponent" + " " +"READY_OP "+data.data1+ " "+data.data2+"\n";
        break;
    case OPCODE::LEAVE_OP:
        info = time + " " + "Opponent" + " " +"LEAVE_OP "+data.data1+ " "+data.data2+"\n";
        break;
    case OPCODE::CHAT_OP:      
        chat->ui->chatHistoryEdit->appendPlainText(info+"\n");
        info = time + " " + "Opponent" + " " +"CHAT_OP "+data.data1+ " "+data.data2+"\n";
        break;
    case OPCODE::MOVE_OP:
        have_send_move_op=false;
        received_move_op=true;
        game->time_now=game->remaining_time;
        game->time->stop();
        qDebug()<<"213213123";
        your_turn=true;
        zy=data.data1.at(0);
        x=data.data1.mid(1).toInt();
        y=zy.toLatin1()-'A'+1;
        color=real_color;
        //rec_time=data.data2.toLongLong();
        //time_now_=QDateTime::currentMSecsSinceEpoch();

        if(items[x][y]) {
            this->server->send(lastOne,NetworkData(OPCODE::SUICIDE_END_OP,this->nameE,""));
            game->ui->report->setText("对方非法落子，你赢了");
            game->ui->report->show();
            this->havesend_sui_op=true;
            color=0;
            return;
        }else{
//            if(time_now_-rec_time>game->remaining_time*1000) {
//                this->server->send(lastOne,NetworkData(OPCODE::TIMEOUT_END_OP,this->nameE,""));
//                game->ui->report->setText("对方超时了，你赢了");
//                game->ui->report->show();
//                have_send_time_out_op=true;
//                color=0;
//                return;
//            }
        items[x][y]=3-real_color;
        qDebug()<<x<<y;
        zz=false,rr=false;
        memset(visits,0,sizeof(visits));
        checks(x,y);
        memset(visits,0,sizeof(visits));
        checks2(x,y);
        qDebug()<<rr<<zz;
        if(zz==false||rr==false) {
            this->havesend_sui_op=true;
                game->ui->report->setText("对方非法落子，你赢了");
            game->ui->report->show();
            this->server->send(lastOne,NetworkData(OPCODE::SUICIDE_END_OP,this->nameE,""));
            color=0;
            return;
        }

        }
        info = time + " " + "Opponent" + " " +"MOVE_OP "+data.data1+ " "+data.data2+"\n";
        game->ui->quitButton->show();
        break;
    case OPCODE::REJECT_OP:
        if(id!=sendid) {
            this->ui->messhow->setText(QString("Your invitation has been rejected."));
        }else {
            this->ui->messhow->setText(QString("You have rejected an invitation"));
        }
        your_turn=false;
        info = time + " " + "Opponent" + " " +"REJECT_OP "+data.data1+ " "+data.data2+"\n";
        break;
    case OPCODE::SUICIDE_END_OP:
        info = time + " " + "sender" + " " +"SUICIDE_END_OP "+data.data1+ " "+data.data2+"\n";
        if(!havesend_sui_op) {
            received_suicide_end_op=true;
            havesend_sui_op=true;
            QFile file("daily.txt");
            if (!file.open(QIODevice::Append | QIODevice::Text)) {
            //qDebug() << "Failed to open file";
            return;
            }

            QTextStream out(&file);
            out<<info;
            file.close();
            this->server->send(lastOne,NetworkData(OPCODE::SUICIDE_END_OP,this->nameE,""));
        }

        if(received_suicide_end_op==true) {
            game->ui->report->setText("您非法落子，寄了");
            game->ui->report->show();
            color=0;
        }
        info = time + " " + "Opponent" + " " +"SUICIDE_END_OP "+data.data1+ " "+data.data2+"\n";
        break;
    case OPCODE::TIMEOUT_END_OP:
        received_time_out=true;
        if(!have_send_time_out_op){
            have_send_time_out_op=true;
            game->ui->report->setText("您超时了，寄");
            game->ui->report->show();
            this->server->send(lastOne,NetworkData(OPCODE::TIMEOUT_END_OP,this->nameE,""));
            color=0;

        }
        info = time + " " + "Opponent" + " " +"TIMEOUT_END_OP "+data.data1+ " "+data.data2+"\n";
        break;
    default: break;
    }
    QFile file("daily.txt");
    if (!file.open(QIODevice::Append | QIODevice::Text)) {
        //qDebug() << "Failed to open file";
        return;
    }

    QTextStream out(&file);
    out<<info;
    file.close();
    //QString currentPath = QDir::currentPath();
    //qDebug() << "Current working directory: " << currentPath;
    //return true;
}

void netting::receieveDataFromServer(NetworkData data)
{//客户端，编号为1
    int x,y;
    qint64 rec_time=0;
    qint64 time_now_=0;
    QChar zy;
    qDebug()<<"Client get a data: "<<data.encode();
    this->ui->clientGetEdit->setText(data.data1);
    qDebug()<<"qwq"<<(data.op==OPCODE::READY_OP);

    QDateTime current;
    QString time = current.currentDateTime().toString("MMM dd hh:mm::ss");
    QString info = time + " " + "Opponent" + "\n" + data.data1;
    //qDebug()<<id<<sendid;
    //qDebug() << (data.op==OPCODE::READY_OP);
    switch(data.op) {
    case OPCODE::GIVEUP_END_OP:
        if(!havesend_end_op){
            this->socket->send(NetworkData(OPCODE::GIVEUP_END_OP,this->nameE,""));
            havesend_end_op=true;
            color=0;
        }
        info = time + " " + "Opponent" + " " +"GIVEUP_END_OP "+data.data1+ " "+data.data2+"\n";
        break;
    case OPCODE::GIVEUP_OP:
        received_give_up_op=true;
        if(received_give_up_op==true) {
            game->ui->report->setText("对方已经认输，你已经赢了");
            game->ui->report->show();
            color=0;
        }
        if(real_color==1&&!you_give_up) {
            if(!havesend_end_op){
                this->socket->send(NetworkData(OPCODE::GIVEUP_END_OP,this->nameE,""));
                havesend_end_op=true;
                color=0;
            }
        }else if(real_color==2&&!you_give_up){
            if(!havesend_end_op){
                this->socket->send(NetworkData(OPCODE::GIVEUP_END_OP,this->nameE,""));
                havesend_end_op=true;
                color=0;
            }
        }
        info = time + " " + "Opponent" + " " +"GIVEUP_OP "+data.data1+ " "+data.data2+"\n";
        break;
    case OPCODE::READY_OP:
        memset(items,0,sizeof(items));
        already_connected=true;
        qDebug()<<already_connected;
        //qDebug()<<"ready";
        game->time_now=game->remaining_time=5;
        if(id!=sendid) {
            if(data.data2=='w'){
                re->ui->lineEdit->setText("对方希望执白先行，同意开始游戏吗？");

                re->show();
                connect(re->ui->agree,&QPushButton::clicked,this,[=](){
//                    Chat * chat=new Chat;
                    chat->show();
                    your_turn=true;
                    already_start=true;
                    re->close();
                    this->close();
                    color=1;
                    real_color=1;
                    your_turn=true;
                    this->socket->send(NetworkData(OPCODE::READY_OP,this->nameE,"b"));

                });
            }else if(data.data2=='b'){
                re->ui->lineEdit->setText("对方希望执黑先行，同意开始游戏吗？");
                re->show();
                connect(re->ui->agree,&QPushButton::clicked,this,[=](){
//                    Chat * chat=new Chat;
                    chat->show();
                    already_start=true;
                    color=2;
                    real_color=2;
                    re->close();
                    this->close();
                    this->socket->send(NetworkData(OPCODE::READY_OP,this->nameE,"w"));
                });
            }
        }else {
            already_start=true;
            this->close();
//            Chat * chat=new Chat;
            chat->show();
        }
        info = time + " " + "Opponent" + " " +"READY_OP "+data.data1+ " "+data.data2+"\n";
        break;
    case OPCODE::LEAVE_OP:
        this->socket->bye();
        info = time + " " + "Opponent" + " " +"LEAVE_OP "+data.data1+ " "+data.data2+"\n";
        break;
    case OPCODE::CHAT_OP:
        chat->ui->chatHistoryEdit->appendPlainText(info+"\n");
        info = time + " " + "Opponent" + " " +"TIMEOUT_END_OP "+data.data1+ " "+data.data2+"\n";
        break;
    case OPCODE::MOVE_OP:
        have_send_move_op=false;
        received_move_op=true;
        your_turn=true;
        game->time_now=game->remaining_time;
        game->time->stop();
        qDebug()<<"213213123";
        zy=data.data1.at(0);
        x=data.data1.mid(1).toInt();
        y=zy.toLatin1()-'A'+1;

        //qDebug()<<x<<y;
        color=real_color;
        rec_time=data.data2.toLongLong();
        time_now_=QDateTime::currentMSecsSinceEpoch();

        if(items[x][y]) {
            this->havesend_sui_op=true;
            this->socket->send(NetworkData(OPCODE::SUICIDE_END_OP,this->nameE,""));
            game->ui->report->setText("对方非法落子，你赢了");
            game->ui->report->show();
            color=0;
            return;
        }else{
//            if(time_now_-rec_time>game->remaining_time*1000) {
//                this->socket->send(NetworkData(OPCODE::TIMEOUT_END_OP,this->nameE,""));
//                game->ui->report->setText("对方超时了，你赢了");
//                game->ui->report->show();
//                have_send_time_out_op=true;
//                color=0;
//                return;
//            }
        items[x][y]=3-real_color;
        qDebug()<<items[x][y];
        zz=false,rr=false;
        memset(visits,0,sizeof(visits));
        checks(x,y);
        memset(visits,0,sizeof(visits));
        checks2(x,y);
           qDebug()<<rr<<zz;
        if(zz==false||rr==false) {
            this->havesend_sui_op=true;
            this->socket->send(NetworkData(OPCODE::SUICIDE_END_OP,this->nameE,""));
            game->ui->report->setText("对方非法落子，你赢了");
            game->ui->report->show();
            color=0;
            return ;
        }
        info = time + " " + "Opponent" + " " +"MOVE_OP "+data.data1+ " "+data.data2+"\n";
        }
        game->ui->quitButton->show();
        break;
    case OPCODE::REJECT_OP:
        if(id==1) this->socket->send(NetworkData(OPCODE::REJECT_OP,this->ui->nameEdit->text(),"hhhhh"));
        else this->server->send(lastOne,NetworkData(OPCODE::REJECT_OP,this->ui->nameEdit->text(),"hhhhh"));
        if(id!=sendid) {
            this->ui->messhow->setText(QString("Your invitation has been rejected."));
        }else {
            this->ui->messhow->setText(QString("You have rejected an invitation"));
        }
        your_turn=false;
        info = time + " " + "Opponent" + " " +"REJECT_OP "+data.data1+ " "+data.data2+"\n";
        break;
    case OPCODE::SUICIDE_END_OP:

        if(!havesend_sui_op) {
            havesend_sui_op=true;
            received_suicide_end_op=true;
            this->socket->send(NetworkData(OPCODE::SUICIDE_END_OP,this->nameE,""));
        }
        if(havesend_sui_op==true) {
            game->ui->report->setText("对方非法落子，你赢了");
            game->ui->report->show();
            color=0;
        }
        if(received_suicide_end_op==true) {
            game->ui->report->setText("您非法落子，寄了");
            game->ui->report->show();
            color=0;
        }
        info = time + " " + "Opponent" + " " +"SUICIDE_END_OP "+data.data1+ " "+data.data2+"\n";
        break;
    case OPCODE::TIMEOUT_END_OP:
        received_time_out=true;
        if(!have_send_time_out_op){
            game->ui->report->setText("您超时了，寄");
            game->ui->report->show();
            have_send_time_out_op=true;
            this->socket->send(NetworkData(OPCODE::TIMEOUT_END_OP,this->nameE,""));
            color=0;
        }
        info = time + " " + "Opponent" + " " +"TIMEOUT_END_OP "+data.data1+ " "+data.data2+"\n";
        break;
    default: break;
    }
    QFile file("daily.txt");
    if (!file.open(QIODevice::Append | QIODevice::Text)) {
        //qDebug() << "Failed to open file";
        return;
    }

    QTextStream out(&file);
    out<<info;
    file.close();
    // recdata(data);
}

void netting::onClientSendButtonClicked()
{
    this->socket->send(NetworkData(OPCODE::CHAT_OP,this->ui->clientSendEdit->text(),"send by client"));
}
//ready op
void netting::AsWhiteClicked() {
    //qDebug()<<"white";
    color=2;
    QDateTime current;
    QString time = current.currentDateTime().toString("MMM dd hh:mm::ss");
    QString info;
    real_color=2;
    if(id==1){
        sendid=1;
        //qDebug()<<"white";
        info = time + " " + "sender" + " " +"READY_OP "+nameE+ " "+"w"+"\n";
        QFile file("daily.txt");
        if (!file.open(QIODevice::Append | QIODevice::Text)) {
            //qDebug() << "Failed to open file";
            return;
        }

        QTextStream out(&file);
        out<<info;
        this->socket->send(NetworkData(OPCODE::READY_OP,this->ui->nameEdit->text(),"w"));
    }
    else {
        sendid=0;
        if(lastOne){
            info = time + " " + "sender" + " " +"READY_OP "+nameE+ " "+"w"+"\n";
            QFile file("daily.txt");
            if (!file.open(QIODevice::Append | QIODevice::Text)) {
            //qDebug() << "Failed to open file";
            return;
            }

            QTextStream out(&file);
            out<<info;
            this->server->send(lastOne,NetworkData(OPCODE::READY_OP,this->ui->nameEdit->text(),"w"));
        }
    }
}
void netting::AsBlackClicked() {
    color=1;
    QDateTime current;
    QString time = current.currentDateTime().toString("MMM dd hh:mm::ss");
    QString info;
    real_color=1;
    //qDebug()<<"black";
    if(id==1){
        sendid=1;
        info = time + " " + "sender" + " " +"READY_OP "+nameE+ " "+"b"+"\n";
        QFile file("daily.txt");
        if (!file.open(QIODevice::Append | QIODevice::Text)) {
            //qDebug() << "Failed to open file";
            return;
        }

        QTextStream out(&file);
        out<<info;
        this->socket->send(NetworkData(OPCODE::READY_OP,nameE,"b"));

    }else {
        sendid=0;
        if(lastOne){
            info = time + " " + "sender" + " " +"READY_OP "+nameE+ " "+"b"+"\n";
            QFile file("daily.txt");
            if (!file.open(QIODevice::Append | QIODevice::Text)) {
            //qDebug() << "Failed to open file";
            return;
            }
            QTextStream out(&file);
            out<<info;
            this->server->send(lastOne,NetworkData(OPCODE::READY_OP,nameE,"b"));
        }
    }
    your_turn=true;
}
//
void netting::onServerSendButtonClicked()
{
    if(lastOne){
        this->server->send(lastOne,NetworkData(OPCODE::CHAT_OP,this->ui->serverSendEdit->text(),"send by server"));
    }
}

void netting::reStart()
{
    //qDebug()<<"restart the server.";
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
    //qDebug()<<"client reconnect to the server.";
    this->ui->connectLabel->setText("connection fail");
    this->socket->bye();
    this->socket->hello(IP,PORT);
    if(!this->socket->base()->waitForConnected(3000)){
        //qDebug()<<"reconnect fail";
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
void netting::checks(int x,int y){

    int dx[4]={1,-1,0,0};
    int dy[4]={0,0,1,-1};//四个方向
    visits[x][y]=true;
    for(int i=0;i<=3;i++) {
        if(x+dx[i]>0&&x+dx[i]<ROW+1&&y+dy[i]>0&&y+dy[i]<COLLON+1){

            if(items[x+dx[i]][y+dy[i]]==0) {
                zz= true;//周围有空
                return;
            }else if(items[x+dx[i]][y+dy[i]]!=items[x][y]) {
                continue;
            }else {
                if(!visits[x+dx[i]][y+dy[i]]){
                    visits[x+dx[i]][y+dy[i]]=true;
                    checks(x+dx[i],y+dy[i]);
                }else {
                    continue;
                }
            }
        }//禁落点的判断
    }
    return;
}
void netting::checks3(int x,int y) {
    int dx[4]={1,-1,0,0};
    int dy[4]={0,0,1,-1};//四个方向
    visits[x][y]=true;
    for(int i=0;i<=3;i++) {
        if(x+dx[i]>0&&x+dx[i]<ROW+1&&y+dy[i]>0&&y+dy[i]<COLLON+1)
            if(items[x+dx[i]][y+dy[i]]==0) {
                rr= true;//周围有空
                return;
            }else if(items[x+dx[i]][y+dy[i]]!=items[x][y]) {
                continue;
            }else {
                if(!visits[x+dx[i]][y+dy[i]]){
                    visits[x+dx[i]][y+dy[i]]=true;
                    checks3(x+dx[i],y+dy[i]);
                }else {
                    continue;
                }
            }
    }//禁落点的判断

    return;
}
void netting::checks2(int x,int y) {
    int jishu3=0;
    int dx[4]={1,-1,0,0};
    int dy[4]={0,0,1,-1};//四个方向
    for(int i=0;i<=3;i++) {
        int x1=x+dx[i],y1=y+dy[i];
        if(x+dx[i]>0&&x+dx[i]<ROW+1&&y+dy[i]>0&&y+dy[i]<COLLON+1){
            if(items[x1][y1]!=items[x][y]&&items[x1][y1]!=0 ){
                rr=false;
                checks3(x1,y1);
                if(rr==false) return;
            }else if(items[x1][y1]==0||items[x1][y1]==items[x][y]){
                jishu3++;
            }else {
                continue;
            }
        }
    }
    if(jishu3==4) {
        rr=true;
        return;
    }
    if(jishu3==3&&((x==1&&y!=COLLON&&y!=1)||(y!=1&&y!=COLLON&&x==ROW)||(y==1&&x!=COLLON&&x!=1)||(x!=1&&x!=COLLON&&y==ROW))){
        rr=true;
        return;
    }
    if(jishu3==2&&(x==COLLON&&y==1)||(x==1&&y==1)||(x==1&&y==ROW)||(x==COLLON&&y==COLLON)){
        rr=true;
        return;
    }
}

void netting::send_OP(QString info){
    QDateTime current;
    QString time = current.currentDateTime().toString("MMM dd hh:mm::ss");
    QString ww;
    if(id==0){
        ww = time + " " + "sender" + " " +"CHAT_OP "+info+ " "+""+"\n";
        QFile file("daily.txt");
        if (!file.open(QIODevice::Append | QIODevice::Text)) {
            //qDebug() << "Failed to open file";
            return;
        }
        QTextStream out(&file);
        out<<ww;
        this->server->send(lastOne,NetworkData(OPCODE::CHAT_OP,info,""));
    }else{
        ww = time + " " + "sender" + " " +"CHAT_OP "+info+ " "+""+"\n";
        QFile file("daily.txt");
        if (!file.open(QIODevice::Append | QIODevice::Text)) {
            //qDebug() << "Failed to open file";
            return;
        }
        QTextStream out(&file);
        out<<ww;
        this->socket->send(NetworkData(OPCODE::CHAT_OP,info,""));
    }
}
