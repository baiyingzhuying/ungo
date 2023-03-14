#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include "board.h"
#include "gameplayer.h"
#include "chessbutton.h"
#include <QString>

namespace Ui {
class dialog;
}

class dialog : public QDialog
{
    Q_OBJECT

public:
    Board now;
    Gameplayer player;
    ChessButton* myButton[9][9];
    QString st;
    explicit dialog(QWidget *parent = nullptr);
    ~dialog();
    void do_first_step();
    void reloadgame(QString str);

private slots:
    void check(int x, int y);
    void on_pushButton_clicked();
    void loadboard();

    void on_pushButton_2_clicked();

private:
    Ui::dialog *ui;
    void paintpieces(int x, int y, int player, int opt);
    void showNotice(QString str);
    void disableButton();
    void memorize(int x, int y);
};

#endif // DIALOG_H
