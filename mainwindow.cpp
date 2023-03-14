#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<QPainter>
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
}

MainWindow::~MainWindow()
{
    delete ui;
}
void DrawChessBroad()
{

}
void MainWindow::paintEvent(QPaintEvent*)
{
    DrawChessBroad();
QPainter painter(this);
QPen pen;//画笔
pen.setColor(QColor(0,0,0));//设置画笔颜色
pen.setWidth(4);
QBrush brush(QColor(255,235,205));//画刷
painter.setPen(pen);//添加画笔
painter.setBrush(brush);//添加画刷
for(int i=0;i<ROWS;i++)
{
    for(int j=0;j<COLLON;j++)
    {
        painter.drawRect((i+0.5)*WIDTH,(j+0.5)*HEIGHT,WIDTH,HEIGHT);
    }
}
}
