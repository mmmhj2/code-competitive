#include <algorithm>
#include <iostream>
#include <iomanip>
#include <cstring>
#include <cstdlib>
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

typedef struct _tagSegment
{
    CPoint a, b;
    _tagSegment() {};
    _tagSegment(CPoint _a, CPoint _b) :
        a(_a), b(_b) {};

    static bool intersection(const _tagSegment &seg1, const _tagSegment &seg2)
    {
        if (max(seg1.a.x, seg1.b.x) < min(seg2.a.x, seg2.b.x) ||
            max(seg1.a.y, seg1.b.y) < min(seg2.a.y, seg2.b.y) ||
            max(seg2.a.x, seg2.b.x) < min(seg1.a.x, seg1.b.x) ||
            max(seg2.a.y, seg2.b.y) < min(seg1.a.y, seg1.b.y))
            return false;
        int c1 = (seg1.b - seg1.a) ^ (seg2.a - seg1.a),
            c2 = (seg1.b - seg1.a) ^ (seg2.b - seg1.a),
            c3 = (seg2.b - seg2.a) ^ (seg1.a - seg2.a),
            c4 = (seg2.b - seg2.a) ^ (seg1.b - seg2.a);
        if (c1 * c2 > 0 || c3 * c4 > 0)
            return false;
        return true;
    }
} CSegment, *pCSegment;

const int MAXN = 100 + 5;

CLine line[MAXN];
CPoint pnts[MAXN * 2];

int main()
{
    int T;
    cin >> T ;
    while(T--)
    {
        int N;
        cin >> N;
        for(int i = 0; i < N; i++)
        {
            cin >> pnts[(i << 1)] >> pnts[(i << 1) | 1] ;
            line[i] = CLine(pnts[(i << 1)], pnts[((i << 1) | 1)]);
        }

        bool noIntersection = false;
        bool hasSolution = false;
        for(int i = 0; i < N*2; i++)
        {
            for(int j = i+1; j < N*2; j++)
            {
                noIntersection = false;
                CLine t(pnts[i], pnts[j]);
                CPoint intersection;

                //cerr << "检查直线：" << t.point << " " << t.direction << endl ;
                //cerr << "由" << pnts[i] << " " << pnts[j] << "构成" << endl ;

                for(int k = 0; k < N; k++)
                {
                    //cerr << "与直线" << k << "[" << line[k].point << " " << line[k].direction << "]" << "的相交情况：" ;
                    int chk = CLine::intersectionCheck(t, line[k]);
                    /*
                    if(chk == -1)
                        continue;
                    if(chk == -2)
                    {
                        noIntersection = true;
                        break;
                    }
                    if(intersection.x < min(pnts[i<<1].x, pnts[(i<<1)|1].x) || intersection.x > max(pnts[i<<1].x, pnts[(i<<1)|1].x))
                    {
                        noIntersection = true;
                        break;
                    }
                    */
                    switch(chk)
                    {
                    case -1:
                        //cerr << "共线" << endl ;
                        break;
                    case -2:
                        //cerr << "平行" << endl ;
                        noIntersection = true;
                        break;
                    default:
                        //cerr << "相交" << endl ;
                        //cerr << "交点坐标：" << intersection << endl ;
                        intersection = CLine::getIntersection(t, line[k]);
                        if((intersection.x < min(pnts[i<<1].x, pnts[(i<<1)|1].x)) ||
                           (intersection.x > max(pnts[i<<1].x, pnts[(i<<1)|1].x)))
                        {
                            noIntersection = true;
                        }

                        if((intersection.y < min(pnts[i<<1].y, pnts[(i<<1)|1].y)) ||
                           (intersection.y > max(pnts[i<<1].y, pnts[(i<<1)|1].y)))
                        {
                            noIntersection = true;
                        }
                        if((intersection.x < min(pnts[j<<1].x, pnts[(j<<1)|1].x)) ||
                           (intersection.x > max(pnts[j<<1].x, pnts[(j<<1)|1].x)))
                        {
                            noIntersection = true;
                        }

                        if((intersection.y < min(pnts[j<<1].y, pnts[(j<<1)|1].y)) ||
                           (intersection.y > max(pnts[j<<1].y, pnts[(j<<1)|1].y)))
                        {
                            noIntersection = true;
                        }

                    }
                }

                if(!noIntersection)
                {
                    hasSolution = true;
                    break;
                }
            }
            if(hasSolution)
                break;
        }
        if(!hasSolution)
            cout << "No!" << endl ;
        else
            cout << "Yes!" << endl ;
    }
    return 0;
}
