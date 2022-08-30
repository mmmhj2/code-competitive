#include <algorithm>
#include <iostream>
#include <iterator>
#include <cstdio>
#include <vector>
#include <cmath>
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

using i64 = long long;

const int MAXN = 100000 + 5 ;
const int INF = 0x7FFFFFFF;

bool noSolution;
int N, K;
pair <int, int> pnt[MAXN];
struct node
{
    int l, r, oe;
}rng[MAXN];
vector <int> Adj[MAXN];

void DFSPushUp(int x, int fa)
{
    if(noSolution)
        return ;
    for(int & to : Adj[x])
    {
        if(to == fa)
            continue;
        DFSPushUp(to, x);

        int l = rng[to].l-1, r = rng[to].r+1;

        if(rng[to].oe != -1)
        {
            if(rng[x].oe == -1)
                rng[x].oe = rng[to].oe ^ 1;
            else if(rng[x].oe == rng[to].oe)
            {
                //cerr << "Interrupted Pushup 1:" << x << " " << fa << endl ;
                noSolution = true;
            }

        }

        rng[x].l = max(rng[x].l, l);
        rng[x].r = min(rng[x].r, r);

        if(rng[x].l > rng[x].r)
        {
            //cerr << "Interrupted Pushup 2:" << x << " " << fa << endl ;
            noSolution = true;
        }

    }
}

void DFSPushDown(int x, int fa)
{
    if(noSolution)
        return;
    if(fa)
    {
        int l = rng[fa].l-1, r = rng[fa].r+1;
        if(rng[fa].oe != -1)
        {
            if(rng[x].oe == -1)
                rng[x].oe = rng[fa].oe ^ 1;
            else if(rng[fa].oe == rng[x].oe)
            {
                //cerr << "Interrupted Pushdown 1: " << x << " " << fa << endl ;
                noSolution = true;
            }

        }
        rng[x].l = max(rng[x].l, l);
        rng[x].r = min(rng[x].r, r);
    }
    if(rng[x].l > rng[x].r)
    {
        //cerr << "Interrupted Pushdown 2: " << x << " " << fa << endl ;
        noSolution = true;
    }


    for(int & to : Adj[x])
        if(to != fa)
            DFSPushDown(to, x);
}

int main()
{
    int u, v, w;
    cin >> N ;

    for(int i = 1; i < N; i++)
        cin >> u >> v ,
        Adj[u].push_back(v),
        Adj[v].push_back(u);

    cin >> K ;
    for(int i = 1; i <= N; i++)
        rng[i].l = 0x80808080, rng[i].r = 0x7F7F7F7F, rng[i].oe = -1;
    for(int i = 1; i <= K; i++)
    {
        cin >> pnt[i].first >> pnt[i].second ;
        rng[pnt[i].first].l = pnt[i].second ;
        rng[pnt[i].first].r = pnt[i].second;
        rng[pnt[i].first].oe = pnt[i].second & 1;
    }

    DFSPushUp(1, 0);
    DFSPushDown(1, 0);

    if(noSolution)
        puts("No");
    else
    {
        puts("Yes");
        for(int i = 1; i <= N; i++)
            cout << rng[i].l << endl ;
    }

    return 0;
}
