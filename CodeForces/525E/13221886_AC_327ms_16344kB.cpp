#include <iostream>
#include <map>
using namespace std;

const int MAXN = 25;
typedef long long int i64;
typedef pair<i64, int> pi6i3;
typedef map<pi6i3, int> mappi;

mappi forwd, revse;
i64 Fact[MAXN+5];
int val[MAXN+5];
int n, k;   i64 s;

int DFSF(int cur, i64 sum, int k);
int DFSR(int cur, i64 sum, int k);

inline void getFact()
{
    Fact[0] = Fact[1] = 1;
    for(i64 i = 2; i <= 26; i++)
        Fact[i] = i * Fact[i-1];
}

int main()
{
    getFact();
    cin >> n >> k >> s ;

    for(int i = 1; i <= n; i++)
        cin >> val[i] ;

    DFSF(1, 0, 0);
    DFSR(n/2+1, 0, 0);

    i64 ans = 0;
    mappi::iterator itr;

    for(itr = forwd.begin(); itr != forwd.end(); itr++)
    {
        int cnt = itr->first.second;
        for(int i = 0; i + cnt <= k; i++)
        {
            i64 tmp = s - ((itr->first).first);
            pi6i3 t = make_pair(tmp, i);
            if(revse.count(t))
               ans += ((i64)itr->second) * revse[t];
        }
    }

    cout << ans << endl ;
}

int DFSF(int cur, i64 sum, int k)
{
    if(sum > s)
        return 0;
    if(k > ::k)
        return 0;
    if(cur > n / 2)
    {
        forwd[make_pair(sum, k)]++;
        return 0;
    }
    DFSF(cur+1, sum, k);
    DFSF(cur+1, sum + val[cur], k);

    if(val[cur] <= 19)
        DFSF(cur+1, sum+Fact[val[cur]], k+1);
}

int DFSR(int cur, i64 sum, int k)
{
    if(sum > s)
        return 0;
    if(k > ::k)
        return 0;
    if(cur > n)
    {
        revse[make_pair(sum, k)]++;
        return 0;
    }
    DFSR(cur+1, sum, k);
    DFSR(cur+1, sum + val[cur], k);

    if(val[cur] <= 19)      // Smax < 19!
        DFSR(cur+1, sum+Fact[val[cur]], k+1);
}
