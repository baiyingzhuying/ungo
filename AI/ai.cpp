#include "ai.h"
#include<QPair>
#include<QMainWindow>
#include"mainwindow.h"
MonteCarloSearch::MonteCarloSearch(MainWindow* a, QObject* parent) : QObject(parent), t(a)
{
    // 将BoardWidget的turnNextPlayer信号与GomokuAi的makeMove槽连接
    connect(a, &MainWindow::turnNextPlayer, this, &MonteCarloSearch::makeMove);
}
void MonteCarloSearch::makeMove()
{
    qDebug()<<123;
        if(t->isplayerturn==1)
        {
        // 调用AI策略选择最佳落子位置
        QPoint bestMove = findBestMove();

        // 发送aiMove信号，传递最佳落子位置的坐标
        if(bestMove.x()==-1)
        {
            QMessageBox::warning(t, tr("警告"), tr("无处可下"));
            return;
        }
        qDebug()<<1234;
        emit aiMove(bestMove.x(), bestMove.y());
        }
}

QPoint MonteCarloSearch::findBestMove()
{
        int boardWidth = 9;
        int boardHeight = 9;

        // 优先选择与已有棋子相邻的空格子
        QVector<QPoint> Positions;
        t->setScores();
        int max=-999999;
        int flag=0;
        for (int x = 1; x <= boardWidth; x++)
        {
        for (int y = 1; y <= boardHeight; y++)
        {
            if(t->candown[x][y]==1)
            {
                flag=1;
                if(t->scores[x][y]>max) max=t->scores[x][y];
            }
        }
        }
        if(flag==0) return QPoint(-1, -1);
        for (int x = 1; x <= boardWidth; x++)
        {
        for (int y = 1; y <= boardHeight; y++)
        {
            if(t->candown[x][y]==1&&t->scores[x][y]==max) Positions.append(QPoint(x,y));
        }
        }
        if (!Positions.isEmpty())
        {
        srand(QTime::currentTime().msec());
        int randomIndex = rand() % Positions.size();
        return Positions[randomIndex];
        }

        return QPoint(-1, -1);
}
