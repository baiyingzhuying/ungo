#ifndef MAINWINDOW_01_H
#define MAINWINDOW_01_H
#include"yonghu.h"
#include <QMainWindow>

namespace Ui {
class MainWindow_01;
}

class MainWindow_01 : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow_01(QWidget *parent = nullptr);
    ~MainWindow_01();

private slots:

private:
    Ui::MainWindow_01 *ui;
};

#endif // MAINWINDOW_01_H
