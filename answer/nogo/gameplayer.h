#ifndef _GAMEPLAYER_H_
#define _GAMEPLAYER_H_

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

// We use UCT_RAVE Search Algorithm and greedy

class Gameplayer
{
public :
    mutable Board now;
    Gameplayer()
    {
        srand(time(0));
    }
    _pos_ play(_pos_ x);

private :
    _pos_ BestChild(Board now);
    Board Tree_Policy(Board now);
    int Default_Policy(Board now);
    void Backup(Board now, int winner);
    _pos_ UCT_RAVE_Search(Board now);
};

#endif
