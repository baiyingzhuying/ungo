#include <bits/stdc++.h>
#include "jsoncpp/json.h"

using namespace std;
#define ll long long

const int sz = 11;   // 棋盘大小
const int sz2 = sz * sz;

#define PLAYER0 0     // 玩家0的标识符
#define PLAYER1 1     // 玩家1的标识符

#define px first      // 坐标x的别名
#define py second     // 坐标y的别名
#define pos pair<int, int>    // 表示坐标的数据结构

int pos_to_id[sz][sz];    // 坐标到索引的映射
pos id_to_pos[sz2];       // 索引到坐标的映射

void init() //该函数用于初始化坐标与索引之间的映射。
{
    srand(time(0));

    for (int i = 0; i < sz; i++)
        for (int j = 0; j < sz; j++) {
            int id = i * sz + j;
            pos_to_id[i][j] = id;
            id_to_pos[id] = pos(i, j);
        }
}

inline bool check(int i, int j) //检查给定的坐标(i, j)是否在合法的范围内
{
    return 0 <= i && i < sz && 0 <= j && j < sz;
}

int dx[6] = {-1, -1, 0, 0, 1, 1};//定义了两个数组 dx 和 dy，用于表示六个方向的移动
int dy[6] = {0, 1, -1, 1, -1, 0};

// using union set to save our state
class UnionSet //并查集,用于管理棋盘上的状态和联通性。
{
public :
    UnionSet();    
    ~UnionSet() {};
    int getfa(int x);//获取元素 x 的根节点（代表元素），并使用路径压缩优化。
    void merge(int x, int y);//合并元素 x 和 y 所在的集合，即将它们所在的连通分量合并为一个。
    int insert(int i, int j);//在位置 (i, j) 插入一个玩家的棋子，并更新相应的连通关系。
    bool legal(int i, int j);//判断位置 (i, j) 是否可以插入一个玩家的棋子，即该位置是否为空。
    void print();
    int col, end;//col：表示当前轮到哪个玩家下棋（0 或 1）。end：表示游戏是否结束，如果游戏结束，则存储获胜玩家的标记。

private :
    int fa[2][sz2 + 2];//保存并查集的数据结构，表示每个元素的父节点（根节点）
    int color[sz][sz];//保存每个格子的颜色，即某个玩家占据的标记。
};

UnionSet::UnionSet() {
    for (int k = 0; k < 2; k++) {
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
    }
        
    col = 0;        
    memset(color, -1, sizeof(color)); 
    end = -1;
}

int UnionSet::getfa(int x)//用于查找元素 x 的根节点（代表元素）
{
    return fa[col][x] == x ? x : fa[col][x] = getfa(fa[col][x]);
}

void UnionSet::merge(int x, int y) //它将元素 x 和元素 y 所在的集合进行合并。
{
    fa[col][getfa(y)] = getfa(x);
}

int UnionSet::insert(int i, int j) //如果当前元素的邻居元素存在且与当前元素具有相同的颜色，就将它们进行合并操作，即将它们的根节点合并在一起。这样做的目的是将相邻的、具有相同颜色的元素连接起来，形成一个更大的集合
{
    int id = pos_to_id[i][j];

    color[i][j] = col;

    for (int k = 0; k < 6; k++) 
        if (check(i + dx[k], j + dy[k]) && color[i + dx[k]][j + dy[k]] == col)
            merge(id, pos_to_id[i + dx[k]][j + dy[k]]);//遍历当前元素周围的六个方向，如果邻居元素存在且与当前元素具有相同的颜色，则将它们进行合并操作

    if (getfa(sz2) == getfa(sz2 + 1)) //判断边界是否完全封闭。
    {
        end = col;
        return col;
    }

    col ^= 1;
    return -1;
}

bool UnionSet::legal(int i, int j) //检查给定位置 (i, j) 是否合法
{
    return color[i][j] == -1;
}

void UnionSet::print() 
{
    for (int i = 0; i < sz; i++)
        for (int j = 0; j < sz; j++)
            cerr << color[i][j] << " \n"[j == sz - 1];
}

// our Monte-Carlo Tree
class Node 
{
public :
    Node() {}
    Node(Node *par, int n_child, pos p, int player);
    ~Node() {};
    int bestChild();
    
    Node *parent;
    vector<Node*> child;
    int nChild, nExpand;//表示当前节点的子节点数量,表示当前节点已经扩展的次数
    pos index;//表示当前节点的位置或索引
    int cntWin, cntAll, player;//表示当前节点的获胜次数（或得分）,表示当前节点的总游玩次数（或访问次数）,表示当前节点对应的玩家
};

Node::Node(Node *par, int n_child, pos p, int play) //构造函数
{
    parent = par;
    nChild = n_child;
    nExpand = 0;
    child.resize(nChild);
    index = p;
    cntWin = cntAll = 0;
    player = play;
}

int Node::bestChild() //选择最佳的子节点
{
    int bstId = 0;
    double maxVal = 0;

    for (int i = 0; i < nExpand; i++) {
        // UCB formula
        //如果当前子节点的评估值（eval）大于当前最大评估值（maxVal），则更新 maxVal 为 eval，同时更新 bstId 为当前子节点的索引（i）。
        double eval = 1.0 * child[i]->cntWin / child[i]->cntAll + 0.9 * sqrt(log(cntAll) / child[i]->cntAll);
        if (eval > maxVal) {
            maxVal = eval;
            bstId = i;
        }
    }
    return bstId;
}

