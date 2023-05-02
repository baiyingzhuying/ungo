
#ifndef NETTING_H
#define NETTING_H
#include<QWidget>
#include"network/networkserver.h"
#include"network/networksocket.h"
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
    // 客户端池，NetworkServer 有一个 QList 的，但这里我想用 set，所以又弄了一个
    QSet<QTcpSocket*> clients;
    Ui::netting *ui;
private slots:
    void receieveData(QTcpSocket* client, NetworkData data);
    void receieveDataFromServer(NetworkData data);
    void onClientSendButtonClicked();
    void onServerSendButtonClicked();
    void reStart();
    void reConnect();
    void reSet();

};

#endif // NETTING_H
