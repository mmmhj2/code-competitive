#include <cmath>
#include <iostream>
#include <algorithm>
using namespace std;

const int MAXN = 50000;

struct _cow
{
    int w, s;

    static int cmp (const _cow & lhs, const _cow & rhs)
    {
        return lhs.w+lhs.s < rhs.w+rhs.s ;
    }

}cow[MAXN+5];

int n;

int main()
{
    ios::sync_with_stdio(0);    cin.tie(0);

    cin >> n ;

    int totalweight = 0;

    for(int i = 1; i <= n; i++)
        cin >> cow[i].w >> cow[i].s ;

    sort(&cow[1], &cow[n+1], _cow::cmp);

    int risk = (int)0x80000000UL;

    for(int i = 1; i <= n; i++)
    {
        risk = max(risk, totalweight - cow[i].s);
        totalweight += cow[i].w ;
    }

    cout << risk << endl ;
    return 0;
}
/*
bool check(int risk)
{

}

int BinarySearch()
{
    int lb = 0, rb = 1000000005;

    while(lb+1 < rb)
    {
        int mid = (lb+rb) >> 1 ;
        if(check(mid))
            rb = mid;
        else
            lb = mid;
    }

    return rb;
}
*/
