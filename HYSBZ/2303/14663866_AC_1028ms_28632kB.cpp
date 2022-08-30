#include <algorithm>
#include <iterator>
#include <iostream>
//#include <iomanip>
//#include <cstring>
//#include <cstdlib>
#include <string>
#include <vector>
//#include <queue>
//#include <cmath>
//#include <set>
using namespace std;

#define GETY(y) (Y[y]+N)
#define GETX(x) (X[x])

#ifdef LOCAL
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
#define DEBUGVAR(x)
#define DEBUGARR(l, r)
#endif // LOCAL

const int MOD = 1000000000;
const int MAXN = 1000000 + 5;
typedef struct
disjointSet_Alter{
    int fa[MAXN*2+20];
    int col[MAXN*2+20];

    void clear(int N)
    {
        for(int i = 1; i <= N; i++)
            fa[i] = i, col[i] = 0;
    }

    disjointSet_Alter()
    {
    }

    disjointSet_Alter(int N)
    {
        clear(N);
    }

    int find(int x)
    {
        if(fa[x] == x)
            return x;
        int f = find(fa[x]);
        col[x] ^= col[fa[x]];
        return fa[x] = f;
    }

    void unite(int x, int y)
    {
        fa[x] = y;
    }
}DSU, *pDSU;

disjointSet_Alter dS(MAXN);
int N, M, K;
int ans ;
int X[MAXN], Y[MAXN], C[MAXN];

int getSolution()
{
    dS.clear(N + M);
    dS.fa[1+N] = dS.fa[1] = 1;
    for(int i = 1; i <= K; i++)
    {
        int u = dS.find(GETX(i)),
            v = dS.find(GETY(i));
        int nc = dS.col[GETX(i)] ^ dS.col[GETY(i)] ^ C[i];
        DEBUGVAR(dS.col[GETX(i)]);
        DEBUGVAR(dS.col[GETY(i)]);
        DEBUGVAR(C[i]);
        DEBUGVAR(u);
        DEBUGVAR(v);

        if(u != v)
            //dS.unite(u, v),
            dS.fa[u] = v,
            dS.col[u] = nc;
        else if(nc)
            return 0;
    }

    int sum = -1;
    for(int i = 1 ; i <= N + M; i++)
        if(dS.find(i) == i)
        {
            if(sum < 0)
                sum = 1;
            else
            {
                sum <<= 1;
                if(sum > MOD)
                    sum -= MOD;
            }
        }
    DEBUGVAR(sum);
    return sum ;
}

int main()
{
    bool Lock0 = true,
         Lock1 = true;
    cin >> N >> M >> K ;

    for(int i = 1; i <= K; i++)
    {
        cin >> X[i] >> Y[i] >> C[i];
        if(X[i] == 1 && Y[i] == 1)
        {
            if(C[i] == 0)
                Lock1 = false;
            if(C[i] == 1)
                Lock0 = false;
            // Ignore this case
            i--, K--;
            continue;
        }
        if(!((X[i] & 1) || (Y[i] & 1)))
            C[i] = !C[i];
    }
    DEBUGARR(&C[1], &C[K+1])
    DEBUGVAR(Lock0);
    DEBUGVAR(Lock1);

    if(Lock0)
    {
        ans += (getSolution() % MOD);
    }
    if(Lock1)
    {
        // Invert all colors
        for(int i = 1; i <= K; i++)
            if(X[i] != 1 && Y[i] != 1)
                C[i] = !C[i];
        ans = (ans+getSolution()) % MOD;
    }
    cout << ans << endl ;
}

