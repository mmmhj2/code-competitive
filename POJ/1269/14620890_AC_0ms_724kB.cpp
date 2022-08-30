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
    _out << "" << VT.x << " " << VT.y << "" ;
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
    _tagLine (CPoint p1, CPoint p2)
    {
        point = p1;
        direction = p2 - p1;
    }

    static int intersectionCheck(const _tagLine & a, const _tagLine & b)
    {
        if((a.direction ^ b.direction) == 0)
        {
            CVector t(a.point - b.point);
            if((t ^ a.direction) == 0 && (t ^ b.direction) == 0)
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
}CLine, *pCLine;

int main()
{
    cout << "INTERSECTING LINES OUTPUT" << endl ;

    int N;
    pCLine L1, L2;
    CPoint p1, p2, p3, p4;
    cin >> N;

    while(N--)
    {
        cin >> p1 >> p2 >> p3 >> p4 ;
        L1 = new CLine(p1, p2),
        L2 = new CLine(p3, p4);

        #ifdef LOCAL
        cerr << "Line 1 : " << L1->point << " " << L1->direction << endl;
        cerr << "Line 2 : " << L2->point << " " << L2->direction << endl;
        #endif // LOCAL

        switch(CLine::intersectionCheck(*L1, *L2))
        {
        case -1:
            cout << "LINE";
            break;
        case -2:
            cout << "NONE";
            break;
        default:
            cout << "POINT ";
            cout << fixed << setprecision(2) << CLine::getIntersection(*L1, *L2) ;
        }
        cout << endl ;
        delete L1;
        delete L2;
    }

    cout << "END OF OUTPUT" << endl ;
    return 0;
}
