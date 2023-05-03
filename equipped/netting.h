
#ifndef NETTING_H
#define NETTING_H
#include<QWidget>
#include"network/networkserver.h"
#include"network/networksocket.h"
#include"ready.h"
#include"mainwindow.h"
namespace Ui{
class netting;
}
class netting:public QWidget{
    Q_OBJECT
public:
    explicit netting(QWidget *parent = nullptr);
    ~netting();
    // 服务端
    NetworkServer* server;
    // 客户端
    NetworkSocket* socket;
    // 最后一个客户端
    QTcpSocket* lastOne;
    QString IP;
    int PORT;
    QString nameE;
    // 客户端池，NetworkServer 有一个 QList 的，但这里我想用 set，所以又弄了一个
    QSet<QTcpSocket*> clients;
    Ui::netting *ui;
    int id=0;
    int real_ip=1;
    int sendid=0;
    ready *re=new ready;
    MainWindow *mw=new MainWindow;

private slots:
    void receieveData(QTcpSocket* client, NetworkData data);
    void receieveDataFromServer(NetworkData data);
    void onClientSendButtonClicked();
    void onServerSendButtonClicked();
    void reStart();
    void reConnect();
    void reSet();
    void AsBlackClicked();
    void AsWhiteClicked();
    void namesetting();
    void recdata(NetworkData data);
    void recdata_AsServer(QTcpSocket* client, NetworkData data);
    bool goin();
    bool refusal();

};

#endif // NETTING_H
