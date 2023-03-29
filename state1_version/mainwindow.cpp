#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<QPainter>
#include<QMouseEvent>
#include<QMessageBox>
#include<QPoint>
#include<QtCore/qmath.h>
#include<QLabel>
#define ROWS 13
#define COLLON 13
#define WIDTH 30
#define HEIGHT 30
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    resize(600,600);//初始化大小
    move(100,100);
    QFont font("Arial",16);
    ui->CountDown->setFont(font);
    ui->CountDown->setReadOnly(true);
    ui->CountDown->appendPlainText(QString("倒计时"));
    m_bIsBlackTun=1;//初始化落子颜色
    memset(m_items,0,sizeof(m_items));
    //清空落子
    time=new QTimer(this);
    time->stop();
    time->setInterval(100);
    this->ui->restart->hide();
    connect(time,&QTimer::timeout,this,&MainWindow::on_time);//开始倒计时
    connect(this->ui->quitButton,&QPushButton::clicked,this,&MainWindow::yougiveup);
    connect(this->ui->startButton,&QPushButton::clicked,this,&MainWindow::start);
    connect(this->ui->restart,&QPushButton::clicked,this,&MainWindow::restarted);
    QStatusBar *statusBar = new QStatusBar(this);
        setStatusBar(statusBar);
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
    QBrush brush(QColor(255, 235, 205)); // 定义浅黄色画刷
    painter.setPen(pen);
    painter.setBrush(brush);

    // 绘制棋盘边框
    painter.drawRect(WIDTH/2, HEIGHT/2, (ROWS+1)*WIDTH, (1+COLLON)*HEIGHT);

    // 绘制棋盘格子
    for(int i = 0; i < ROWS; i++)
    {
        for(int j = 0; j < COLLON; j++)
        {
            painter.drawRect((i+1)*WIDTH, (j+1)*HEIGHT, WIDTH, HEIGHT);
        }
    }

}
//用于获取一个方向的棋子数量
//int MainWindow::CountRoundItems(Item it,QPoint pt){

