#ifndef ASWHITE_H
#define ASWHITE_H

#include <QWidget>

namespace Ui {
class AsWhite;
}

class AsWhite : public QWidget
{
    Q_OBJECT

public:
    explicit AsWhite(QWidget *parent = nullptr);
    ~AsWhite();

private:
    Ui::AsWhite *ui;
};

#endif // ASWHITE_H
