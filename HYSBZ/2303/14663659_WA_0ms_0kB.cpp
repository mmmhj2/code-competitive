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
    dS.fa[GETY(1)] = dS.fa[GETX(1)] = 1;
    for(int i = 1; i <= K; i++)
    {
        int u = dS.find(GETX(i)),
            v = dS.find(GETY(i));
        int nc = dS.col[GETX(i)] ^ dS.col[GETY(i)] ^ C[i];
        DEBUGVAR(dS.col[GETX(i)]);
        DEBUGVAR(dS.col[GETY(i)]);
        DEBUGVAR(C[i]);

        if(u != v)
            dS.unite(u, v),
            dS.col[u] = nc;
        else if(nc == 1)
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

/*
const int M=2000009,mo=1000000000;
int n,m,i,k,sum,u,v,t,ans,x[M],y[M],z[M],g[M],fa[M];

int read()
{
    int x=0;
    char ch=getchar();
    while (ch<'0' || ch>'9') ch=getchar();
    while (ch>='0' && ch<='9') x=(x<<1)+(x<<3)+ch-48,ch=getchar();
    return x;
}

int getfa(int x)
{
    if (x==fa[x]) return x;
    int t=getfa(fa[x]);    g[x]^=g[fa[x]];
    return fa[x]=t;
}

int wk()
{
    for (i=1;i<=n+m;i++) fa[i]=i,g[i]=0;
    for (fa[n+1]=i=1;i<=k;i++)
    {
        u=getfa(x[i]),v=getfa(y[i]+n),t=g[x[i]]^g[y[i]+n]^z[i];
        DEBUGVAR(g[x[i]]);
        DEBUGVAR(g[y[i]+n]);
        DEBUGVAR(z[i]);
        if (u!=v) fa[u]=v,g[u]=t;
        else if (t) return 0;
    }
    for (sum=-1,i=1;i<=n+m;i++)
        if (getfa(i)==i)
            if (sum==-1) sum=1;
            else if ((sum<<=1)>=mo) sum-=mo;
    return sum;
}

int main()
{
    bool flag[2]={1,1};
    n=read(),m=read(),k=read();
    for (i=1;i<=k;i++)
    {
        x[i]=read(),y[i]=read(),z[i]=read();
        if (x[i]+y[i]==2) { flag[z[i]]=0,i--,k--; continue; }
        if (!((x[i]|y[i])&1)) z[i]^=1;
    }
    if (flag[1]) ans=wk();
    if (flag[0])
    {
        for (i=1;i<=k;i++)
            if (x[i]>1 && y[i]>1) z[i]^=1;
        if ((ans+=wk())>=mo) ans-=mo;
    }
    printf("%d\n",ans);
    return 0;
}
*/
