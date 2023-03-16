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
    resize(1000,1000);//初始化大小
    move(100,100);
    m_bIsBlackTun=1;//初始化落子颜色
    memset(m_items,0,sizeof(m_items));
    //清空落子
    QStatusBar *statusBar = new QStatusBar(this);
        setStatusBar(statusBar);
}

MainWindow::~MainWindow()//终止
{
    delete ui;
}
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

void MainWindow::DrawItems() //画个棋子
{
    QPainter painter(this);
    QPen pen(Qt::black);  // 设置边框为黑色
    QBrush brush;
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
//判断函数（待finish）
bool MainWindow::check(int x,int y) {//不能下死手
    bool visit[19][19];
    memset(visit,0,sizeof(visit));
    int dx[4]={1,-1,0,0};
    int jishu=0;
    int dy[4]={0,0,1,-1};
    visit[x][y]=true;
    for(int i=0;i<=3;i++) {
        if(m_items[x+dx[i]][y+dy[i]]==0) {
            return true;
        }else if(m_items[x+dx[i]][y+dy[i]]!=m_items[x][y]) {
            continue;
        }else {
            if(!visit[x+dx[i]][y+dy[i]]){
                visit[x+dx[i]][y+dy[i]]=true;
                return check(x+dx[i],y+dy[i]);
            }else {
                continue;
            }
        }
    }
    return false;
}

void MainWindow::mousePressEvent(QMouseEvent *event){//落点位置，改好了，别动

    QPoint pt;
    int chess_x=event->pos().x()+WIDTH/2;//获取鼠标点击的x坐标
    int chess_y=event->pos().y()+HEIGHT/2;//y坐标
    pt.setX(chess_x/WIDTH);//设置x坐标
    pt.setY(chess_y/HEIGHT);//y坐标
    //循环所有棋子判断落子出是否存在棋子
    if(m_items[pt.x()][pt.y()]!=0) return;
    Item item(pt,m_bIsBlackTun);
    int x=item.m_pt.x();
    int y=item.m_pt.y();
    m_items[x][y]=m_bIsBlackTun;
    //判断是否赢。。。。。
    //判定四种情况。。。。。

    if(check(x,y)==false) {
        QMessageBox::information(this,"final","you can't do this",QMessageBox::Yes);
    }
    if(m_bIsBlackTun==1)
    m_bIsBlackTun=2;
    else if(m_bIsBlackTun==2)
    m_bIsBlackTun=1;

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
