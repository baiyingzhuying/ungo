#ifndef YONGHU_H
#define YONGHU_H

#include<qsettings.h>
#include<QMessageBox>
#define CONFIGPATH (QCoreA)
#include <QWidget>

extern QString White_player;//白方
extern QString Black_player;//黑方
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
    void login_check_black();
    void login_check_white();
    void zhuce_check();
//    QString White_player;
//    QString Black_player;
//    int havewhite;
//    int haveblack;
    friend class MainWindow_01;




private slots:

private:
    Ui::YongHu *ui;

};

#endif // YONGHU_H
