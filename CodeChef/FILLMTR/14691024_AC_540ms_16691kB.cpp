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

struct disjointSet_weighted
{
    int fa[MAXN];
    int diff[MAXN];

    void clear(int N)
    {
        for(int i = 0; i <= N; i++)
            fa[i] = i, diff[i] = 0;
    }

    int find(int x)
    {
        if(x == fa[x])
            return x;
        int t = fa[x];
        fa[x] = find(fa[x]);
        diff[x] ^= diff[t];
        return fa[x];
    }

    void merge(int u, int v, int w)
    {
        int fu = find(u), fv = find(v);
        if(fu == fv)
            return ;
        fa[fu] = fv;
        diff[fu] = w ^ diff[u] ^ diff[v];
    }
}dSW;

int T, N, Q;

int main()
{
    cin >> T ;
    while(T--)
    {
        bool noSol = false;
        cin >> N >> Q ;
        dSW.clear(N);
        while(Q--)
        {
            int u, v, w;
            cin >> u >> v >> w ;
            if(dSW.find(u) != dSW.find(v))
                dSW.merge(u, v, w);
            else
                if(dSW.diff[u] ^ dSW.diff[v] ^ w)
                    noSol = true;
        }

        if(noSol)
            cout << "no" << endl ;
        else
            cout << "yes" << endl ;
    }
}


