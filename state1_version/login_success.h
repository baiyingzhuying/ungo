#ifndef LOGIN_SUCCESS_H
#define LOGIN_SUCCESS_H

#include <QWidget>

namespace Ui {
class login_success;
}

class login_success : public QWidget
{
    Q_OBJECT

public:
    explicit login_success(QWidget *parent = nullptr);
    ~login_success();

private:
    Ui::login_success *ui;
};

#endif // LOGIN_SUCCESS_H
