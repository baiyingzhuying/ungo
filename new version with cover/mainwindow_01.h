#ifndef MAINWINDOW_01_H
#define MAINWINDOW_01_H

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
    void on_StartGame_clicked();

    void on_YongHu_clicked();

    void on_User_clicked();

    void on_Log_in_clicked();

    void on_pushButton_clicked();

private:
    Ui::MainWindow_01 *ui;
};

#endif // MAINWINDOW_01_H
