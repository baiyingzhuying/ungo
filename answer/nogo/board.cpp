#include <iostream>
#include <algorithm>
#include <cstdlib>
#include <cmath>
#include <cstring>
#include <vector>
#include <ctime>
#include <assert.h>
#include <map>
#include "board.h"
using namespace std;

int dx[4] = {0, 1, 0, -1}, dy[4] = {-1, 0, 1, 0};
bool airJudged[10][10];
#define _pos_ pair<int, int>

Board ::Board()
{
    memset(board, 0, sizeof(board));
    player = 1;
}

int Board ::steps()
{
    int cc = 0;
    for (int x = 1; x <= 9; x++)
        for (int y = 1; y <= 9; y++)
            if (board[x][y])
                cc++;
    return cc;
}

inline bool Board ::inboard(int x, int y)
{
    return 1 <= x && x <= 9 && 1 <= y && y <= 9;
}

bool Board ::airJudge(int x, int y)
{
    bool flag = 0;
    airJudged[x][y] = 1;
    for (int i = 0; i < 4; i++)
    {
        int X = x + dx[i], Y = y + dy[i];
        if (inboard(X, Y))
        {
            if (board[X][Y] == 0)
                flag = 1;
            if (board[X][Y] == board[x][y] && !airJudged[X][Y])
                if (airJudge(X, Y))
                    flag = 1;
        }
    }
    return flag;
}

bool Board ::colorJudge(int x, int y)
{
    if (!inboard(x, y) || board[x][y])
        return 0;
    board[x][y] = player;
    memset(airJudged, 0, sizeof(airJudged));
    if (!airJudge(x, y))
    {
        board[x][y] = 0;
        return 0;
    }
    for (int i = 0; i < 4; i++)
    {
        int X = x + dx[i], Y = y + dy[i];
        if (inboard(X, Y))
        {
            if (board[X][Y] && !airJudged[X][Y])
                if (!airJudge(X, Y))
                {
                    board[x][y] = 0;
                    return 0;
                }
        }
    }
    board[x][y] = 0;
    return 1;
}

bool Board ::checkmove(int x, int y) {
    return colorJudge(x, y);
}

bool Board ::checkend() {
    return cntPoint().empty();
}

vector<_pos_> Board ::cntPoint()
{
    vector<_pos_> res;
    for (int x = 1; x <= 9; x++)
        for (int y = 1; y <= 9; y++)
            if (colorJudge(x, y))
                res.push_back(_pos_(x, y));
    return res;
}

void Board ::move(_pos_ p)
{
    int x = p.first, y = p.second;
    assert(board[x][y] == 0);
    board[x][y] = player;
    player = 3 - player;
}

void Board ::demove(_pos_ p)
{
    int x = p.first, y = p.second;
    assert(board[x][y] != 0);
    board[x][y] = 0;
    player = 3 - player;
}
