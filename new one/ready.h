#ifndef READY_H
#define READY_H

#include <QWidget>

namespace Ui {
class ready;
}

class ready : public QWidget
{
    Q_OBJECT

public:
    explicit ready(QWidget *parent = nullptr);
    ~ready();
    Ui::ready *ui;
};

#endif // READY_H
