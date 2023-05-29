#ifndef AI_H
#define AI_H
#include<QPair>
#include <vector>
#include<QPoint>
#include <QObject>
struct Move {
    int row;
    int col;
};
class MainWindow;
class MonteCarloSearch :public QObject{
    Q_OBJECT
public:
    explicit MonteCarloSearch(MainWindow* boardWidget, QObject* parent = nullptr);
    QPoint findBestMove();
signals:
    void aiMove(int x, int y);

public slots:
    void makeMove();
private:
    MainWindow* t;
};

#endif // MONTECARLOSEARCH_H
