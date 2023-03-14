#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<QPainter>
#include<QMouseEvent>
#include<QMessageBox>
#include<QPoint>
#define ROWS 9
#define COLLON 9
#define WIDTH 90
#define HEIGHT 90
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    resize(1000,1000);
    move(100,100);
    m_bIsBlackTun=0;//初始化落子颜色
    m_items.clear();//清空落子
}

MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::DrawCHessBroad()
{
    QPainter painter(this);
    QPen pen;
    pen.setColor(Qt::black);
    pen.setWidth(2);
    QBrush brush(QColor(220,150,100));
    painter.setPen(pen);
    painter.setBrush(brush);
    for(int j=0;j<COLLON;j++){
        for(int i=0;i<ROWS;i++){
            painter.drawRect((i+0.5)*WIDTH,(j+0.5)*HEIGHT,WIDTH,HEIGHT);
        }
    }

}
//用于获取一个方向的棋子数量
//int MainWindow::CountRoundItems(Item it,QPoint pt){

//}

void MainWindow::DrawItems(){
    QPainter painter(this);
    QPen pen;
    QBrush brush;
    pen.setColor(Qt::transparent);
    painter.setPen(pen);
    for(int i=0;i<m_items.size();i++){
        Item item =m_items[i];
        if(item.m_bBlack){
            painter.setBrush(Qt::black);

        }
        else {
            painter.setBrush(Qt::white);

        }
        //获取棋子位置
        QPoint ptCenter((item.m_pt.x()+0.5)*WIDTH,(item.m_pt.y()+0.5)*HEIGHT);
        //绘制棋子，棋子的半径为宽高的一半
        painter.drawEllipse(ptCenter,WIDTH/2,HEIGHT/2);

    }


}

void MainWindow::mousePressEvent(QMouseEvent *event){
    QPoint pt;
    int chess_x=event->pos().x();//获取鼠标点击的x坐标
    int chess_y=event->pos().y();//y坐标
    pt.setX(chess_x/WIDTH);//设置x坐标
    pt.setY(chess_y/HEIGHT);//y坐标
    //循环所有棋子判断落子出是否存在棋子
    for(int i=0;i<m_items.size();i++){
        Item item =m_items[i];
        if(item.m_pt==pt){
            return ;
        }
    }
    Item item(pt,m_bIsBlackTun);
    m_items.append(item);
    //判断是否赢。。。。。
    //判定四种情况。。。。。
    m_bIsBlackTun=!m_bIsBlackTun;

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
