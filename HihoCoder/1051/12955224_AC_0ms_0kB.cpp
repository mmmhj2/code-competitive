#include <iostream>
#include <cstring>
#include <utility>
#include <vector>
using namespace std;
const int MAXN = 100;

int a[MAXN+5];

int main()
{
    int kase;
    cin >> kase ;
    while(kase--)
    {
        memset(a, 0x00, sizeof a);
        int n, m;
        cin >> n >> m;
        for(int i = 1; i <= n; i++)
            cin >> a[i] ;
        if(n <= m)
            cout << 100 << endl;
        else
        {
            int ans = 0;
            for(int i = m+1; i <= n; i++)
                ans = max (a[i] - a[i-m-1] -1 , ans);
            cout << ans << endl ;
        }
    }
}
