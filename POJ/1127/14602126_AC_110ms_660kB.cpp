#include <algorithm>
#include <iostream>
#include <cstring>
using namespace std;

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

typedef VectorTemplate<int> CVector, CPoint;


class disjointSet
{
    const static int MAXN = 20 + 5;
    int fa[MAXN];
public:
    disjointSet()
    {
        for (int i = 0; i < MAXN; i++)
            fa[i] = i;
    }

    // With compression
    int find(int x)
    {
        if (x == fa[x])
            return x;
        return fa[x] = find(fa[x]);
    }

    void unite(int x, int y)
    {
        fa[find(x)] = find(y);
    }
};

struct segment
{
    CPoint a, b;
} seg[20];

bool intersection(const segment &seg1, const segment &seg2)
{
    if (max(seg1.a.x, seg1.b.x) < min(seg2.a.x, seg2.b.x) ||
            max(seg1.a.y, seg1.b.y) < min(seg2.a.y, seg2.b.y) ||
            max(seg2.a.x, seg2.b.x) < min(seg1.a.x, seg1.b.x) ||
            max(seg2.a.y, seg2.b.y) < min(seg1.a.y, seg1.b.y))
    {
        return false;
    }
    if ((((seg1.a.x - seg2.a.x) * (seg2.b.y - seg2.a.y) - (seg1.a.y - seg2.a.y) * (seg2.b.x - seg2.a.x)) *
            ((seg1.b.x - seg2.a.x) * (seg2.b.y - seg2.a.y) - (seg1.b.y - seg2.a.y) * (seg2.b.x - seg2.a.x))) > 0 ||
            (((seg2.a.x - seg1.a.x) * (seg1.b.y - seg1.a.y) - (seg2.a.y - seg1.a.y) * (seg1.b.x - seg1.a.x)) *
             ((seg2.b.x - seg1.a.x) * (seg1.b.y - seg1.a.y) - (seg2.b.y - seg1.a.y) * (seg1.b.x - seg1.a.x))) > 0)
    {
        return false;
    }
    return true;
}

int main()
{
    disjointSet * dS;
    int N;
    while (cin >> N)
    {
        if(!N)
            break;
        dS = new disjointSet;
        for (int i = 1; i <= N; i++)
            cin >> seg[i].a.x >> seg[i].a.y >> seg[i].b.x >> seg[i].b.y ;

        for (int i = 1; i <= N; i++)
            for (int j = 1; j < i; j++)
                if (intersection(seg[i], seg[j]))
                    dS->unite(i, j);

        int x, y;
        while (cin >> x >> y)
        {
            if ((!x) && (!y))
                break;;
            if (dS->find(x) == dS->find(y))
                cout << "CONNECTED" << endl ;
            else
                cout << "NOT CONNECTED" << endl ;
        }
        delete dS;
    }

    return 0;
}
