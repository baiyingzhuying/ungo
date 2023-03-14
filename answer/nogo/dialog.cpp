#include "dialog.h"
#include "ui_dialog.h"
#include <QDebug>
#include "chessbutton.h"
#include <QPushButton>
#include "board.h"
#include "gameplayer.h"
#include "noticewidget.h"
#include "dialogask.h"
#include <map>
#include <string>

#include <QByteArray>
#include <QFile>
#include <QFileInfo>

using namespace std;

void dialog ::paintpieces(int x, int y, int player, int opt)
{
    myButton[x][y]->paintColor(player, opt);
}

void dialog ::showNotice(QString str)
{
    NoticeWidget* w = new NoticeWidget(str);
    w->show();
}

void dialog ::disableButton()
{
    st.clear();
    for (int i = 0; i < 9; i++)
        for (int j = 0; j < 9; j++)
            disconnect(myButton[i][j], SIGNAL(clicked(int, int)), this, SLOT(check(int, int)));
}

int lstx = -1, lsty = -1;

void dialog ::memorize(int x, int y) {
    st.append((char)(x + '0'));
    st.append((char)(y + '0'));
}

void dialog ::check(int x, int y)
{
    if (now.checkmove(x + 1 , y + 1))
    {
        memorize(x + 1, y + 1);
        paintpieces(x, y, now.player, 0);
        now.move(make_pair(x + 1, y + 1));
        if (lstx != -1)
            paintpieces(lstx, lsty, now.player, 0);
        if (now.checkend())
            showNotice("恭喜，你赢了！"), disableButton();

        QCoreApplication ::processEvents();

        pair<int, int> res = player.play(make_pair(x + 1, y + 1));
        memorize(res.first, res.second);
        int rx = lstx = res.first - 1;
        int ry = lsty = res.second - 1;
        paintpieces(rx, ry, now.player, 1);
        now.move(res);
        if (now.checkend())
            showNotice("你输了，再接再厉！"), disableButton();
    }
    else
        showNotice("抱歉，这里不能落子");
}

void dialog ::do_first_step() {
    pair<int, int> res = player.play(make_pair(-1, -1));
    memorize(res.first, res.second);
    int rx = lstx = res.first - 1;
    int ry = lsty = res.second - 1;
    paintpieces(rx, ry, now.player, 1);
    now.move(res);
}

dialog::dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::dialog)
{
    ui->setupUi(this);
    st.clear();
    for (int i = 0; i < 9; i++)
        for (int j = 0; j < 9; j++)
        {
            myButton[i][j] = new ChessButton;
            myButton[i][j]->x = i;
            myButton[i][j]->y = j;
            myButton[i][j]->setParent(this);
            myButton[i][j]->resize(80, 80);
            myButton[i][j]->move(124 + i * 95 - 40, 168 + j * 99 - 40);
            myButton[i][j]->setFlat(true);
            connect(myButton[i][j], SIGNAL(clicked(int, int)), this, SLOT(check(int, int)));
        }
}



dialog::~dialog()
{
    delete ui;
}

void dialog ::reloadgame(QString str) {
    string s = str.toStdString();
    int sz = s.size();
    for (int i = 0; i < sz; i += 2) {
        int x = s[i] - '0';
        int y = s[i + 1] - '0';
        if (i + 1 != sz - 1)
        {
            memorize(x, y);
            paintpieces(x - 1, y - 1, now.player, 0);
        }
        else
        {
            memorize(x, y);
            paintpieces(x - 1, y - 1, now.player, 1);
            lstx = x - 1;
            lsty = y - 1;
        }
        now.move(make_pair(x, y));
        player.now.move(make_pair(x, y));
    }
}

void dialog ::loadboard()
{
    QString path("../nogo/board.txt");
    QFile file(path);
    bool openok = file.open(QIODevice ::WriteOnly);
    if (openok)
        file.write(st.toUtf8());
    file.close();
}

void dialog::on_pushButton_clicked()
{
    DialogAsk* w = new DialogAsk;
    w->show();
    connect(w, &DialogAsk ::acceptload, this, &dialog ::loadboard);
    connect(w, &DialogAsk ::acceptload, this, &dialog ::close);
    connect(w, &DialogAsk ::rejectload, this, &dialog ::close);
}

void dialog::on_pushButton_2_clicked()
{
    dialog ::loadboard();
    showNotice("已存盘");
}
