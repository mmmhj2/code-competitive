#include <algorithm>
#include <iterator>
#include <iostream>
//#include <iomanip>
//#include <cstring>
//#include <cstdlib>
#include <cstring>
#include <string>
#include <vector>
#include <queue>
//#include <cmath>
//#include <set>
#include <map>
using namespace std;
#ifdef LOCAL
#define DEBUGMSG()                                                              \
{                                                                               \
    cerr << "[调试 @" << __PRETTY_FUNCTION__ << ":" << __LINE__ << "]" ;        \
}
#define DEBUGVAR(x)                                                             \
{                                                                               \
    cerr << "[调试 @" << __PRETTY_FUNCTION__ << ":" << __LINE__ << "]:" ;       \
    cerr << "([" << typeid(x).name() << "]" << #x << ")" << x << endl ;         \
}
#define DEBUGARR(l, r)                                                          \
{                                                                               \
    cerr << "[调试 @" << __PRETTY_FUNCTION__ << ":" << __LINE__ << "]:" ;       \
    copy(l, r, ostream_iterator<decltype(*l)>(cerr, " "));                      \
    cerr << endl ;                                                              \
}
#else
#define DEBUGMSG()
#define DEBUGVAR(x)
#define DEBUGARR(l, r)
#endif // LOCAL

typedef long long i64 ;
const int MAXN = 100000 + 5;

int N;
i64 ans;

struct disjointSet_weighted
{
    int fa[MAXN];
    i64 sum[MAXN];

    void clear(int N)
    {
        for(int i = 0; i <= N; i++)
            fa[i] = i, sum[i] = 1;
    }

    int find(int x)
    {
        if(x == fa[x])
            return x;
        int t = find(fa[x]);

        sum[t] += sum[x];
        sum[x] = 0;

        return fa[x] = t;
    }

    void merge(int u, int v)
    {
        int fu = find(u),
            fv = find(v);
        if(fu == fv)
            return;
        fa[fu] = fv;
        sum[fv] += sum[fu];
        sum[fu] = 0;
    }
}dSW;

bool is_lucky(int x)
{
    while(x)
    {
        if(x % 10 != 4 && x % 10 != 7)
            return false;
        x /= 10;
    }
    return true;
}


int main()
{
    int u, v, w;
    cin >> N ;
    if(N < 3)
    {
        cout << 0 << endl ;
        return 0;
    }

    dSW.clear(N+1);
    for(int i = 1; i < N; i++)
    {
        cin >> u >> v >> w ;
        if(is_lucky(w))
            continue;

        dSW.merge(u, v);
    }

    for(int i = 1; i <= N; i++)
    {
        if(dSW.find(i) != i)
            continue;

        if(dSW.sum[i] > 2)
            ans += dSW.sum[i] * (dSW.sum[i]-1) * (dSW.sum[i]-2);
        ans += 2LL * dSW.sum[i] * (dSW.sum[i]-1) * (N - dSW.sum[i]);
    }

    ans = 1LL * N * (N-1) * (N-2) - ans;

    cout << ans << endl ;
}


