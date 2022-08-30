#include <iostream>
#include <algorithm>

using namespace std;

const int MAXN = 100000;

int n, c;
int loc[MAXN+5];

bool check(int);
int BinarySearch(void);

int main()
{
    //ios::sync_with_stdio(false);
    //cin.tie(0);

    cin >> n >> c ;

    for(int i = 1; i <= n; i++)
        cin >> loc[i] ;

    sort(&loc[1], &loc[n]);

    cout << BinarySearch() << endl ;
}

bool check(int dist)
{
    int lastcowpos = 1;

    for(int i = 2; i <= c; i++)
    {
        int curpos;
        for(curpos = lastcowpos+1; curpos <= n; curpos++)
        {
            if(loc[curpos] - loc[lastcowpos] >= dist)
                break;
        }
        if(curpos > n)
            return false;
        lastcowpos = curpos ;
    }
    return true;
}

int BinarySearch(void)
{
    int lb = 0, rb = loc[n] + 1;

    while(lb + 1 < rb)
    {
        int mid = (lb+rb) >> 1 ;
        if(check(mid)) lb = mid;
        else rb = mid;
    }

    return lb ;
}
