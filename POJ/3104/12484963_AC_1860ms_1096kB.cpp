#include <cmath>
#include <iostream>
#include <algorithm>
using namespace std;
typedef unsigned long long ui64;
typedef long long int i64;

const int MAXN = 100000;

int n, k, a[MAXN+10];

bool check(int exptime);
i64 BinarySearch(int r);

int main()
{
    ios::sync_with_stdio(0);    cin.tie(0);

    cin >> n ;
    int maxtime = 0;
    for(int i = 1; i <= n; i++)
    {
        cin >> a[i];
        maxtime = max(maxtime, a[i]);
    }

    cin >> k ;

    if(k == 1)
    {
        cout << maxtime << endl;
        return 0;
    }

    cout << BinarySearch(maxtime+5) << endl ;
    return 0;
}

bool check(int exptime)
{
    i64 sum = 0;

    for(int i = 1; i <= n; i++)
        if(a[i] > exptime)
        {
            i64 t = ceil((a[i]-exptime)*1.0/(k-1));
            sum += t;
        }


    if(sum <= exptime)
        return true;
    return false;
}

i64 BinarySearch(int r)
{
    i64 lb = 0, rb = r;

    while(lb+1 < rb)
    {
        i64 mid = (lb+rb) >> 1 ;
        if(check(mid))
            rb = mid;
        else
            lb = mid;
    }

    return rb;
}
