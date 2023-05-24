
#ifndef AI_H
#define AI_H
#include<QPair>
#include<Qvector>
#include"ui_mainwindow.h"
#define ll long long

const int sz = 9;   // 棋盘大小
const int sz2 = sz * sz;

#define PLAYER0 0     // 玩家0的标识符
#define PLAYER1 1     // 玩家1的标识符
#define poss std::pair<int, int>    // 表示坐标的数据结构
class Ai{
public:
    class UnionSet //并查集,用于管理棋盘上的状态和联通性。
    {
    public :
        UnionSet();//构造
    ~UnionSet() {};//析构
        void init();
    bool check1(int i,int j);//不越界
        int getfa(int x);//获取元素 x 的根节点（代表元素），并使用路径压缩优化，时间复杂度o(a)。
        void merge(int x, int y);//合并元素 x 和 y 所在的集合，即将它们所在的连通分量合并为一个。
        int insert(int i, int j);//在位置 (i, j) 插入一个玩家的棋子，并更新相应的连通关系。
        bool legal(int i, int j);//判断位置 (i, j) 是否可以插入一个玩家的棋子，即该位置是否为空。
        void print();
        int col, end;//col：表示当前轮到哪个玩家下棋（0 或 1）。end：表示游戏是否结束，如果游戏结束，则存储获胜玩家的标记。
        int dx[6] = {-1, -1, 0, 0, 1, 1};//定义了两个数组 dx 和 dy，用于表示六个方向的移动
        int dy[6] = {0, 1, -1, 1, -1, 0};
        int pos_to_id[sz][sz];    // 坐标到索引的映射
        poss id_to_pos[sz2];       // 索引到坐标的映射
        int fa[2][15];//保存并查集的数据结构，表示每个元素的父节点（根节点）
        int color[15][15];//保存每个格子的颜色，即某个玩家占据的标记。
    };
    class Node
    {
    public :
        Node() {}
        Node(Node *par, int n_child, poss p, int player);
        ~Node() {};
        int bestChild();
        Node *parent;
        std::vector<Node*> child;
        int nChild, nExpand;//表示当前节点的子节点数量,表示当前节点已经扩展的次数
        poss index;//表示当前节点的位置或索引
        int cntWin, cntAll, player;//表示当前节点的获胜次数（或得分）,表示当前节点的总游玩次数（或访问次数）,表示当前节点对应的玩家
    };
    UnionSet *unionSet; // Public member variable for UnionSet
    Node *node1; // Public member variable for Node
    void treePolicy(Node *&now, UnionSet *state);
    void expandChild(Node *&now,UnionSet *state);
    int defaultPolicy(Node *&now, UnionSet *state);
    void backPropagate(Node *&now, int st);
    poss mctsSearch(Node *rt, UnionSet *state);
};

#endif // AI_H
