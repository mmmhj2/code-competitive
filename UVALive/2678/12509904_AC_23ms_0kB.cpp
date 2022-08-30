#include <iostream>
#include <cstring>
using namespace std;

const int MAXN = 100000 ;

int a[MAXN+5];
int t, n, s;

int main()
{
    ios::sync_with_stdio(0);    cin.tie(0);
    //cin >> t ;

    while(cin >> n >> s)
    {
        memset(a, 0x00, sizeof a);

        for(int i = 1; i <= n; i++)
            cin >> a[i];

        int res = n+1;
        int st = 1, ed = 1, sum = 0;

        while(true)
        {
            while(ed <= n && sum < s)
            {
                sum += a[ed++];
            }
            if(sum < s)
                break;
            res = min(res, ed-st);
            sum -= a[st++];
        }

        if(res > n)
            res = 0;
        cout << res << endl;
    }

    return 0;
}
