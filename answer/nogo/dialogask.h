#ifndef DIALOGASK_H
#define DIALOGASK_H

#include <QDialog>

namespace Ui {
class DialogAsk;
}

class DialogAsk : public QDialog
{
    Q_OBJECT

public:
    explicit DialogAsk(QWidget *parent = nullptr);
    ~DialogAsk();

signals :
    void acceptload();
    void rejectload();

private slots:
    void on_buttonBox_accepted();

    void on_buttonBox_rejected();

private:
    Ui::DialogAsk *ui;
};

#endif // DIALOGASK_H
