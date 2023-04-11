#include "mainwindow.h"
#include "ui_mainwindow.h"
#include"mainwindow_01.h"
#include<QPainter>
#include<QMouseEvent>
#include<QMessageBox>
#include<QPoint>
#include<QtCore/qmath.h>
#include<QLabel>
#define LIMIT_WIDTH 700
#define LIMIT_HEIGHT 700
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
//#define ROW 13
//#define COLLON 13
//#define WIDTH 50
//#define HEIGHT 50

int WIDTH=0;
int HEIGHT=0;
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{

    HEIGHT=LIMIT_WIDTH/COLLON;
    WIDTH=LIMIT_HEIGHT/ROW;
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
    connect(time,&QTimer::timeout,this,&MainWindow::on_time);//开始倒计时
    connect(this->ui->quitButton,&QPushButton::clicked,this,&MainWindow::yougiveup);//认输按钮
    connect(this->ui->startButton,&QPushButton::clicked,this,&MainWindow::start);//开始按钮
    connect(this->ui->restart,&QPushButton::clicked,this,&MainWindow::restarted);//重开
    connect(this->ui->savebutton,&QPushButton::clicked,this,&MainWindow::save);//保存
    connect(this->ui->reproduce,&QPushButton::clicked,this,&MainWindow::read_in);//读入
    QStatusBar *statusBar = new QStatusBar(this);
        setStatusBar(statusBar);
    QSoundEffect * BGM=new QSoundEffect;
        BGM->setSource(QUrl::fromLocalFile(":/bgm/Genshin Impact Main Theme .wav"));
    BGM->setLoopCount(QSoundEffect::Infinite);
    BGM->setVolume(0.25f);
    BGM->play();
}

