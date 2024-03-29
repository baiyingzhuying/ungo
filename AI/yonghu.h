#ifndef YONGHU_H
#define YONGHU_H

#include<qsettings.h>
#include<QMessageBox>
#define CONFIGPATH (QCoreA)
#include <QWidget>

extern QString White_player;
extern QString Black_player;
extern int havewhite;
extern int haveblack;

namespace Ui {
class YongHu;
}

class YongHu : public QWidget
{
    Q_OBJECT

public:
    explicit YongHu(QWidget *parent = nullptr);
    ~YongHu();

    int White_score,Black_score;
    void login_check_black();//黑方注册
    void login_check_white();//白方注册
    void zhuce_check();//注册表
//    QString White_player;
//    QString Black_player;
//    int havewhite;
//    int haveblack;
    friend class MainWindow_01;




private slots:

signals:
    void sendWhiteUser(QString &text);
    void sendBlackUser(QString &text);

private:
    Ui::YongHu *ui;

};

#endif // YONGHU_H
