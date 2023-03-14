#ifndef CHESSBUTTON_H
#define CHESSBUTTON_H

#include <QPushButton>
#include <QWidget>

class ChessButton : public QPushButton
{
    Q_OBJECT
public:
    int x, y;
    explicit ChessButton(QWidget *parent = nullptr);
    ~ChessButton();
    void paintColor(int player, int opt);

protected:
    void mousePressEvent(QMouseEvent *e);


signals:
    void clicked(int x, int y);


private:

};

#endif // CHESSBUTTON_H