MainWindow::~MainWindow()//终止
{
    delete ui;
}
//画棋盘
void MainWindow::DrawCHessBroad()//画个棋盘
{


    QPainter painter(this);
    for(int i=1;i<jishu;i++) {
        m_steps[items[i].p_x][items[i].p_y]=items[i].steps;
    }
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
    QPainter painter(this);
    QImage pic;

    for(int i=0; i<19; i++)
    {
        for(int j=0; j<19; j++)
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
            //MainWindow::play_wav(1);
            //QPixmap leishen =QPixmap::fromImage(pic);//图片
            //qreal radius=WIDTH*45/100;//是极半径
            //QPainterPath path;
            //path.addEllipse(ptCenter,radius,radius);
            //painter.setClipPath(path);
            //leishen=leishen.scaled(radius*2.65,radius*2.65,Qt::KeepAspectRatio,Qt::SmoothTransformation);
            //painter.setClipPath(path);
            //painter.drawPixmap(i*WIDTH-radius,j*HEIGHT-radius,leishen);
            QPoint pt(i,j);
            if(!reproduced&&pt==lastMove) {
                painter.setBrush(Qt::red);
                painter.drawEllipse(ptCenter,WIDTH*25/100,HEIGHT*25/100);//标记上一个落子
            }
            if(reproduced){//重现的代码
                if(m_steps[i][j]>0) {
                    painter.setPen(Qt::red);
                    QFont font=painter.font();
                    font.setPointSize(14);
                    painter.setFont(font);
                    QString stepStr=QString::number(m_steps[i][j]);
                    //显示第几步
                    if(m_steps[i][j]<10){
                        QPoint ptText = ptCenter - QPoint(WIDTH * 10/100, -HEIGHT * 10/100);
                        painter.drawText(ptText, stepStr);
                    }else {
                        QPoint ptText = ptCenter - QPoint(WIDTH * 15/100, -HEIGHT * 10/100);
                        painter.drawText(ptText, stepStr);
                    }
                }
            }
//            painter.setBrush(Qt::NoBrush);
//            painter.setPen(Qt::NoPen);
//            painter.drawEllipse(innerRect);


        }
    }

}
//判断函数（finished)
void MainWindow::check(int x,int y) {//不能下死手

    int dx[4]={1,-1,0,0};
    int dy[4]={0,0,1,-1};//四个方向
    visit[x][y]=true;
    for(int i=0;i<=3;i++) {
        if(x+dx[i]>0&&x+dx[i]<ROW+1&&y+dy[i]>0&&y+dy[i]<COLLON+1){

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
        if(x+dx[i]>0&&x+dx[i]<ROW+1&&y+dy[i]>0&&y+dy[i]<COLLON+1)
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
    if(!allow_start||you_lose||you_giveup||out_of_timelimit) return;
    pressed=true;
    QPoint pt;
    int chess_x=event->pos().x()+WIDTH/2;//获取鼠标点击的x坐标
    int chess_y=event->pos().y()+HEIGHT/2;//y坐标
    pt.setX(chess_x/WIDTH);//设置x坐标
    pt.setY(chess_y/HEIGHT);//y坐标
    if(pt.x()>=ROW+1||pt.y()>=COLLON+1||pt.x()<1||pt.y()<1) {
        return;
    }
    //循环所有棋子判断落子出是否存在棋子
    if(m_items[pt.x()][pt.y()]!=0) return;
    items[jishu]=node{m_bIsBlackTun,pt.x(),pt.y(),jishu};
    lastMove=QPoint(pt.x(),pt.y());
    jishu++;
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
        if(m_items[x][y]==1){
        this->ui->report->setPlainText("白方玩家胜利\n");
        this->ui->report->setAlignment(Qt::AlignCenter);
        }else {
        this->ui->report->setPlainText("黑方玩家胜利\n");
        this->ui->report->setAlignment(Qt::AlignCenter);
        }
        this->ui->report->show();
        restat();
    }
    if(m_bIsBlackTun==1)
    m_bIsBlackTun=2;
    else if(m_bIsBlackTun==2)
    m_bIsBlackTun=1;
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
    if(m_items[lastMove.x()][lastMove.y()]==2||m_items[lastMove.x()][lastMove.y()]==0){
    this->ui->report->setPlainText("黑方认输，白方玩家胜利\n");
    this->ui->report->setAlignment(Qt::AlignCenter);
    this->ui->report->show();
    }
    if(m_items[lastMove.x()][lastMove.y()]==1){
    this->ui->report->setPlainText("白方认输，黑方玩家胜利\n");
    this->ui->report->setAlignment(Qt::AlignCenter);
    this->ui->report->show();
    }
    this->ui->quitButton->hide();
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
        this->ui->report->setPlainText("黑方超时，白方玩家胜利\n");
        this->ui->report->setAlignment(Qt::AlignCenter);
        this->ui->report->show();
        }
        if(m_items[lastMove.x()][lastMove.y()]==1){
        this->ui->report->setPlainText("白方超时，黑方玩家胜利\n");
        this->ui->report->setAlignment(Qt::AlignCenter);
        this->ui->report->show();
        }
        restat();
    }
    ui->lcdNumber->display(remaining_time);
}
bool MainWindow::start() {//开始
    time->start();
    this->ui->startButton->hide();
    this->ui->reproduce->hide();
    allow_start=true;
    jishu=1;
    return true;
}
bool MainWindow::restarted() {//重开
    memset(m_items,0,sizeof(m_items));
    remaining_time=30;
    ui->lcdNumber->display(remaining_time);
    lb->hide();
    this->ui->quitButton->show();
    this->ui->reproduce->hide();
    this->ui->restart->hide();
    this->ui->report->hide();
    m_bIsBlackTun=1;
    allow_start=true;
    you_lose=false;
    you_giveup=false;
    out_of_timelimit=false;
    time->start();
    jishu=1;
    reproduced=false;//不是重现的
    return true;
}
void MainWindow::restat() {
    this->ui->restart->show();
    this->ui->reproduce->show();
}


bool MainWindow::save() {//存储程序
    QFile file("items.txt");
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        qDebug() << "Failed to open file";
        return false;
    }

    QTextStream out(&file);
    for (int i = 0; i <= ROW; ++i) {
        for (int j = 0; j <= COLLON; ++j) {
        out << m_items[i][j] << " ";
        }
        out << "\n";
    }
    file.close();
    QString currentPath = QDir::currentPath();
    qDebug() << "Current working directory: " << currentPath;
    return true;
}

bool MainWindow::read_in() {//复盘程序
    reproduced=true;
    this->lb->hide();
    this->ui->report->hide();
    QFile file("items.txt");
    if (!file.exists()) {
        qDebug() << "File not found.";
        return false;
    }
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "Failed to open file";
        return false;
    }
    QTextStream in(&file);
    memset(m_items,0,sizeof(m_items));
    for (int i = 0; i <= ROW; ++i) {
        for (int j = 0; j <= COLLON; ++j) {
        if (in.status() != QTextStream::Ok) {
            qDebug() << "Failed to read value at row " << i << " column " << j;
            file.close();
            return false;
        }
        in >> m_items[i][j];
        }
    }
    file.close();
    return true;
}
void vs_ai() {

}

void MainWindow::paintEvent(QPaintEvent*)
{
    DrawCHessBroad();
    DrawItems();

    update();
}