void treePolicy(Node *&now, UnionSet *state) 
//执行蒙特卡洛树搜索的策略
//可以在蒙特卡洛树搜索过程中进行策略的执行，根据当前的游戏状态和已有的树结构，选择合适的子节点进行探索和游戏状态更新。
{
    if (state->end != -1)//如果已经存在胜利的情况（end 不等于 -1），则直接返回，不再执行后续的策略。
        return;

    while (now->nExpand == now->nChild) //当前节点已经扩展了所有可能的子节点，需要选择一个最佳的子节点进行探索
    {
        int bst = now->bestChild();
        
        pos p = now->child[bst]->index;
        int x = p.px, y = p.py;

        now = now->child[bst];

        int t = state->insert(x, y);//将选择的子节点的位置信息传递给游戏状态 state 进行更新
        if (t != -1)
            return;
    }
}

void expandChild(Node *&now, UnionSet *state) //扩展当前节点的子节点
{
    static bool visited[sz][sz];//标记已经访问过的位置
    static pos nxtP[sz2];

    if (state->end != -1 || now->nChild == 0)//游戏已经结束或者当前节点没有子节点可扩展
        return;
    
    int nowExpand = now->nExpand++;

    memset(visited, 0, sizeof(visited));
    
    for (int i = 0; i < nowExpand; i++) {
        int x = now->child[i]->index.px;
        int y = now->child[i]->index.py;
        visited[x][y] = 1;
    }
    
    int cntP = 0;//未访问过且合法的位置的数量
    for (int i = 0; i < sz; i++) 
        for (int j = 0; j < sz; j++) 
            if (!visited[i][j] && state->legal(i, j)) 
                nxtP[cntP++] = pos(i, j);
    
    int t = (int) ((1.0 * cntP * (rand() % 65536)) / 65536);//生成一个随机数t
    int x = nxtP[t].px, y = nxtP[t].py;

    now->child[nowExpand] = new Node(now, now->nChild - 1, pos(x, y), now->player ^ 1);
    now = now->child[nowExpand];
    
    state->insert(x, y);
} 


int defaultPolicy(Node *&now, UnionSet *state) //在当前游戏状态下进行随机操作直到游戏结束
{
    if (state->end != -1)
        return state->end;
    
    static pos posNext[sz2];//未访问过且合法的位置
    int cntNext = 0;//未访问过且合法的位置的数量

    for (int i = 0; i < sz; i++)
        for (int j = 0; j < sz; j++)
            if (state->legal(i, j))
                posNext[cntNext++] = pos(i, j);
    
    while (cntNext)//在未访问的合法位置中随机选择一个位置，并将其传递给游戏状态进行更新 
    {
        int num = (int) ((1.0 * cntNext * (rand() % 65536)) / 65536);
        assert(num < cntNext);//确保生成的随机数 num 是合法的，即小于 cntNext 的值

        pos p = posNext[num];
        posNext[num] = posNext[--cntNext];

        int x = p.px, y = p.py;

        int t = state->insert(x, y);
        if (t != -1)
            return t;
    }
}

void backPropagate(Node *&now, int st) //反向传播更新节点的统计信息，以便更新节点的胜利次数和访问次数
{
    while (now != NULL) {
        now->cntAll++;
        now->cntWin += (now->player == st);
        now = now->parent;
    }
}

#define TIME_LIMIT 0.75

pos mctsSearch(Node *rt, UnionSet *state) //蒙特卡洛树搜索
{
    int st = clock();

    while (1.0 * (clock() - st) / CLOCKS_PER_SEC < TIME_LIMIT) //超过时间限制后，根据已经收集到的统计信息选择最优的子节点
    {
        Node* now = rt;

        UnionSet* st = new UnionSet();
        *st = *state;

        treePolicy(now, st);
        expandChild(now, st);

        int t = defaultPolicy(now, st);
        
        backPropagate(now, t);
    }

    int bstId = 0;
    double maxVal = 0;

    for (int i = 0; i < rt->nExpand; i++) 
    {
        // UCB formula
        double eval = 1.0 * rt->child[i]->cntWin / rt->child[i]->cntAll;

        if (eval > maxVal) {
            maxVal = eval;
            bstId = i;
        }
    }
    
    return rt->child[bstId]->index;
}

int main() {
    init();

    int all = sz2, player = 0;
    UnionSet* state = new UnionSet();

    // 读入JSON
	string str;
	getline(cin, str);
	Json::Reader reader;
	Json::Value input;
	reader.parse(str, input); 
	
    // 分析自己收到的输入和自己过往的输出，并恢复状态
	int turn_id = input["responses"].size();
    int x, y;
    bool forced_flag;
	for (int i = 0; i < turn_id; i++) {
		x = input["requests"][i]["x"].asInt();
        y = input["requests"][i]["y"].asInt();
        if (x >= 0 and y >= 0){
            state->insert(x, y);
            all--;
            player ^= 1;
        }
        x = input["responses"][i]["x"].asInt();
        y = input["responses"][i]["y"].asInt();
        state->insert(x, y);
        all--;
        player ^= 1;
	}
    x = input["requests"][turn_id]["x"].asInt();
    y = input["requests"][turn_id]["y"].asInt();

    if (x >= 0 and y >= 0){
        state->insert(x, y);
        all--;
        player ^= 1;
        forced_flag = false;
    } else if (input["requests"][0].isMember("forced_x")){
        forced_flag = true;
    } else {
        forced_flag = false;
    }

    Json::Value action_json;

    if (forced_flag) {
        action_json["x"] = 1;
	    action_json["y"] = 2;
    } else {
        Node* rt = new Node(NULL, all, pos(-1, -1), player ^ 1);
        pos nxt = mctsSearch(rt, state);
        action_json["x"] = nxt.px;
	    action_json["y"] = nxt.py;
    }

    // 做出决策存为action 
	// 输出决策JSON
	Json::Value result;
	
    result["response"] = action_json;

	Json::FastWriter writer;
	
    cout << writer.write(result) << endl;
	
    return 0;
}