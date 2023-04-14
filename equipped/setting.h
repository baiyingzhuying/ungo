
#ifndef SETTING_H
#define SETTING_H
#include<QMainWindow>
#include<QIntValidator>
#include<Qwidget>
namespace Ui{
class setting;
}
class setting:public QWidget {
    Q_OBJECT

public:
    explicit setting(QWidget *parent = nullptr);
    ~setting();
    Ui::setting *ui;
};

#endif // SETTING_H
