#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include<QVector>
#include"item.h"
#include <QMainWindow>
#include<QMessageBox>
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
    void DrawItems();//绘制棋子
    int m_items[20][20];//记录我们的落子   ？
    int m_bIsBlackTun;//记录落子颜色
    int CountRoundItems(Item it,QPoint pt);
    void mousePressEvent(QMouseEvent *event);
    void paintEvent(QPaintEvent *event);
    bool check(int x,int y);


private:
    Ui::MainWindow *ui;
protected:
};
#endif // MAINWINDOW_H
