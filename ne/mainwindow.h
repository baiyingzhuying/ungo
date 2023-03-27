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
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:

    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void DrawCHessBroad();//绘制棋盘
    bool yougiveup();//放弃的函数
    bool you_giveup;//已经放弃
    bool you_lose;//输了
    bool out_of_timelimit;//超时
    bool zz=false,rr=false;//非法落子
    bool allow_start;//允许开始
    QLabel *lb;
    QImage pool;
    QLabel *label;
    bool restarted();
    void DrawItems();//绘制棋子
    int m_items[190][100];//记录我们的落子
    int m_bIsBlackTun;//记录落子颜色
    int CountRoundItems(Item it,QPoint pt);
    void mousePressEvent(QMouseEvent *event);
    void paintEvent(QPaintEvent *event);
    void check(int x,int y);//禁落点
    void check2(int x,int y);//提子
    void check3(int x,int y);//衍生品
    QTimer *time;
    bool pressed;
    bool visit[1001][1001];
    double remaining_time;
    bool start();
    void restat();
public slots:
    void on_time();
private:
    Ui::MainWindow *ui;

protected:
};
#endif // MAINWINDOW_H
