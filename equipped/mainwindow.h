#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include<QVector>
#include"item.h"
#include <QMainWindow>
#include<QMessageBox>
#include<QTime>
#include<QTimer>
#include<QHBoxLayout>
#include<QPushButton>
#include<QLineEdit>
#include<QLabel>
#include<QImage>
#include<QFile>
#include<QDir>
#include<QThread>
#include<windows.h>
#include"setting.h"
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE


extern int ROW;
extern int COLLON;
extern int WIDTH;
extern int HEIGHT;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:

    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    //判断胜负
    //==-------------------
    bool yougiveup();//放弃的函数
    bool you_giveup;//已经放弃
    bool you_lose;//输了
    bool out_of_timelimit;//超时
    bool zz=false,rr=false;//非法落子
    void check(int x,int y);//禁落点
    void check2(int x,int y);//提子
    void check3(int x,int y);//衍生品（用于check2())
    bool allow_start;//允许开始
    //---------------------
    QLabel *lb;
    QImage pool;
    QLabel *label;
    //用于显示图像的一些变量
    //---------------------
    void DrawCHessBroad();//绘制棋盘
    void DrawItems();//绘制棋子
    int m_items[190][100];//记录我们的落子
    int m_bIsBlackTun;//记录落子颜色
    int CountRoundItems(Item it,QPoint pt);
    void mousePressEvent(QMouseEvent *event);
    void paintEvent(QPaintEvent *event);
    //绘图
    //---------------------
    //底层
    QTimer *time;
    bool pressed;//落子
    bool visit[1001][1001];
    double time_now;
    double remaining_time;//剩余时间
    double time_total_white;
    double time_total_black;
    bool start();//开始
    void restat();//重开
    bool restarted();//重开
    QPoint lastMove;//上一步
    int jishu=0;//总步数
    struct node {
        int colors;
        int p_x;
        int p_y;
        int steps;
    }items[20*20];//位置，步数，颜色
    int times_for_place[20][20];
    bool save();//存储
    bool read_in();//读入
    int m_steps[20][20];//记录步数
    bool reproduced;//重现
    int count_black,count_while;
    bool IsVolume;
    bool setting_show();

    bool time_set();
    setting *ww=new setting;

public slots:
    void on_time();
private:
    Ui::MainWindow *ui;

protected:
};
#endif // MAINWINDOW_H
