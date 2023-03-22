#ifndef YONGHU_H
#define YONGHU_H

#include <QWidget>

namespace Ui {
class YongHu;
}

class YongHu : public QWidget
{
    Q_OBJECT

public:
    explicit YongHu(QWidget *parent = nullptr);
    ~YongHu();

private slots:
    void on_pushButton_3_clicked();

private:
    Ui::YongHu *ui;
};

#endif // YONGHU_H
