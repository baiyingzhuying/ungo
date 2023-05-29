#ifndef MAINWINDOW_01_H
#define MAINWINDOW_01_H
#include <QMainWindow>
#include"netting.h"
#include"mainwindow.h"
namespace Ui {
class MainWindow_01;
}

class MainWindow_01 : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow_01(QWidget *parent = nullptr);
    ~MainWindow_01();
    bool net_setting_show();
    netting *nw=new netting;
    friend class YongHu;
private slots:
    void setWhiteUser(QString &text);
    void setBlackUser(QString &text);
private:
    Ui::MainWindow_01 *ui;
};
extern MainWindow_01 *Cover;
#endif // MAINWINDOW_01_H
