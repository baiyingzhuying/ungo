#include "mainwindow.h"
#include"ai.h"
#include "ui_mainwindow.h"
#include"mainwindow_01.h"
#include"setting.h"
#include<QPainter>
#include<QMouseEvent>
#include<QMessageBox>
#include<QPoint>
#include<QtCore/qmath.h>
#include<QLabel>
#include"ui_setting.h"

#include<qpainterpath.h>
#include<QPixmap>
#include<qpropertyanimation.h>
#include<QRandomGenerator>
#include<qrandom.h>
#include<QTime>
#include<qmediaplayer.h>
#include <QtCore/QCoreApplication>
#include <QtMultimedia/QMediaPlayer>
#include<qaudiooutput.h>
#include<qsoundeffect.h>
#include"network/networkdata.h"
#include"network/networkserver.h"
#include"network/networksocket.h"
#include"ui_netting.h"
#include"ai.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{


    ui->setupUi(this);
    this->setFixedSize(1050,850);
    move(100,100);
    QFont font("Arial",16);
    m_bIsBlackTun=1;//初始化落子颜色
    memset(m_items,0,sizeof(m_items));
    //清空落子
    time=new QTimer(this);
    time->stop();
    time->setInterval(100);//间隔为0.1s
    this->ui->restart->hide();//隐藏重开按钮
    this->ui->reproduce->hide();//隐藏重现按钮
    this->ui->report->hide();
    hideall();
    connect(time,&QTimer::timeout,this,&MainWindow::on_time);//开始倒计时
    connect(this->ui->quitButton,&QPushButton::clicked,this,&MainWindow::yougiveup);//认输按钮
    connect(this->ui->startButton,&QPushButton::clicked,this,&MainWindow::start);//开始按钮
    connect(this->ui->restart,&QPushButton::clicked,this,&MainWindow::restarted);//重开
    connect(this->ui->savebutton,&QPushButton::clicked,this,&MainWindow::save);//保存
    connect(this->ui->reproduce,&QPushButton::clicked,this,&MainWindow::read_in);//读入
    connect(this->ui->setbutton,&QPushButton::clicked,this,&MainWindow::setting_show);
    connect(ww->ui->sure,&QPushButton::clicked,this,&MainWindow::time_set);
    //    connect(this->ui->AI_start,&QPushButton::clicked,this,&MainWindow::inite);//这样我们就实现了信息的传递
    connect(this->ui->net_setting,&QPushButton::clicked,this,&MainWindow::net_set);
    connect(this->ui->showing,&QPushButton::clicked,this,&MainWindow::bofang);
    connect(this->ui->last,&QPushButton::clicked,this,&MainWindow::last);
    connect(this->ui->next,&QPushButton::clicked,this,&MainWindow::next);
    connect(this->ui->stop,&QPushButton::clicked,this,&MainWindow::zanting);
    connect(this->ui->ensure,&QPushButton::clicked,this,&MainWindow::sure);
    connect(this->ui->UseAI,&QPushButton::clicked,this,&MainWindow::onSwitchModeButtonClicked);
    connect(this->ui->UseAI,&QPushButton::clicked,this,[=]{
        if(net->already_connected)
            USE_AI=!USE_AI;
    });

}
MainWindow::~MainWindow()//终止
{
    delete ui;
}
//画棋盘
void MainWindow::DrawCHessBroad()//画个棋盘
{


    QPainter painter(this);
    QPen pen(Qt::black, 4); // 定义黑色画笔
    QBrush brush(QColor(173, 216, 230)); // 定义浅黄色画刷
    painter.setPen(pen);
    painter.setBrush(brush);    
    // 绘制棋盘边框
    painter.drawRect(WIDTH/2, HEIGHT/2, (ROW)*WIDTH, (COLLON)*HEIGHT);    
    // 绘制棋盘格子
    for(int i = 0; i < ROW-1; i++)
    {
        for(int j = 0; j < COLLON-1; j++)
        {
            painter.drawRect((i+1)*WIDTH, (j+1)*HEIGHT, WIDTH, HEIGHT);
        }
    }
    QFont font("Arial", 12);
    painter.setFont(font);  
    // 绘制行数字
    for(int i = 0; i < ROW; i++) {
        painter.drawText(QRectF((i+0.8)*WIDTH, 0, WIDTH, HEIGHT),  QString::number(i+1));
    }    
    // 绘制列字母
    for(int i = 0; i < COLLON; i++) {
        painter.drawText(QRectF(0, (i+0.8)*HEIGHT, WIDTH, HEIGHT),  QString(QChar('A' + i)));
    }
}
//画棋子
void MainWindow::DrawItems() //画个棋子
{


    if(!net->already_connected){
        QPainter painter(this);
        QImage pic; 
        for(int i=0; i<=ROW; i++)
        {
            for(int j=0; j<=COLLON; j++)
            {
                if(m_items[i][j] == 1){
                    painter.setPen(Qt::NoPen);
                    painter.setBrush(QBrush(QColor(255, 192, 203)));
                }
                else if(m_items[i][j] == 2){
                    painter.setPen(Qt::NoPen);
                    painter.setBrush(QBrush(QColor(220, 208, 255)));
                }
                else{
                    continue;
                }
                //获取棋子位置
                painter.setRenderHint(QPainter::Antialiasing);
                QPoint ptCenter(i*WIDTH, j*HEIGHT);
                //绘制棋子，棋子的半径为宽高的一半
                painter.drawEllipse(ptCenter, WIDTH * 45/100, HEIGHT * 45/100);
                painter.setBrush(QBrush(QColor(255, 255, 255)));
                painter.drawEllipse(ptCenter, WIDTH*25/100, HEIGHT*25/100);

                QPoint pt(i,j);
                if(!reproduced&&pt==lastMove) {
                    painter.setBrush(Qt::red);
                    painter.drawEllipse(ptCenter,WIDTH*25/100,HEIGHT*25/100);//标记上一个落子
                }
            }
        }
    }else {//联网部分逻辑
        QPainter painter(this);
        QImage pic;

        for(int i=0; i<=ROW; i++)
        {
            for(int j=0; j<=COLLON; j++)
            {
                if(net->items[i][j] == 1){
                    painter.setPen(Qt::NoPen);
                    painter.setBrush(QBrush(QColor(255, 192, 203)));
                }
                else if(net->items[i][j] == 2){
                    painter.setPen(Qt::NoPen);
                    painter.setBrush(QBrush(QColor(220, 208, 255)));
                }
                else{
                    continue;
                }
                //获取棋子位置
                painter.setRenderHint(QPainter::Antialiasing);
                QPoint ptCenter(i*WIDTH, j*HEIGHT);
                //绘制棋子，棋子的半径为宽高的一半
                painter.drawEllipse(ptCenter, WIDTH * 45/100, HEIGHT * 45/100);
                painter.setBrush(QBrush(QColor(255, 255, 255)));
                painter.drawEllipse(ptCenter, WIDTH*25/100, HEIGHT*25/100);
            }
        }
    }
}
//判断函数（finished)
void MainWindow::check(int x,int y) {//不能下死手

    int dx[4]={1,-1,0,0};
    int dy[4]={0,0,1,-1};//四个方向
    visit[x][y]=true;
    for(int i=0;i<=3;i++) {
        if(x+dx[i]>0&&x+dx[i]<10&&y+dy[i]>0&&y+dy[i]<10){

            if(m_items[x+dx[i]][y+dy[i]]==0) {
                zz= true;//周围有空
                return;
            }else if(m_items[x+dx[i]][y+dy[i]]!=m_items[x][y]) {
                continue;
            }else if(m_items[x+dx[i]][y+dy[i]]==m_items[x][y]){ {
                if(!visit[x+dx[i]][y+dy[i]]){
                    check(x+dx[i],y+dy[i]);
                }else {
                    continue;
                }
            }
        }//禁落点的判断
    }
    }
    return;
    }
