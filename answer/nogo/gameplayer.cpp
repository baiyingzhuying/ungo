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
#include "gameplayer.h"
#include <QDebug>
using namespace std;

// We use UCT_RAVE Search Algorithm and greedy
#define TIME_LIMIT 0.98
#define pex pair<Board, _pos_>

map<Board, int> Ns_UCT;
map<pex, int> N_UCT, Q_UCT;
map<_pos_, int> N_RAVE, Q_RAVE;
int Ns_RAVE;

vector<_pos_> visited;

#define db double
#define EQUIV 20
#define PREFER 0.3
_pos_ Gameplayer ::BestChild(Board now)
{
    vector<_pos_> nxt = now.cntPoint();
    for (int i = 1; i <= 5; i++)
        random_shuffle(nxt.begin(), nxt.end());
    db max_eval = -1;
    _pos_ max_child = _pos_(-1, -1);
    int all = now.steps();
    int lst = 80 - all;
    for (auto u : nxt)
    {
        db eval_UCT = 1.0 * Q_UCT[pex(now, u)] / N_UCT[pex(now, u)] + sqrt(1.96 * log(Ns_UCT[now]) / N_UCT[pex(now, u)]);
        db eval_RAVE = 1.0 * Q_RAVE[u] / N_RAVE[u] + 0.2 * sqrt(log(Ns_RAVE) / N_RAVE[u]);
        db beta = sqrt(EQUIV / (EQUIV + 3.0 * all));
        db eval = beta * eval_RAVE + (1.0 - beta) * eval_UCT;
        now.move(u);
        eval = PREFER * eval + (1.0 - PREFER) * (lst - now.cntPoint().size()) / lst;
        now.demove(u);
        if (eval > max_eval)
        {
            max_eval = eval;
            max_child = u;
        }
    }
    return max_child;
}

Board Gameplayer ::Tree_Policy(Board now)
{
    vector<_pos_> nxt = now.cntPoint();
    while (!nxt.empty()) {
        for (int i = 1; i <= 5; i++)
            random_shuffle(nxt.begin(), nxt.end());

        for (auto u : nxt)
        {
            if (N_UCT.find(pex(now, u)) == N_UCT.end())
            {
                visited.push_back(u);
                now.move(u);
                goto ed;
            }
        }

        db max_eval = -1;
        _pos_ max_child = _pos_(-1, -1);
        int all = now.steps();
        for (auto u : nxt)
        {
            db eval_UCT = 1.0 * Q_UCT[pex(now, u)] / N_UCT[pex(now, u)] + sqrt(1.96 * log(Ns_UCT[now]) / N_UCT[pex(now, u)]);
            db eval_RAVE = 1.0 * Q_RAVE[u] / N_RAVE[u] + 0.2 * sqrt(log(Ns_RAVE) / N_RAVE[u]);
            db beta = sqrt(EQUIV / (EQUIV + 3.0 * all));
            db eval = beta * eval_RAVE + (1.0 - beta) * eval_UCT;
            if (eval > max_eval)
            {
                max_eval = eval;
                max_child = u;
            }
        }
        visited.push_back(max_child);
        now.move(max_child);
        nxt = now.cntPoint();
    }
    ed :
    return now;
}

int Gameplayer ::Default_Policy(Board now)
{
    vector<_pos_> nxt = now.cntPoint();
    while (!nxt.empty()) {
        int sz = nxt.size();
        now.move(nxt[rand() % sz]);
        nxt = now.cntPoint();
    }
    return 3 - now.player;
}

void Gameplayer ::Backup(Board now, int winner)
{
    while (!visited.empty())
    {
        auto u = visited.back();
        visited.pop_back();
        now.demove(u);

        Ns_UCT[now]++;
        N_UCT[pex(now, u)]++;

        Ns_RAVE++;
        N_RAVE[u]++;

        if (now.player == winner) {
            Q_UCT[pex(now, u)]++;
            Q_RAVE[u]++;
        }

    }
}

_pos_ Gameplayer ::UCT_RAVE_Search(Board now)
{
    int st = clock();
    while (1.0 * (clock() - st) / CLOCKS_PER_SEC < TIME_LIMIT)
    {
        visited.clear();
        Board ed = Tree_Policy(now);
        int winner = Default_Policy(ed);
        Backup(ed, winner);
    }
    return BestChild(now);
}

_pos_ Gameplayer ::play(_pos_ x)
{
    if (x != _pos_(-1, -1))
        now.move(x);
    _pos_ res = UCT_RAVE_Search(now);
    now.move(res);
    return res;
}
