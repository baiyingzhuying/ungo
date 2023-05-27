#ifndef NETTING_H
#define NETTING_H
#include"network/networkserver.h"
#include"network/networksocket.h"
#include"ready.h"
#include<QLineEdit>
#include"chat.h"
#include<QDateTime>
#include<QQueue>
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
    QQueue<QTcpSocket*> clients;
    QLineEdit *rep;
    Ui::netting *ui;
    int id =0;
    int sendid=2;
    int color;
    int real_color;
    bool havesend_end_op=false;
    bool havesend_sui_op=false;
    ready *re=new ready;
    bool game_start=false;
    bool you_give_up=false;
    bool zz=false,rr=false;
    bool received_give_up_op=false;
    bool received_suicide_end_op=false;
    bool received_move_op=false;
    bool received_time_out=false;
    bool have_send_move_op=false;
    bool have_send_time_out_op=false;
    bool visits[20][20];
    void checks(int x,int y);
    void checks2(int x,int y);
    void checks3(int x,int y);
    int items[20][20];
    bool already_start=false;
    bool already_connected=false;
    bool your_turn=false;
    Chat * chat=new Chat;
    QDateTime timee;
    QQueue<NetworkData>receive_ready_op;
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
    void send_OP(QString);


};

#endif // NETTING_H
