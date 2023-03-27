#include "mainwindow.h"
#include"mainwindow_01.h"
#include"yonghu.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow_01 w;
    w.show();
    return a.exec();
}