//}
//画棋子
void MainWindow::DrawItems() //画个棋子
{
    QPainter painter(this);
    for(int i=0; i<19; i++)
    {
        for(int j=0; j<19; j++)
        {
            int q = m_items[i][j];
            if(q == 1){
                painter.setPen(Qt::black);
                painter.setBrush(Qt::black);
            }
            else if(q == 2){
                painter.setPen(Qt::white);
                painter.setBrush(Qt::white);
            }
            else{
                continue;
            }
            //获取棋子位置
            QPoint ptCenter(i*WIDTH, j*HEIGHT);
            //绘制棋子，棋子的半径为宽高的一半
            painter.drawEllipse(ptCenter, WIDTH * 45/100, HEIGHT * 45/100);
        }
    }
}
//判断函数（finished)
void MainWindow::check(int x,int y) {//不能下死手

    int dx[4]={1,-1,0,0};
    int dy[4]={0,0,1,-1};//四个方向
    visit[x][y]=true;
    for(int i=0;i<=3;i++) {
        if(x+dx[i]>0&&x+dx[i]<=ROWS+1&&y+dy[i]>0&&y+dy[i]<=COLLON+1){

        if(m_items[x+dx[i]][y+dy[i]]==0) {
            zz= true;//周围有空
            return;
        }else if(m_items[x+dx[i]][y+dy[i]]!=m_items[x][y]) {
            continue;
        }else {
            if(!visit[x+dx[i]][y+dy[i]]){
                visit[x+dx[i]][y+dy[i]]=true;
                check(x+dx[i],y+dy[i]);
            }else {
                continue;
            }
        }
    }//禁落点的判断
}
    return;
}
void MainWindow::check3(int x,int y) {
    int dx[4]={1,-1,0,0};
    int dy[4]={0,0,1,-1};//四个方向
    visit[x][y]=true;
    for(int i=0;i<=3;i++) {
        if(x+dx[i]>0&&x+dx[i]<=ROWS+1&&y+dy[i]>0&&y+dy[i]<=COLLON+1)
        if(m_items[x+dx[i]][y+dy[i]]==0) {
            rr= true;//周围有空
            return;
        }else if(m_items[x+dx[i]][y+dy[i]]!=m_items[x][y]) {
            continue;
        }else {
            if(!visit[x+dx[i]][y+dy[i]]){
                visit[x+dx[i]][y+dy[i]]=true;
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
        if(x+dx[i]>0&&x+dx[i]<=ROWS+1&&y+dy[i]>0&&y+dy[i]<=COLLON+1){
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
    if(jishu3==3&&((x==1&&y!=COLLON+1&&y!=1)||(y!=1&&y!=COLLON+1&&x==ROWS+1)||(y==1&&x!=COLLON+1&&x!=1)||(x!=1&&x!=COLLON+1&&y==ROWS+1))){
        rr=true;
    return;
    }
    if(jishu3==2&&(x==1&&y==COLLON+1)||(x==1&&y==1)||(x==1&&y==ROWS+1)||(x==COLLON+1&&y==COLLON+1)){
        rr=true;
        return;
    }
}
//落子程序
void MainWindow::mousePressEvent(QMouseEvent *event){//落点位置，改好了，别动
    if(!allow_start||you_lose||you_giveup||out_of_timelimit) return;
    pressed=true;
    QPoint pt;
    int chess_x=event->pos().x()+WIDTH/2;//获取鼠标点击的x坐标
    int chess_y=event->pos().y()+HEIGHT/2;//y坐标
    pt.setX(chess_x/WIDTH);//设置x坐标
    pt.setY(chess_y/HEIGHT);//y坐标
    if(pt.x()>=15||pt.y()>=15||pt.x()<1||pt.y()<1) {
        return;
    }
    //循环所有棋子判断落子出是否存在棋子
    if(m_items[pt.x()][pt.y()]!=0) return;
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
        you_lose=true;
        QImage pool;
        pool.load(":/new/prefix1/lost.jpg");
        QPixmap pixmap = QPixmap::fromImage(pool);
        pixmap = pixmap.scaled(400, 400, Qt::KeepAspectRatio, Qt::SmoothTransformation);
        this->lb = new QLabel(this);
        lb->setGeometry(20, 20, 400, 400); // set QLabel size to the scaled size
        lb->setPixmap(pixmap);
        lb->show();
        time->stop();
        allow_start=false;
        restat();
    }
    if(m_bIsBlackTun==1)
    m_bIsBlackTun=2;
    else if(m_bIsBlackTun==2)
    m_bIsBlackTun=1;
}

bool MainWindow::yougiveup() {
    you_giveup=true;
    QImage pool;
    pool.load(":/new/prefix1/giveup.jpg");
    QPixmap pixmap = QPixmap::fromImage(pool);
    pixmap = pixmap.scaled(400, 400, Qt::KeepAspectRatio, Qt::SmoothTransformation);
    this->lb = new QLabel(this);
    lb->setGeometry(20, 20, 400, 400); // set QLabel size to the scaled size
    lb->setPixmap(pixmap);
    lb->show();
    allow_start=false;
    time->stop();
    restat();
    return true;
}

void MainWindow::on_time() {//倒计时
    remaining_time=ui->lcdNumber->value();//将倒计时赋值给remaining_time

    if(pressed) {
        remaining_time=30;
        pressed=false;
    }
    remaining_time-=0.1;//
    if(remaining_time<0){
        out_of_timelimit=true;
        QImage pool;
        pool.load(":/new/prefix1/lost.jpg");
        QPixmap pixmap = QPixmap::fromImage(pool);
        pixmap = pixmap.scaled(400, 400, Qt::KeepAspectRatio, Qt::SmoothTransformation);
        this->lb = new QLabel(this);
        lb->setGeometry(20, 20, 400, 400); // set QLabel size to the scaled size
        lb->setPixmap(pixmap);
        lb->show();
        allow_start=false;
        time->stop();
        restat();
    }
    ui->lcdNumber->display(remaining_time);
}
bool MainWindow::start() {//开始
    time->start();
    allow_start=true;
    return true;
}
bool MainWindow::restarted() {
    memset(m_items,0,sizeof(m_items));
    remaining_time=30;
    ui->lcdNumber->display(remaining_time);
    lb->hide();
    this->ui->restart->hide();
    m_bIsBlackTun=1;
    allow_start=true;
    you_lose=false;
    you_giveup=false;
    out_of_timelimit=false;
    time->start();
    return true;
}
void MainWindow::restat() {
    this->ui->restart->show();
}
void MainWindow::paintEvent(QPaintEvent*)
{
    DrawCHessBroad();

    DrawItems();
//    QPainter painter(this);
//    QPen pen;//画笔
//    pen.setColor(QColor(0,0,0));//设置画笔颜色
//    pen.setWidth(4);
//    QBrush brush(QColor(255,235,205));//画刷
//    painter.setPen(pen);//添加画笔
//    painter.setBrush(brush);//添加画刷
//    for(int i=0;i<ROWS;i++)
//    {
//        for(int j=0;j<COLLON;j++)
//        {
//            painter.drawRect((i+0.5)*WIDTH,(j+0.5)*HEIGHT,WIDTH,HEIGHT);
//        }
//    }
    update();
}

