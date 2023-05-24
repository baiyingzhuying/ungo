#include"ai.h"
#include"mainwindow.h"
//现在我们需要补充一个能让ai识别到棋盘的功能
//那么逻辑上这个ai是一个双线程的操作，我们在mainwindow和ai里面都设有数组来存储当前的对局信息，并进行了共通（从ai->mainwindow方面的）
//所以在中途要求和ai对局的时候，我们需要将mainwindow中的数据与ai进行互通。
#define px first      // 坐标x的别名
#define py second     // 坐标y的别名


static int fa[2][15];//保存并查集的数据结构，表示每个元素的父节点（根节点）
static int color[15][15];//保存每个格子的颜色，即某个玩家占据的标记。

void Ai::UnionSet::init() //该函数用于初始化坐标与索引之间的映射。
{
    srand(time(0));//用当前的时间来随机
    for (int i = 0; i < sz; i++)
        for (int j = 0; j < sz; j++) {
            int id = i * sz + j;//二维转一维
            pos_to_id[i][j] = id;
            id_to_pos[id] = poss(i, j);//用一个pair来对应id
        }
}
bool Ai::UnionSet::check1(int i,int j){
    return 0 <= i && i < sz && 0 <= j && j < sz;
}
Ai::UnionSet::UnionSet(){
    for (int k = 0; k < 2; k++) {//k对应玩家颜色
        for (int i = 0; i < sz; i++)
            for (int j = 0; j < sz; j++) {
                int id = pos_to_id[i][j];//将二维坐标 (i, j) 转换为唯一的一维编号 id，用于表示并查集中的一个元素。
                if (i == 0 && k == 0) //设置特殊的根节点，用于表示边界上的虚拟节点。
                    fa[k][id] = sz2;
                else if (i == sz - 1 && k == 0)
                    fa[k][id] = sz2 + 1;
                else if (j == 0 && k == 1)
                    fa[k][id] = sz2;
                else if (j == sz - 1 && k == 1)
                    fa[k][id] = sz2 + 1;
                else fa[k][id] = id;
            }
        fa[k][sz2] = sz2;
        fa[k][sz2 + 1] = sz2 + 1;
    }//初始化并查集
    col = 0;
    memset(color, -1, sizeof(color)); //初始化所有位置为-1
    end = -1;
}
int Ai::UnionSet::getfa(int x) {
     return fa[col][x] == x ? x : fa[col][x] = getfa(fa[col][x]);
}
void Ai::UnionSet::merge(int x,int y) {
     fa[col][getfa(y)]=getfa(x);
}
int Ai::UnionSet::insert(int i,int j) {//插入一个棋子
     int id = pos_to_id[i][j];
     color[i][j] = col;
     game->m_items[i][j]=col;
     for (int k = 0; k < 6; k++)
        if (check1(i + dx[k], j + dy[k]) && color[i + dx[k]][j + dy[k]] == col)
            merge(id, pos_to_id[i + dx[k]][j + dy[k]]);//遍历当前元素周围的六个方向，如果邻居元素存在且与当前元素具有相同的颜色，则将它们进行合并操作

     if (getfa(sz2) == getfa(sz2 + 1)) //判断边界是否完全封闭。
     {
        end = col;
        return col;
     }

     col =3-col;
     return -1;
}//事实上是没有必要的，这玩意只有Ai用的时候才好用
bool Ai::UnionSet::legal(int i,int j) {
     return color[i][j]!=-1;
}


Ai::Node::Node(Node *par, int n_child, poss p, int play) //构造函数
{
     parent = par;//父节点
     nChild = n_child;//子结点个数
     nExpand = 0;//拓展次数初始化
     child.resize(nChild);//设置大小
     index = p;//指向当前节点
     cntWin = cntAll = 0;//得分
     player = play;//玩家
}

int Ai::Node::bestChild() //选择最佳的子节点
{
     int bstId = 0;//最好的位置
     double maxVal = 0;//记录最大的评估值
     for (int i = 0; i < nExpand; i++) {
        // UCB formula
        //UCB算法公式
        //如果当前子节点的评估值（eval）大于当前最大评估值（maxVal），则更新 maxVal 为 eval，同时更新 bstId 为当前子节点的索引（i）。
        double eval = 1.0 * child[i]->cntWin / child[i]->cntAll + 0.9 * sqrt(log(cntAll) / child[i]->cntAll);
        //计算公式 获胜次数/游玩次数+0.9*√（ln(目前的游玩次数)/子节点游玩次数）
        //前半部分表示期望回报，后半部分是一种探索（非贪心），从而表示总体的期望回报的不确定程度
        if (eval > maxVal) {
            maxVal = eval;
            bstId = i;
        }
     }
     return bstId;
}

