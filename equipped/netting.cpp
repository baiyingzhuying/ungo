#include"netting.h"
#include"network/networkdata.h"

#include"ui_netting.h"
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

    connect(this->socket->base(),&QTcpSocket::connected,this,[&](){this->ui->connectLabel->setText("connection succeed");});
    connect(this->socket,&NetworkSocket::receive,this,&netting::receieveDataFromServer);
    connect(this->server,&NetworkServer::receive,this,&netting::receieveData);
    connect(this->ui->clientSendButton,&QPushButton::clicked,this,&netting::onClientSendButtonClicked);
    connect(this->ui->serverSendButton,&QPushButton::clicked,this,&netting::onServerSendButtonClicked);
    connect(this->ui->showClientButton,&QPushButton::clicked,this,[&](){qDebug()<<clients;});
    connect(this->ui->reSetButton,&QPushButton::clicked,this,&netting::reSet);
    connect(this->ui->reConnectButton,&QPushButton::clicked,this,&netting::reConnect);
    connect(this->ui->reStartButton,&QPushButton::clicked,this,&netting::reStart);

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
}

void netting::receieveDataFromServer(NetworkData data)
{
    qDebug()<<"Client get a data: "<<data.encode();
    this->ui->clientGetEdit->setText(data.data1);
}

void netting::onClientSendButtonClicked()
{
    this->socket->send(NetworkData(OPCODE::CHAT_OP,this->ui->clientSendEdit->text(),"send by client"));
}

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
}

void netting::reSet()
{
    this->ui->connectLabel->setText("connection fail");
    IP=this->ui->IPEdit->text();
    PORT=this->ui->PORTEdit->text().toInt();
    this->reStart();
    this->reConnect();
}
