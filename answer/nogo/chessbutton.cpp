#include "chessbutton.h"



ChessButton ::ChessButton(QWidget *parent):
    QPushButton(parent)
{

}

void ChessButton ::mousePressEvent(QMouseEvent *e){
    QPushButton::mousePressEvent(e);
    emit clicked(x, y);
}

void ChessButton ::paintColor(int player, int opt) {
    if (opt) {
        player == 1 ? this->setStyleSheet("border:2px groove red;\nborder-radius:40px;\npadding:2px 4px;\nborder-style: outset;\nbackground-color : black;")
                    : this->setStyleSheet("border:2px groove red;\nborder-radius:40px;\npadding:2px 4px;\nborder-style: outset;\nbackground-color : white;");
    } else {
        player == 1 ? this->setStyleSheet("border:2px groove grey;\nborder-radius:40px;\npadding:2px 4px;\nborder-style: outset;\nbackground-color : black;")
                    : this->setStyleSheet("border:2px groove grey;\nborder-radius:40px;\npadding:2px 4px;\nborder-style: outset;\nbackground-color : white;");
    }
}

ChessButton::~ChessButton()
{

}
