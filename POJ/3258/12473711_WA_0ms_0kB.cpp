#include <iostream>
#include <algorithm>
using namespace std;

const int MAXN = 50005;

int stone[MAXN+5];
int n, m;

int check(int tardist);
int BinarySearch(void);

int main()
{
    ios::sync_with_stdio(0);
    cin >> stone[2] >> n >> m;
    for(int i = 3; i <= n+2; i++)
        cin >> stone[i];
    n += 2;
    sort(&stone[1], &stone[n]);

    cout << BinarySearch() << endl ;
}

int check(int tardist)
{
    int cnt(0), pre(1);

    for(int i = 2; i <= n; i++)
    {
        if(stone[i]-stone[pre] >= tardist)
            // Keep stone i
            pre = i;
        else
            //Remove stone i
            cnt++;
    }

    if(cnt <= m)
        return true;
    return false;
}

int BinarySearch(void)
{
    int lb = 0 , rb = 2*m;

    while(lb+1 < rb)
    {
        int mid = (rb+lb) >> 1;

        if(check(mid))
            lb = mid;
        else
            rb = mid;
    }
    return rb;
}
