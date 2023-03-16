#ifndef ITEM_H
#define ITEM_H
#include<qpoint.h>

class Item
{
public:
    Item();
    Item(QPoint pt,int bBlack);
    QPoint m_pt;//棋子坐标
    bool operator ==(const Item &t1) const
    {
        return (m_bBlack == t1.m_bBlack && m_pt == t1.m_pt);
    }
    int m_bBlack=0;//黑方还是白方下棋
};

#endif // ITEM_H
