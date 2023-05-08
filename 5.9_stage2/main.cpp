#include "mainwindow.h"
#include"mainwindow_01.h"
#include"yonghu.h"
#include <QApplication>
int ROW=9;
int COLLON=9;
MainWindow_01 * Cover=nullptr;
MainWindow * game=nullptr;
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow_01 w;
    Cover=&w;
    MainWindow d;
    game=&d;
    Cover->show();
    return a.exec();
}
