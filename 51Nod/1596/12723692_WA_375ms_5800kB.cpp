#include <iostream>
#include <algorithm>
#include <utility>
//#include <bitset>
using namespace std;
const int MAXN = 1000000;

int n, ans, t;
int cnt[MAXN*2+5];
//bitset <MAXN*2> bs;
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    
    cin >> n;
    for(int i = 1; i <= n; i++)
        cin >> t, \
        cnt[t]++;
    for(int i = 1; i <= 2*MAXN; i++)
    {
        if(cnt[i] == 0 && i > MAXN)
            break;
        cnt[i+1] += cnt[i] / 2;
        cnt[i] &= 1;
        if(cnt[i] == 1)
            ans++;
    }
    cout << ans << endl;
}
