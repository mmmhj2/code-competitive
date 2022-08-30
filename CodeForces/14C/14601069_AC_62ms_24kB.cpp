#include <algorithm>
#include <iostream>
#include <cstring>
using namespace std;
/*
template <typename T>
struct VectorTemplate
{
    T x, y;
    VectorTemplate() {};
    VectorTemplate(T _x, T _y) :
        x(_x), y(_y) {};

    VectorTemplate operator + (const VectorTemplate & rhs) const
    {
        return VectorTemplate(x + rhs.x, y + rhs.y);
    }
    VectorTemplate operator - (const VectorTemplate & rhs) const
    {
        return VectorTemplate(x - rhs.x, y - rhs.y);
    }
    /// @b 向量数乘
    VectorTemplate operator * (double rhs) const
    {
        return VectorTemplate(x * rhs, y * rhs);
    }
    /// @b 向量点乘
    T operator * (const VectorTemplate & rhs) const
    {
        return x * rhs.x + y * rhs.y;
    }
    /// @b 向量叉乘
    T operator ^ (const VectorTemplate & rhs) const
    {
        return x * rhs.y - y * rhs.x;
    }
};

typedef VectorTemplate<int> CVector;
*/

int main()
{
    int tx = 0, ty = 0;
    int x, y;
    bool isRect = true;
    pair<int, int> pnts[10];
    for(int i = 0; i < 8; i++)
    {
        cin >> x >> y ;
        pnts[i].first = x,
        pnts[i].second = y;
    }
    // There should be exactly one point (self-exclusively) which has the same coordinate
    for(int i = 0; i < 8; i++)
    {
        int cnt = 0;
        for(int j = 0; j < 8; j++)
            if(pnts[i].first == pnts[j].first && pnts[i].second == pnts[j].second)
                cnt++;
        if(cnt != 2)
        {
            isRect = false;
            goto RESULT;
        }
    }

    // There should be exactly two edges which have different x but the same y,
    // and two ones have different y but the same x
    for(int i = 0; i < 4; i++)
    {
        int p1 = i << 1;
        int p2 = p1 + 1;
        if(pnts[p1].first == pnts[p2].first && pnts[p1].second != pnts[p2].second)
            tx++;
        if(pnts[p1].first != pnts[p2].first && pnts[p1].second == pnts[p2].second)
            ty++;
    }

    isRect = (tx == 2 && ty == 2);

RESULT:
    if(isRect)
        cout << "YES" << endl ;
    else
        cout << "NO" << endl ;

    return 0;
}