void Ai::treePolicy(Ai::Node *&now, Ai::UnionSet *state) //执行蒙特卡洛树搜索的策略,可以在蒙特卡洛树搜索过程中进行策略的执行，根据当前的游戏状态和已有的树结构，选择合适的子节点进行探索和游戏状态更新。
{
     if (state->end != -1)//如果已经存在胜利的情况（end 不等于 -1），则直接返回，不再执行后续的策略。
        return;
     while (now->nExpand == now->nChild) //当前节点已经扩展了所有可能的子节点，需要选择一个最佳的子节点进行探索
     {
        int bst = now->bestChild();
        //返回最优子节点位置,在这里进行了预测
        poss p = now->child[bst]->index;
        //找到对应坐标
        int x = p.px, y = p.py;
        //存储最优子节点信息
        now = now->child[bst];
        //更新
        int t = state->insert(x, y);//将选择的子节点的位置信息传递给游戏状态 state 进行更新
        if (t != -1)
            return;
     }
}

void Ai::expandChild(Ai::Node *&now, Ai::UnionSet *state) //扩展当前节点的子节点
{
     static bool visited[sz][sz];//标记已经访问过的位置
     static poss nxtP[sz2];

     if (state->end != -1 || now->nChild == 0)//游戏已经结束或者当前节点没有子节点可扩展
        return;
     //拓展次数
     int nowExpand = now->nExpand++;

     memset(visited, 0, sizeof(visited));

     for (int i = 0; i < nowExpand; i++) {
        int x = now->child[i]->index.px;
        int y = now->child[i]->index.py;
        visited[x][y] = 1;
        //所有访问过的节点
     }
     int cntP = 0;//未访问过且合法的位置的数量
     for (int i = 0; i < sz; i++)
        for (int j = 0; j < sz; j++)
            if (!visited[i][j] && state->legal(i, j))
                nxtP[cntP++] = poss(i, j);//存储象形的坐标
     //cnt的最大值 sz*sz
     int t = (int) ((1.0 * cntP * (rand() % 65536)) / 65536);//生成一个随机数t（0~cnt),精妙的设计
     int x = nxtP[t].px, y = nxtP[t].py;
     //返回到相应的坐标
     now->child[nowExpand] = new Ai::Node(now, now->nChild - 1, poss(x, y), now->player ^ 1);//新增节点，子节点-1，对应的坐标,最后一个异或1从而进行玩家的转换
     //扩展子节点
     now = now->child[nowExpand];
     state->insert(x, y);
     //插入
}

int Ai::defaultPolicy(Ai::Node *&now, Ai::UnionSet *state) //在当前游戏状态下进行随机操作直到游戏结束。
{
     if (state->end != -1)
        return state->end;
     //还没有找到最优解
     static poss posNext[sz2];//未访问过且合法的位置
     int cntNext = 0;//未访问过且合法的位置的数量
     for (int i = 0; i < sz; i++)
        for (int j = 0; j < sz; j++)
            if (state->legal(i, j))
                posNext[cntNext++] = poss(i, j);
     //存储坐标
     while (cntNext)//在未访问的合法位置中随机选择一个位置，并将其传递给游戏状态进行更新
    {
        int num = (int) ((1.0 * cntNext * (rand() % 65536)) / 65536);//(0~cntNext)
        assert(num < cntNext);//确保生成的随机数 num 是合法的，即小于 cntNext 的值(应该是不存在能=cntNext的)
        poss p = posNext[num];//得到对应位置的坐标
        posNext[num] = posNext[--cntNext];//下一个坐标
        int x = p.px, y = p.py;
        int t = state->insert(x, y);//传参
        if (t != -1)
            return t;
     }
}

void Ai::backPropagate(Ai::Node *&now, int st) //反向传播更新节点的统计信息，以便更新节点的胜利次数和访问次数
{
     //现在仍然可以找到节点
     while (now != NULL) {
        now->cntAll++;//总游玩次数
        now->cntWin += (now->player == st);//胜利次数
        now = now->parent; //往父节点返回
     }
}

#define TIME_LIMIT 0.75//设置时间限制

poss Ai::mctsSearch(Ai::Node *rt, Ai::UnionSet *state) //蒙特卡洛树搜索
{
     int st = clock();//time.h中的函数，用来计时

     while (1.0 * (clock() - st) / CLOCKS_PER_SEC < TIME_LIMIT) //超过时间限制后，根据已经收集到的统计信息选择最优的子节点
     //卡时，不过可以修改一下，时间要求没有那么高
     //CLOCKS_PER_SEC将单位转成秒
     {
        Ai::Node* now = rt;
        //新建并查集
        Ai::UnionSet* st = new Ai::UnionSet();
        *st = *state;
        //现在状态
        treePolicy(now, st);//开始搜索,这里存储了最优的子节点
        expandChild(now, st);//扩展子节点

        int t = defaultPolicy(now, st);//随机落子的条件下,返回落子方

        backPropagate(now, t);//从相应的子节点返回
     }

     int bstId = 0;
     double maxVal = 0;

     for (int i = 0; i < rt->nExpand; i++)
     {
        // UCB formula
        double eval = 1.0 * rt->child[i]->cntWin / rt->child[i]->cntAll;
        //估值函数:胜利次数/游玩次数,这是一个期望的计算，没有处理预测
        if (eval > maxVal) {
            maxVal = eval;
            bstId = i;
        }
     }

     return rt->child[bstId]->index;
}

