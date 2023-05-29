#ifndef UNREADY_H
#define UNREADY_H

#include <QWidget>

namespace Ui {
class unready;
}

class unready : public QWidget
{
    Q_OBJECT

public:
    explicit unready(QWidget *parent = nullptr);
    ~unready();

private:
    Ui::unready *ui;
};

#endif // UNREADY_H
