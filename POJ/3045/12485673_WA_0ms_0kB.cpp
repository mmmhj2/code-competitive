#include <cmath>
#include <iostream>
#include <algorithm>
using namespace std;

const int MAXN = 50000;

struct _cow
{
    int w, s, sum;

    static int cmp (const _cow & lhs, const _cow & rhs)
    {
        return lhs.sum < rhs.sum ;
    }

}cow[MAXN+5];

int n;

//bool check(int );
//int BinarySearch();

int main()
{
    ios::sync_with_stdio(0);    cin.tie(0);

    cin >> n ;
    for(int i = 1; i <= n; i++)
    {
        cin >> cow[i].w >> cow[i].s ;
        cow[i].sum = cow[i].w + cow[i].s ;
    }

    sort(&cow[1], &cow[n+1], _cow::cmp);

    int totw = 0, risk = 0;
    for(int i = 1; i <= n; i++)
    {
        risk = max(risk, totw-cow[i].s);
        totw += cow[i].w;
    }

    cout << risk << endl ;
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