void MainWindow::check3(int x,int y) {
    int dx[4]={1,-1,0,0};
    int dy[4]={0,0,1,-1};//四个方向
    visit[x][y]=true;
    for(int i=0;i<=3;i++) {
        if(x+dx[i]>0&&x+dx[i]<=9&&y+dy[i]>0&&y+dy[i]<10)

            if(m_items[x+dx[i]][y+dy[i]]==0) {

                rr= true;//周围有空
                return;
            }else if(m_items[x+dx[i]][y+dy[i]]!=m_items[x][y]) {
                continue;
            }else if(m_items[x+dx[i]][y+dy[i]]==m_items[x][y]){
                if(!visit[x+dx[i]][y+dy[i]]){
                    check3(x+dx[i],y+dy[i]);
                }else {
                    continue;
                }
            }
    }//禁落点的判断  
    return;
}
void MainWindow::check2(int x,int y) {//落子不吃子
    int jishu3=0;
    int dx[4]={1,-1,0,0};
    int dy[4]={0,0,1,-1};//四个方向
    for(int i=0;i<=3;i++) {
        int x1=x+dx[i],y1=y+dy[i];
        if(x+dx[i]>0&&x+dx[i]<ROW+1&&y+dy[i]>0&&y+dy[i]<COLLON+1){
            if(m_items[x1][y1]!=m_items[x][y]&&m_items[x1][y1]!=0 ){
                rr=false;
                check3(x1,y1);
                if(rr==false) return;
            }else if(m_items[x1][y1]==0||m_items[x1][y1]==m_items[x][y]){
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
//落子程序
void MainWindow::mousePressEvent(QMouseEvent *event){//落点位置，改好了，别动
    //    qDebug()<<net->already_connected;
    //    QFile file("AI_save.txt");
    //    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
    //    {
    //        // 打开文件失败

    //    }

    //    // 创建 QTextStream 对象并关联文件
    //    QTextStream in(&file);

    //    // 逐行读取文件并输出到控制台
    //    while (!in.atEnd())
    //    {
    //        QString line = in.readLine();
    //        char ItemColor = line.at(0).toLatin1(); // 提取第一个字符
    //        int pos_y = line.at(1).toLatin1()-'A'+1; // 提取第二个字符
    //        int pos_x = line.mid(2).toInt(); // 提取从第三个字符开始的整数
    //       // qDebug()<<line<<" "<<ItemColor<<" "<<pos_x<<" "<<pos_y<<" "<<Qt::endl;

    //    }
    if(!net->already_connected){//没联网
        if(!allow_start||you_lose||you_giveup||out_of_timelimit) return;//没开始，或者输了，认输，超时，都不能落子
        QPoint pt;
        int chess_x=event->pos().x()+WIDTH/2;//获取鼠标点击的x坐标
        int chess_y=event->pos().y()+HEIGHT/2;//y坐标
        pt.setX(chess_x/WIDTH);//设置x坐标
        pt.setY(chess_y/HEIGHT);//y坐标
        if(pt.x()>=ROW+1||pt.y()>=COLLON+1||pt.x()<1||pt.y()<1) {
            return;
        }
        //        qDebug()<<pt.x();
        //循环所有棋子判断落子出是否存在棋子
        if(m_items[pt.x()][pt.y()]!=0) return;
        pressed=true;//落子成功      
        items[jishu++]=node{m_bIsBlackTun,pt.x(),pt.y(),jishu};
        lastMove=QPoint(pt.x(),pt.y());
        Item item(pt,m_bIsBlackTun);
        int x=item.m_pt.x();
        int y=item.m_pt.y();
        m_items[x][y]=m_bIsBlackTun;
        //判断是否赢。。。。。
        //判定四种情况。。。。。
        rr=false;zz=false;
        memset(visit,0,sizeof(visit));
        check(x,y);
        memset(visit,0,sizeof(visit));
        check2(x,y);
        if(zz==false||rr==false) {
            cant_move[x][y]=true;
            if(times_for_place[x][y]!=2) {
                times_for_place[x][y]++;
                QTextEdit *textEdit=new QTextEdit(this);
                QPoint position(chess_x,chess_y);
                textEdit->move(position);
                QSize size(300,200);
                textEdit->resize(size);
                textEdit->setPlainText("亲，这里不能落子哦");
                textEdit->show();
                QTimer *timer = new QTimer(this);
                // 设置定时器超时时间为2秒
                timer->setInterval(3000);
                // 连接定时器的超时信号到槽函数
                connect(timer, &QTimer::timeout, this, [=]() {
                    // 在定时器超时后执行的程序
                    textEdit->hide();
                    m_items[x][y]=0;
                    jishu--;
                });
                // 启动定时器
                timer->start();
                return;
            }
            you_lose=true;
            //这一段都是显示一个动画用的，不用管
            QImage pool;
            pool.load(":/new/prefix1/lost.jpg");
            QPixmap pixmap = QPixmap::fromImage(pool);
            pixmap = pixmap.scaled(400, 400, Qt::KeepAspectRatio, Qt::SmoothTransformation);
            this->lb = new QLabel(this);
            lb->setGeometry(20, 20, 400, 400); // 设置大小
            lb->setPixmap(pixmap);
            lb->show();
            //动画
            lb->move(this->width()/2-pixmap.width()*0.7,-pixmap.height()*1.5);
            QPropertyAnimation * animation =new QPropertyAnimation(lb,"geometry");
            animation->setDuration(1000);
            animation->setStartValue(QRect(lb->x(),lb->y(),lb->width(),lb->height()));
            animation->setEndValue(QRect(lb->x(),lb->y()+pixmap.height()*2,lb->width(),lb->height()));allow_start=false;
            animation->setEasingCurve(QEasingCurve::OutBounce);
            animation->start();
            //隐藏认输按钮(从而避免一些莫名其妙的bug）
            this->ui->quitButton->hide();
            time->stop();
            allow_start=false;
            if(m_items[x][y]==1&&times_for_place[x][y]==2){
                QString report_message="黑方落子违规，白方玩家胜利\n 总步数：%1\n游戏总时长: %2\n黑方总思考时长: %3\n白方总思考时长: %4";
                QString report_mes=report_message.arg(jishu-1).arg(time_total_black+time_total_white).arg(time_total_black).arg(time_total_white);
                this->ui->report->setPlainText(report_mes);
                this->ui->report->setAlignment(Qt::AlignCenter);
                this->ui->report->show();
                restat();
            }else if(m_items[x][y]==2&&times_for_place[x][y]==2){
                QString report_message="白方落子违规，黑方玩家胜利\n 总步数：%1\n游戏总时长: %2\n黑方总思考时长: %3\n白方总思考时长: %4";
                QString report_mes=report_message.arg(jishu-1).arg(time_total_black+time_total_white).arg(time_total_black).arg(time_total_white);
                this->ui->report->setPlainText(report_mes);
                this->ui->report->setAlignment(Qt::AlignCenter);
                this->ui->report->show();
                restat();
            }
        }
        if(ispvp){
            if(m_bIsBlackTun==1)
                m_bIsBlackTun=2;
            else if(m_bIsBlackTun==2)
                m_bIsBlackTun=1;
        }else{

        }
        isplayerturn=1-isplayerturn;
        //qDebug()<<"dwa";
        emit turnNextPlayer(nextPlayer);
    }else {//用来写网络链接后
        net_pressed=true;
        QPoint pt;
        m_bIsBlackTun=net->real_color;
        if(net->your_turn==true){
            if(!USE_AI){
                int chess_x=event->pos().x()+WIDTH/2;//获取鼠标点击的x坐标
                int chess_y=event->pos().y()+HEIGHT/2;//y坐标
                pt.setX(chess_x/WIDTH);//设置x坐标
                pt.setY(chess_y/HEIGHT);//y坐标
                if(pt.x()>=ROW+1||pt.y()>=COLLON+1||pt.x()<1||pt.y()<1) {
                    return;
                }
            }else {
                emit turnNextPlayer(nextPlayer);
            }
        }
        qDebug()<<USE_AI;
        //循环所有棋子判断落子出是否存在棋子

        if(pt.x()<=0||pt.y()<=0||pt.x()>=9||pt.y()>=9){
            return;
        }
        QString move_x=QString::number(pt.x());
        QString move_y=QChar(pt.y()+'A'-1);
        QString move_op=move_y+move_x;
        timestamp=QDateTime::currentMSecsSinceEpoch();
        QString times_op=QString::number(timestamp);
        //qDebug()<<timestamp;
        QDateTime current;
        QString timerw = current.currentDateTime().toString("MMM dd hh:mm::ss");
        QString info;

        //            QFile ai_file("AI_save1.txt");
        //            if (!ai_file.open(QIODevice::Append | QIODevice::Text)) {
        //                //qDebug() << "Failed to open file";
        //                return;
        //            }
        //            QTextStream ai_out(&ai_file);
        //            ai_out<<(m_bIsBlackTun==1?'b':'w')<<move_op<<Qt::endl;
        //            AI_step++;
        //            ai_file.close();
        if(net->color!=0){
            if(net->id==1) {
                //客户端发送move_op
                info = timerw + " " + "sender" + " " +"MOVE_OP "+move_op+ " "+times_op+"\n";
                QFile file("daily.txt");
                if (!file.open(QIODevice::Append | QIODevice::Text)) {
                    //qDebug() << "Failed to open file";
                }
                QTextStream out(&file);
                out<<info;
                net->socket->send(NetworkData(OPCODE::MOVE_OP,move_op,times_op));
                received_move_op=0;
                time->start();
                time_now=remaining_time;
            }else {
                //服务端发送move_op
                info = timerw + " " + "sender" + " " +"MOVE_OP "+move_op+ " "+times_op+"\n";
                QFile file("daily.txt");
                if (!file.open(QIODevice::Append | QIODevice::Text)) {
                    //qDebug() << "Failed to open file";
                }
                QTextStream out(&file);
                out<<info;
                net->server->send(net->lastOne,NetworkData(OPCODE::MOVE_OP,move_op,times_op));
                time->start();
                time_now=remaining_time;
            }
            net->have_send_move_op=true;
            net->received_move_op=false;
            items[jishu++]=node{m_bIsBlackTun,pt.x(),pt.y(),jishu};
            lastMove=QPoint(pt.x(),pt.y());
            Item item(pt,m_bIsBlackTun);
            int x=item.m_pt.x();
            int y=item.m_pt.y();
            net->items[x][y]=m_bIsBlackTun;
            m_items[x][y]=m_bIsBlackTun;
            net->color=0;
            //判断是否赢。。。。。
            //判定四种情况。。。。。
            net->your_turn=false;
            this->ui->quitButton->hide();
        }
    }
}


bool MainWindow::yougiveup() {//认输
    you_giveup=true;
    QImage pool;
    pool.load(":/new/prefix1/giveup.jpg");
    QPixmap pixmap = QPixmap::fromImage(pool);
    pixmap = pixmap.scaled(400, 400, Qt::KeepAspectRatio, Qt::SmoothTransformation);
    this->lb = new QLabel(this);
    lb->setGeometry(20, 20, 400, 400); // set QLabel size to the scaled size
    lb->setPixmap(pixmap);
    lb->show();
    lb->move(this->width()/2-pixmap.width()*0.7,-pixmap.height()*1.5);
    QPropertyAnimation * animation =new QPropertyAnimation(lb,"geometry");
    animation->setDuration(1000);
    animation->setStartValue(QRect(lb->x(),lb->y(),lb->width(),lb->height()));
    animation->setEndValue(QRect(lb->x(),lb->y()+pixmap.height()*2,lb->width(),lb->height()));allow_start=false;
    animation->setEasingCurve(QEasingCurve::OutBounce);
    animation->start();
    time->stop();
    if(!net->already_connected){
        if(m_items[lastMove.x()][lastMove.y()]==2||m_items[lastMove.x()][lastMove.y()]==0){
            QString report_message="黑方认输，白方玩家胜利\n 总步数：%1\n游戏总时长: %2\n黑方总思考时长: %3\n白方总思考时长: %4";
            QString report_mes=report_message.arg(jishu).arg(time_total_black+time_total_white).arg(time_total_black).arg(time_total_white);
            this->ui->report->setPlainText(report_mes);
            this->ui->report->setAlignment(Qt::AlignCenter);
            this->ui->report->show();
        }
        if(m_items[lastMove.x()][lastMove.y()]==1){
            QString report_message="黑方认输，白方玩家胜利\n 总步数：%1\n游戏总时长: %2\n黑方总思考时长: %3\n白方总思考时长: %4";
            QString report_mes=report_message.arg(jishu).arg(time_total_black+time_total_white).arg(time_total_black).arg(time_total_white);
            this->ui->report->setPlainText(report_mes);
            this->ui->report->setAlignment(Qt::AlignCenter);
            this->ui->report->show();
        }
    }else{
        QDateTime current;
        QString time = current.currentDateTime().toString("MMM dd hh:mm::ss");
        QString info;
        if(net->id==1) {
            info = time + " " + "sender" + " " +"GIVEUP_OP "+net->nameE+ " "+"GLHF"+"\n";
            QFile file("daily.txt");
            if (!file.open(QIODevice::Append | QIODevice::Text)) {
                //qDebug() << "Failed to open file";
            }
            QTextStream out(&file);
            out<<info;
            this->ui->report->setText("你选择认输");
            net->socket->send(NetworkData(OPCODE::GIVEUP_OP,net->nameE,"GLHF"));
        }else{
            info = time + " " + "sender" + " " +"GIVEUP_OP "+net->nameE+ " "+"GLHF"+"\n";
            QFile file("daily.txt");
            if (!file.open(QIODevice::Append | QIODevice::Text)) {
                //qDebug() << "Failed to open file";
            }
            QTextStream out(&file);
            out<<info;
            this->ui->report->setText("你选择认输");
            net->server->send(net->lastOne,NetworkData(OPCODE::GIVEUP_OP,net->nameE,"GLHF"));
        }
        net->you_give_up=true;
    }
    this->ui->restart->show();
    this->ui->setbutton->show();
    this->ui->quitButton->hide();
    restat();
    return true;
}
void MainWindow::on_time() {//倒计时

    if(!net->already_connected){
        if(ww->ui->numedit->text().toInt()!=0){
            remaining_time=ww->ui->numedit->text().toDouble();//将倒计时赋值给remaining_time
        }
        else {
            remaining_time=30;
        }
        if(pressed) {
            time_now=remaining_time;
            pressed=false;
        }
        time_now-=0.1;//
        if(m_bIsBlackTun==1) {
            time_total_black+=0.1;
        }else {
            time_total_white+=0.1;
        }
        if(time_now<0){
            out_of_timelimit=true;
            QImage pool;
            pool.load(":/new/prefix1/lost.jpg");
            QPixmap pixmap = QPixmap::fromImage(pool);
            pixmap = pixmap.scaled(400, 400, Qt::KeepAspectRatio, Qt::SmoothTransformation);
            this->lb = new QLabel(this);
            lb->setGeometry(20, 20, 400, 400); // set QLabel size to the scaled size
            lb->setPixmap(pixmap);
            lb->show();
            lb->move(this->width()/2-pixmap.width()*0.7,-pixmap.height()*1.5);
            QPropertyAnimation * animation =new QPropertyAnimation(lb,"geometry");
            animation->setDuration(1000);
            animation->setStartValue(QRect(lb->x(),lb->y(),lb->width(),lb->height()));
            animation->setEndValue(QRect(lb->x(),lb->y()+pixmap.height()*2,lb->width(),lb->height()));allow_start=false;
            animation->setEasingCurve(QEasingCurve::OutBounce);
            animation->start();
            allow_start=false;
            time->stop();
            if(m_items[lastMove.x()][lastMove.y()]==2||m_items[lastMove.x()][lastMove.y()]==0){
                QString report_message="黑方超时，白方玩家胜利\n 总步数：%1\n游戏总时长: %2\n黑方总思考时长: %3\n白方总思考时长: %4";
                QString report_mes=report_message.arg(jishu).arg(time_total_black+time_total_white).arg(time_total_black).arg(time_total_white);
                this->ui->report->setPlainText(report_mes);
                this->ui->report->setAlignment(Qt::AlignCenter);
                this->ui->report->show();
            }
            if(m_items[lastMove.x()][lastMove.y()]==1){
                QString report_message="白方超时，黑方玩家胜利\n 总步数：%1\n游戏总时长: %2\n黑方总思考时长: %3\n白方总思考时长: %4";
                QString report_mes=report_message.arg(jishu).arg(time_total_black+time_total_white).arg(time_total_black).arg(time_total_white);
                this->ui->report->setPlainText(report_mes);
                this->ui->report->setAlignment(Qt::AlignCenter);
                this->ui->report->show();
            }
            restat();
        }
        ui->lcdNumber->display(time_now);
    }else {
        QDateTime current;
        QString timerw = current.currentDateTime().toString("MMM dd hh:mm::ss");
        QString info;
        if(ww->ui->numedit->text().toInt()!=0){
            remaining_time=ww->ui->numedit->text().toDouble();//将倒计时赋值给remaining_time
        }
        else {
            remaining_time=30;
        }
        //        qDebug()<<net->have_send_move_op;
        //        qDebug()<<"this is time_now :"<<time_now;

        time_now-=0.1;//
        if(time_now<0){
            if(net->have_send_move_op==true) {
                if(net->id==1) {
                    net->have_send_time_out_op=true;

                    this->ui->report->setText("对方超时了，你赢了");
                    this->ui->report->show();
                    time->stop();
                    info = timerw + " " + "sender" + " " +"TIMEOUT_END_OP "+net->nameE+ " "+"b"+"\n";
                    QFile file("daily.txt");
                    if (!file.open(QIODevice::Append | QIODevice::Text)) {
                        //qDebug() << "Failed to open file";
                    }
                    QTextStream out(&file);
                    out<<info;
                    net->socket->send(NetworkData(OPCODE::TIMEOUT_END_OP,net->nameE,""));
                }else {
                    net->have_send_time_out_op=true;
                    this->ui->report->setText("对方超时了，你赢了");
                    this->ui->report->show();
                    time->stop();
                    info = timerw + " " + "sender" + " " +"TIMEOUT_END_OP "+net->nameE+ " "+"b"+"\n";
                    QFile file("daily.txt");
                    if (!file.open(QIODevice::Append | QIODevice::Text)) {
                        //qDebug() << "Failed to open file";
                    }
                    QTextStream out(&file);
                    net->server->send(net->lastOne,NetworkData(OPCODE::TIMEOUT_END_OP,net->nameE,""));
                }
            }
        }
        ui->lcdNumber->display(time_now);
    }
}
bool MainWindow::start() {//开始
    for (int i = 1; i <=9; i++)
    {
        for (int j = 0; j <=9; j++)
        {
            m_items[i][j] = 0;
            candown[i][j]=1;
            value[i][j] = qMin(qAbs(i-2),qAbs(i-6))*10+qMin(qAbs(j-2),qAbs(j-6))*10;
            if(i+j==0||i+j==8||i+j==16) value[i][j]++;
        }
    }
    if(ww->ui->numedit->text().toInt()!=0){
        remaining_time=ww->ui->numedit->text().toDouble();//将倒计时赋值给remaining_time
    }
    else {
        remaining_time=30;
    }
    this->ui->setbutton->hide();
    time_now=remaining_time;
    time->start();
    this->ui->startButton->hide();
    this->ui->reproduce->hide();
    allow_start=true;
    jishu=1;
    return true;
}
bool MainWindow::restarted() {//重开
    if(!net->already_connected){
        memset(m_items,0,sizeof(m_items));
        if(ww->ui->numedit->text().toInt()!=0){
            remaining_time=ww->ui->numedit->text().toDouble();//将倒计时赋值给remaining_time
        }
        else {
            remaining_time=30;
        }
        time_now=remaining_time;
        ui->lcdNumber->display(time_now);


        this->ui->quitButton->show();
        m_bIsBlackTun=1;
        allow_start=true;
        you_lose=false;
        you_giveup=false;
        out_of_timelimit=false;
        time->start();
        this->ui->reproduce->hide();
        this->ui->restart->hide();
        this->ui->report->hide();
        lb->hide();
        this->ui->setbutton->hide();
        this->ui->report->hide();
        jishu=1;
        reproduced=false;//不是重现的
        return true;
    }else {
        memset(net->items,0,sizeof(net->items));
        QDateTime current;
        QString time = current.currentDateTime().toString("MMM dd hh:mm::ss");
        QString info;
        if(net->id==1) {
            net->sendid=net->id;
            if(net->real_color==1){
                info = time + " " + "sender" + " " +"READY_OP "+net->nameE+ " "+"b"+"\n";
                QFile file("daily.txt");
                if (!file.open(QIODevice::Append | QIODevice::Text)) {
                    //qDebug() << "Failed to open file";
                }
                QTextStream out(&file);
                out<<info;
                net->socket->send(NetworkData(OPCODE::READY_OP,net->nameE,"b"));

            }
            else{
                if(net->real_color==1){
                    info = time + " " + "sender" + " " +"READY_OP "+net->nameE+ " "+"b"+"\n";
                    QFile file("daily.txt");
                    if (!file.open(QIODevice::Append | QIODevice::Text)) {
                        //qDebug() << "Failed to open file";
                    }
                    QTextStream out(&file);
                    out<<info;
                    net->socket->send(NetworkData(OPCODE::READY_OP,net->nameE,"w"));}
            }
        }else {
            net->sendid=net->id;
            if(net->real_color==1){
                info = time + " " + "sender" + " " +"READY_OP "+net->nameE+ " "+"b"+"\n";
                QFile file("daily.txt");
                if (!file.open(QIODevice::Append | QIODevice::Text)) {
                    //qDebug() << "Failed to open file";
                }
                QTextStream out(&file);
                out<<info;
                net->server->send(net->lastOne,NetworkData(OPCODE::READY_OP,net->nameE,"b"));
            }
            else{
                if(net->real_color==1){
                    info = time + " " + "sender" + " " +"READY_OP "+net->nameE+ " "+"b"+"\n";
                    QFile file("daily.txt");
                    if (!file.open(QIODevice::Append | QIODevice::Text)) {
                        //qDebug() << "Failed to open file";
                    }
                    QTextStream out(&file);
                    out<<info;
                    net->server->send(net->lastOne,NetworkData(OPCODE::READY_OP,net->nameE,"w"));}
            }
        }
        net->havesend_end_op=false;
        net->received_give_up_op=false;
        this->ui->reproduce->hide();
        this->ui->restart->hide();
        this->ui->report->hide();
        lb->hide();
        this->ui->setbutton->hide();
        this->ui->report->hide();
        time_now=remaining_time;
        ui->lcdNumber->display(time_now);

    }
}
void MainWindow::restat() {//重开的模块化
    steps_total=0;
    this->ui->restart->show();
    this->ui->reproduce->show();
    this->ui->setbutton->show();
}
bool MainWindow::save() {//存储程序
    QFile file("item.txt");
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        //qDebug() << "Failed to open file";
        return false;
    }

    QTextStream out(&file);
    for(int i=1;i<jishu;i++) {
        out<<items[i].p_x<<char(items[i].p_y+'A'-1)<<" ";
    }
    if(you_giveup) {
        out<<"G";
    }
    if(out_of_timelimit) {
        out<<"T";
    }
    file.close();
    QString currentPath = QDir::currentPath();
    //qDebug() << "Current working directory: " << currentPath;
    return true;
}
//现在我希望实现播放，暂停，上一步，下一步，到第几步的功能，那么我应该一次读入所有的，然后在复盘程序中进行操作
bool MainWindow::read_in() {//复盘程序
    reproduced=true;
    showall();
    this->lb->hide();
    this->ui->report->hide();
    QFile file("item.txt");
    if (!file.exists()) {
        //qDebug() << "File not found.";
        return false;
    }
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        //qDebug() << "Failed to open file";
        return false;
    }

    QTextStream in(&file);
    memset(m_items,0,sizeof(m_items));
    memset(m_steps,0,sizeof(m_steps));
    QString str;
    int num=1;
    while(!in.atEnd()) {
        in>>str;
        bool ok;
        //qDebug()<<str.right(1);
        int x,y;
        x=str.mid(0,str.length()-1).toInt(&ok);//横轴
        if(!ok) {
            //qDebug()<<"Invalid number: "<<str;
            break;
        }else {
            y=str.right(1).at(0).unicode()-'A'+1;//纵轴
            //qDebug()<<x<<y;
        }
        if(num%2==1)
            m_items[x][y]=1;
        else {
            m_items[x][y]=2;
        }
        m_steps[x][y]=num;
        saving.push_back(node{m_items[x][y],x,y,num});//这里使用了动态数组来存储、后续再优化前面的
        //qDebug()<<x<<y<<m_steps[x][y];
        num++;
    }
    memset(m_items,0,sizeof(m_items));
    file.close();
    return true;
}
bool MainWindow::net_set() {
    net->show();
    return true;
}
bool MainWindow::setting_show() {//显示设置界面
    ww->show();
    return true;
}

bool MainWindow::time_set() {//设置倒计时
    QString time_edit=ww->ui->numedit->text();
    remaining_time=time_edit.toDouble();
    ui->lcdNumber->display(time_now);
    return true;
}
void MainWindow::paintEvent(QPaintEvent*)
{
    DrawCHessBroad();
    DrawItems();
    update();
}

void MainWindow::hideall() {
    this->ui->ensure->hide();
    this->ui->showing->hide();
    this->ui->next->hide();
    this->ui->last->hide();
    this->ui->stop->hide();
    this->ui->stepedit->hide();
}
void MainWindow::showall() {
    this->ui->ensure->show();
    this->ui->showing->show();
    this->ui->next->show();
    this->ui->last->show();
    this->ui->stop->show();
    this->ui->stepedit->show();
}
void MainWindow::bofang(){
    if(saving[steps_total].steps==0) return;
    // 设置定时器超时时间为2秒
    timers->setInterval(2000);
    // 连接定时器的超时信号到槽函数
    connect(timers, &QTimer::timeout, this, [=]() {
        // 在定时器超时后执行的程序
        QPainter painter(this);
        int s=saving[steps_total].steps;//第几步
        int x=saving[steps_total].p_x;//位置
        int y=saving[steps_total].p_y;
        int c=saving[steps_total].colors;//颜色
        if(c == 1){
            painter.setPen(Qt::NoPen);
            painter.setBrush(QBrush(QColor(255, 192, 203)));
        }
        else if(c == 2){
            painter.setPen(Qt::NoPen);
            painter.setBrush(QBrush(QColor(220, 208, 255)));
        }
        m_items[x][y]=c;
        painter.setRenderHint(QPainter::Antialiasing);
        QPoint ptCenter(x*WIDTH, y*HEIGHT);
        //绘制棋子，棋子的半径为宽高的一半
        painter.drawEllipse(ptCenter, WIDTH * 45/100, HEIGHT * 45/100);
        painter.setBrush(QBrush(QColor(255, 255, 255)));
        painter.drawEllipse(ptCenter, WIDTH*25/100, HEIGHT*25/100);//棋子画上去了
        //painter.setPen(Qt::red);
        //QFont font=painter.font();
        //font.setPointSize(14);
        //painter.setFont(font);
        //QString stepStr=QString::number(s);
        //不显示第几步
        //if(m_steps[x][y]<10){
        //  QPoint ptText = ptCenter - QPoint(WIDTH * 10/100, -HEIGHT * 10/100);
        // painter.drawText(ptText, stepStr);
        //}else {
        //  QPoint ptText = ptCenter - QPoint(WIDTH * 15/100, -HEIGHT * 10/100);
        //  painter.drawText(ptText, stepStr);
        //}
        if(saving[steps_total+1].steps!=0)
            steps_total++;
    });
    timers->start();
}
void MainWindow::zanting(){
    timers->stop();
}
void MainWindow::next(){
    if(saving[steps_total].steps==0) return;
    QPainter painter(this);
    int s=saving[steps_total].steps;//第几步
    int x=saving[steps_total].p_x;//位置
    int y=saving[steps_total].p_y;
    int c=saving[steps_total].colors;//颜色
    if(c == 1){
        painter.setPen(Qt::NoPen);
        painter.setBrush(QBrush(QColor(255, 192, 203)));
    }
    else if(c == 2){
        painter.setPen(Qt::NoPen);
        painter.setBrush(QBrush(QColor(220, 208, 255)));
    }
    m_items[x][y]=c;
    painter.setRenderHint(QPainter::Antialiasing);
    QPoint ptCenter(x*WIDTH, y*HEIGHT);
    //绘制棋子，棋子的半径为宽高的一半
    painter.drawEllipse(ptCenter, WIDTH * 45/100, HEIGHT * 45/100);
    painter.setBrush(QBrush(QColor(255, 255, 255)));
    painter.drawEllipse(ptCenter, WIDTH*25/100, HEIGHT*25/100);//棋子画上去了
    //painter.setPen(Qt::red);
    //QFont font=painter.font();
    //font.setPointSize(14);
    //painter.setFont(font);
    //QString stepStr=QString::number(s);
    //不显示第几步
    //if(m_steps[x][y]<10){
    //  QPoint ptText = ptCenter - QPoint(WIDTH * 10/100, -HEIGHT * 10/100);
    // painter.drawText(ptText, stepStr);
    //}else {
    //  QPoint ptText = ptCenter - QPoint(WIDTH * 15/100, -HEIGHT * 10/100);
    //  painter.drawText(ptText, stepStr);
    //}
    steps_total++;
}
void MainWindow::last(){
    if(steps_total==0) return;
    steps_total--;
    m_items[saving[steps_total].p_x][saving[steps_total].p_y]=0;
}
void MainWindow::sure(){
    int t=this->ui->stepedit->text().toInt();
    if(steps_total<t) {
        for(int i=steps_total;i<=t;i++) {
            QPainter painter(this);
            int s=saving[i].steps;//第几步
            int x=saving[i].p_x;//位置
            int y=saving[i].p_y;
            int c=saving[i].colors;//颜色
            if(c == 1){
                painter.setPen(Qt::NoPen);
                painter.setBrush(QBrush(QColor(255, 192, 203)));
            }
            else if(c == 2){
                painter.setPen(Qt::NoPen);
                painter.setBrush(QBrush(QColor(220, 208, 255)));
            }
            m_items[x][y]=c;
            painter.setRenderHint(QPainter::Antialiasing);
            QPoint ptCenter(x*WIDTH, y*HEIGHT);
            //绘制棋子，棋子的半径为宽高的一半
            painter.drawEllipse(ptCenter, WIDTH * 45/100, HEIGHT * 45/100);
            painter.setBrush(QBrush(QColor(255, 255, 255)));
            painter.drawEllipse(ptCenter, WIDTH*25/100, HEIGHT*25/100);//棋子画上去了
        }
    }else {
        for(int i=steps_total;i>=t;i--) {
            int x=saving[i].p_x;//位置
            int y=saving[i].p_y;
            m_items[x][y]=0;
        }
    }
    steps_total=t;
}
int MainWindow::getLiberty(int color)
{
    int score=0;
    for(int i=1;i<=9;i++)
    {
        for(int j=1;j<=9;j++)
        {
            if(m_items[i][j]==0)
            {
                score+=hasNeighborPiece(i,j,color);
            }
        }
    }
    return score;
}
bool MainWindow::hasNeighborPiece(int x, int y,int color) const
{
    // 检查指定位置的上下左右四个方向是否有棋子
    if (x > 1 && m_items[x - 1][y] == m_bIsBlackTun)
        return true;
    if (x < 9 && m_items[x + 1][y] == m_bIsBlackTun)
        return true;
    if (y > 1 && m_items[x][y - 1] == m_bIsBlackTun)
        return true;
    if (y <9 && m_items[x][y + 1] == m_bIsBlackTun)
        return true;

    return false;
}
int MainWindow::getScore(int color)
{
    int score=8000;
    for(int i=1;i<=9;i++)
    {
        for(int j=1;j<=9;j++)
        {
            if(m_items[i][j]==AIColor) score+=value[i][j];
            if(m_items[i][j]==3-m_bIsBlackTun) score-=value[i][j];
            if(!m_items[i][j])
            {
                if(canDown(i,j,color)) {score+=1000;}
                if(canDown(i,j,3-color)) {score-=1000;}
            }
        }
    }
    score-=getLiberty(color)*100;
    score+=getLiberty(3-color)*100;
    return score;
}
bool MainWindow::canDown(int x,int y,int color)
{
    int flag=0;
    if(m_items[x][y]!=0) return false;
    m_items[x][y]=color;
    zz=false,rr=false;
    memset(visit,0,sizeof(visit));
    check(x,y);
    memset(visit,0,sizeof(visit));
    check2(x,y);
    if(!zz||!rr) flag=1;
    m_items[x][y]=0;
    if(flag) return false;
    return true;
}
void MainWindow::setScores()
{
    for(int i=1;i<=9;i++)
    {
        for(int j=1;j<=9;j++)
        {
            if(canDown(i,j,AIColor))
            {
                m_items[i][j]=AIColor;
                scores[i][j]=getScore(AIColor);
                //if(i==4&&j==4) qDebug()<<scores[i][j]<<" 1 ";
                m_items[i][j]=0;
                if(canDown(i,j,3-AIColor))
                {
                    scores[i][j]-=getScore(3-AIColor);
                    m_items[i][j]=3-AIColor;
                    scores[i][j]+=getScore(3-AIColor);
                }
                else scores[i][j]-=3000;
                m_items[i][j]=0;
                //if(i==4&&j==4) qDebug()<<scores[i][j]<<" ";
            }
            else
            {
                candown[i][j]=0;
                scores[i][j]=-999999;
            }
        }
    }
}
void MainWindow::onSwitchModeButtonClicked()
{
    if(!net->already_connected){
        if (USE_AI == 0)
        {
            // 切换到人机对战模式
            USE_AI = 1;
            AIColor=(m_bIsBlackTun == 2) ? 2 : 1;
            m_bIsBlackTun=(AIColor == 1) ? 2 : 1;
            ispve=true;
            ispvp=false;
            // qDebug()<<PVPColor<<"\n";
            //qDebug()<<AIColor;
            startAIPlayer(); // 启动AI玩家的决策
        }
        else
        {
            ispvp=true;
            ispve=false;
            // 切换回人人对战模式
            qDebug()<<"weq";
            USE_AI = 0;
            stopAIPlayer(); // 停止AI玩家的决策
        }
    }else{
        if(USE_AI==0){
            USE_AI = 1;
            AIColor=net->real_color;
            startAIPlayer();
        }else{
            USE_AI = 0;
            stopAIPlayer();
        }
    }
}
void MainWindow::startAIPlayer()
{
    // 创建AI玩家对象（GomokuAi），并连接相应信号和槽
    ai = new MonteCarloSearch(this);
    connect(ai, &MonteCarloSearch::aiMove, this, &MainWindow::makeAiMove);
    isplayerturn=1;
    emit turnNextPlayer(nextPlayer);
}
void MainWindow::stopAIPlayer()
{
    //newGame();
    // 断开信号和槽连接，并释放AI玩家对象
    disconnect(ai, &MonteCarloSearch::aiMove, this, &MainWindow::makeAiMove); // 这里断开连接BoardWidget类的makeMove槽
    delete ai;
    ai = nullptr;
}
void MainWindow::makeAiMove()
{
    // AI玩家进行落子
    if(!net->already_connected){
        if (ai&&isplayerturn==1)
        {
            QPoint pos = ai->findBestMove();
            aiDropPiece(pos.x(), pos.y());
            if(flag2==0)
            {
                isplayerturn=0;
            }
            else
            {
                emit turnNextPlayer(nextPlayer);
            }
        }}else{
        if (ai&&net->your_turn==1)
        {
            QPoint pos = ai->findBestMove();
            aiDropPiece(pos.x(), pos.y());
            if(flag2==0)
            {
                isplayerturn=0;
            }
            else
            {
                emit turnNextPlayer(nextPlayer);
            }
        }
    }
}
void MainWindow::setScores(int x,int y) {
    int dx[4]={0,0,1,-1};
    int dy[4]={1,-1,0,0};
    for(int i=0;i<=3;i++) {
        if(canDown(x+dx[i],y+dy[i],AIColor))
        {
            m_items[x+dx[i]][y+dy[i]]=AIColor;
            scores[x+dx[i]][y+dy[i]]=getScore(AIColor);
            //if(i==4&&j==4) qDebug()<<scores[i][j]<<" 1 ";
            m_items[x+dx[i]][y+dy[i]]=0;
            if(canDown(x+dx[i],y+dy[i],3-AIColor))
            {
                scores[x+dx[i]][y+dy[i]]-=getScore(3-AIColor);
                m_items[x+dx[i]][y+dy[i]]=3-AIColor;
                scores[x+dx[i]][y+dy[i]]+=getScore(3-AIColor);
            }
            else scores[x+dx[i]][y+dy[i]]-=3000;
            m_items[x+dx[i]][y+dy[i]]=0;
            //if(i==4&&j==4) qDebug()<<scores[i][j]<<" ";
        }
        else
        {
            candown[x+dx[i]][y+dy[i]]=0;
            scores[x+dx[i]][y+dy[i]]=-999999;
        }
    }
}
void MainWindow::aiDropPiece(int x, int y)
{
    m_items[x][y]=AIColor;
    if(net->already_connected){
        net->items[x][y]=AIColor;
        QPoint pt(x,y);
        QString move_x=QString::number(pt.x());
        QString move_y=QChar(pt.y()+'A'-1);
        QString move_op=move_y+move_x;
        timestamp=QDateTime::currentMSecsSinceEpoch();
        QString times_op=QString::number(timestamp);
        //qDebug()<<timestamp;
        QDateTime current;
        QString timerw = current.currentDateTime().toString("MMM dd hh:mm::ss");
        QString info;
        if(net->id==1) {
            //客户端发送move_op
            info = timerw + " " + "sender" + " " +"MOVE_OP "+move_op+ " "+times_op+"\n";
            QFile file("daily.txt");
            if (!file.open(QIODevice::Append | QIODevice::Text)) {
                //qDebug() << "Failed to open file";
            }
            QTextStream out(&file);
            out<<info;
            net->socket->send(NetworkData(OPCODE::MOVE_OP,move_op,times_op));
            received_move_op=0;
            time->start();
            time_now=remaining_time;
        }else {
            //服务端发送move_op
            info = timerw + " " + "sender" + " " +"MOVE_OP "+move_op+ " "+times_op+"\n";
            QFile file("daily.txt");
            if (!file.open(QIODevice::Append | QIODevice::Text)) {
                //qDebug() << "Failed to open file";
            }
            QTextStream out(&file);
            out<<info;
            net->server->send(net->lastOne,NetworkData(OPCODE::MOVE_OP,move_op,times_op));
            time->start();
            time_now=remaining_time;
        }
        net->have_send_move_op=true;
        net->received_move_op=false;
        items[jishu++]=node{m_bIsBlackTun,pt.x(),pt.y(),jishu};
        lastMove=QPoint(pt.x(),pt.y());
        Item item(pt,m_bIsBlackTun);
        m_items[pt.x()][pt.y()]=net->real_color;
        net->your_turn=false;
        this->ui->quitButton->hide();
    }
}
