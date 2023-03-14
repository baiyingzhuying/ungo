#ifndef _BOARD_H_
#define _BOARD_H_

#include <iostream>
#include <algorithm>
#include <cstdlib>
#include <cmath>
#include <cstring>
#include <vector>
#include <ctime>
#include <assert.h>
#include <map>
using namespace std;

#define _pos_ pair<int, int>

class Board
{
public:
    int board[10][10], player;
    Board();
    vector<_pos_> cntPoint();
    bool checkmove(int x, int y);
    bool checkend();
    void move(_pos_ p);
    void demove(_pos_ p);
    int steps();
    friend bool operator<(Board a, Board b)
    {
        for (int x = 1; x <= 9; x++)
            for (int y = 1; y <= 9; y++)
                if (a.board[x][y] != b.board[x][y])
                    return a.board[x][y] < b.board[x][y];
        return 0;
    }

private:
    inline bool inboard(int x, int y);
    bool airJudge(int x, int y);
    bool colorJudge(int x, int y);
};

#endif
