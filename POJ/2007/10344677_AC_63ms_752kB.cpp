#include<iostream>
#include<cmath>
#include<algorithm>
#include<cstdio>
using namespace std;

class _CVector;

typedef const _CVector& CCVECR;

class _CVector
{
public:
    double x, y;

    _CVector()
    {
        x = 0; y = 0;
    }

    _CVector(double a, double b)
    {
        x = a; y = b;
    }


    _CVector operator + (CCVECR);
    _CVector operator - (CCVECR);
    /// @brief 向量积
    friend _CVector operator * (double, CCVECR);
    friend _CVector operator * (CCVECR, double);
    /// @brief 向量点积
    double operator * (CCVECR);
    /// @brief 向量叉积
    double operator ^ (CCVECR);

    /// @brief 长度
    static double length (_CVector);
    /// @brief 单位矢量
    static _CVector unit (CCVECR);
    /// @brief 计算投影
    static double project(_CVector, _CVector);
//    static _CVector dot (_CVector, _CVector);

};

typedef _CVector CVector, CPoint;
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief 主函数

bool sotcp(CVector a, CVector b)
{
    if((CVector(b-CPoint(0, 0)) ^ (CVector(a-CPoint(0, 0)))) > 0)
        return true;
    return false;
}

CPoint point[60];

int main(int argc, char ** argv, char ** envp)
{
    int n = 0;
    while(cin >> point[n].x >> point[n].y)
        n++;
    sort(point+1, point+n, sotcp);
    cout << "(0,0)" << endl;
    for(int i = n-1; i > 0; i--)
        printf("(%d,%d)\n", (int)point[i].x, (int)point[i].y);
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
_CVector _CVector :: operator + (CCVECR p)
{
    return _CVector(x + p.x, y + p.y);
}

_CVector _CVector :: operator - (CCVECR p)
{
    return _CVector(x - p.x, y - p.y);
}

_CVector operator * (double k, CCVECR p)
{
    return _CVector(p.x * k, p.y * k);
}

_CVector operator * (CCVECR p, double k)
{
    return k*p;
}

double _CVector :: operator * (CCVECR p)
{
    return x*p.x + y*p.y;
}

double _CVector :: length(_CVector p)
{
    return sqrt(p * p);
}

_CVector _CVector :: unit(CCVECR p)
{
    return (1 / length(p)) * p;
}

double _CVector :: project(_CVector p, _CVector q)
{
    return p * (_CVector::unit(q));
}

double _CVector :: operator ^ (CCVECR p)
{
    return x*p.y - y*p.x;
}
