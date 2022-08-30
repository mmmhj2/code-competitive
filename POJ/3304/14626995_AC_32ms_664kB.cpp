#include <algorithm>
#include <iostream>
#include <iomanip>
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <cmath>

#define L(x) ((x<<1))
#define R(x) ((x<<1)|1)

using namespace std;
// Constant
const double EPS = 1e-8;
const int MAXN = 100 + 5;
// Universal Functions
int sgn(double x)
{
    if(fabs(x) < EPS)
        return 0;
    else if(x < 0)
        return -1;
    else
        return 1;
}
// Data types
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

template <typename T>
ostream & operator << (ostream & _out, VectorTemplate<T> VT)
{
    _out << "(" << VT.x << "," << VT.y << ")" ;
    return _out;
}
template <typename T>
istream & operator >> (istream & _in, VectorTemplate<T> & VT)
{
    _in >> VT.x >> VT.y ;
    return _in;
}

typedef VectorTemplate<double> CVector, CPoint;
/*
typedef struct _tagLine
{
    CVector direction;
    CPoint point;
    _tagLine(){};
    _tagLine(CPoint p1, CPoint p2)
    {
        point = p1;
        direction = p2 - p1;
    }

    static int intersectionCheck(const _tagLine & a, const _tagLine & b)
    {
        if ((a.direction ^ b.direction) == 0)
        {
            CVector t(a.point - b.point);
            if ((t ^ a.direction) == 0 && (t ^ b.direction) == 0)
                return -1;      // 重合
            return -2;          // 平行
        }
        return 0;
    }

    static CPoint getIntersection(const _tagLine & a, const _tagLine & b)
    {
        CVector t = a.point - b.point;
        double delta = 1.00 * (b.direction ^ t) / (a.direction ^ b.direction);
        return a.point + a.direction * delta;
    }
} CLine, *pCLine;
*/
typedef struct _tagLine
{
    CPoint s, e;
    _tagLine(){};
    _tagLine(CPoint _s, CPoint _e) :
        s(_s), e(_e) {};

    static double multi(const CPoint & p0, const CPoint & p1, const CPoint & p2)
    {
        return (p1 - p0) ^ (p2 - p0);
    }

    static bool segInLine(const _tagLine & lin, const _tagLine & seg)
    {
        return sgn(multi(seg.s, lin.s, lin.e)) * sgn(multi(seg.e, lin.s, lin.e)) <= 0;
    }
}CLine, *pCLine;
// Global Variables
CLine line[MAXN];
CPoint pnts[MAXN * 2];

double get_dist(CPoint a, CPoint b)
{
    return sqrt((a.x-b.x) * (a.x-b.x) + (a.y-b.y) * (a.y-b.y));
}

int main()
{
    int T;
    scanf("%d", &T);
    while(T--)
    {
        bool hasSolution = false;
        int N;
        scanf("%d", &N);
        for(int i = 0; i < N; i++)
            scanf("%lf%lf%lf%lf",
                &pnts[L(i)].x ,&pnts[L(i)].y,
                &pnts[R(i)].x ,&pnts[R(i)].y),
            line[i] = CLine(pnts[L(i)], pnts[R(i)]);

        for(int i = 0; i < N * 2 && !hasSolution; i++)
            for(int j = 0; j < N * 2 && !hasSolution; j++)
            {
                bool noIntersect = false;
                if(!sgn(get_dist(pnts[i], pnts[j])))
                    continue;
                CLine cur(pnts[i], pnts[j]);
                for(int k = 0; k < N; k++)
                    if(!CLine::segInLine(cur, line[k]))
                    {
                        noIntersect = true;
                        break;
                    }
                if(!noIntersect)
                    hasSolution = true;
            }

        if(hasSolution)
            puts("Yes!");
        else
            puts("No!");
    }
    return 0;
}
