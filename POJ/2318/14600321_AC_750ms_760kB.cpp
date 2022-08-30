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
bool vecCmp(const CVector & x, const CVector & y)
{
    if(x.x < y.y)
        return true;
    return x.y < y.y;
}
*/

struct CardBoard
{
    int x1, x2, y1, y2;
};
struct Point
{
    int x, y;
};

const int MAXN = 5000 + 10;

int N, M;
int ans[MAXN];
CardBoard cardBoard[MAXN];
Point point[MAXN];

bool Check(int x, int y, const CardBoard & cB)
{
    int tx1 = x - cB.x1,
        ty1 = y - cB.y1,
        tx2 = cB.x2 - cB.x1,
        ty2 = cB.y2 - cB.y1;
    int cross = tx1 * ty2 - tx2 * ty1;
    if(cross > 0)
    {
        //cerr << "Reducing upper bound" << endl ;
        return true;
    }
    //cerr << "Increasing lower bound" << endl ;
    return false;
}

int BinarySearch(int x, int y)
{
    int L = 0, R = N+1;

    while(L + 1 < R)
    {
        int mid = (L+R) >> 1;
        //cerr << "Checking : " << mid << endl ;
        if(Check(x, y, cardBoard[mid]))
            R = mid;
        else
            L = mid;
    }
    //cerr << "final result : " << L << endl ;
    return L;
}

int main()
{
    int x1, y1, x2, y2, U, L;

    while(cin >> N)
    {
        if(!N)
            break;
        cin >> M >> x1 >> y1 >> x2 >> y2 ;
        int x, y;
        memset(ans, 0x00, sizeof ans);
        for(int i = 1; i <= N; i++)
        {
            cin >> U >> L ;
            cardBoard[i].x1 = U,
            cardBoard[i].x2 = L,
            cardBoard[i].y1 = y1,
            cardBoard[i].y2 = y2;
        }
        for(int i = 1; i <= M; i++)
        {
            cin >> x >> y ;
            ans[BinarySearch(x, y)]++;
        }

        for(int i = 0; i <= N; i++)
            cout << i << ": " << ans[i] << endl ;
        cout << endl ;
    }

    return 0;
}
