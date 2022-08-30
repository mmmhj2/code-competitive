#include <algorithm>
#include <iostream>
#include <vector>
#include <map>
using namespace std;

#ifdef LOCAL
#include <iterator>
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

using i64 = long long ;
const int MAXN = 500000 + 5;
const int INF  = 0x7F7F7F7F;

struct Edge
{
    int to, id;
};

int N, MAX, curDep;

int EdgeCnt = 0;
vector <Edge> Adj[MAXN];
char ch[MAXN];
int sonCnt[MAXN], maxSon[MAXN], depth[MAXN], stage[MAXN];
int stCnt[(1 << 22) + 5], ans[MAXN];

inline void AddEdge(int fa, int ch)
{
    Adj[fa].push_back(Edge{ch, ++EdgeCnt});
}

void enumSon(int cur)
{
    sonCnt[cur] = 1;

    for(vector<Edge>::iterator itr = Adj[cur].begin(); itr != Adj[cur].end(); itr++)
    {
        const int & to = itr->to;
        //if(to == fa)    continue;

        depth[to] = depth[cur] + 1;
        stage[to] = stage[cur] ^ (1 << ch[to]);
        enumSon(to);
        sonCnt[cur] += sonCnt[to];

        if(sonCnt[to] > sonCnt[maxSon[cur]])
            maxSon[cur] = to;
    }
}

inline void enumStage(int cur)
{
    if(stCnt[stage[cur]])
        MAX = max(MAX, depth[cur] - curDep*2 + stCnt[stage[cur]]);

    for(int i = 0; i < 22; i++)
        if(stCnt[stage[cur] ^ (1 << i)])
            MAX = max(MAX, depth[cur] - curDep*2 + stCnt[stage[cur] ^ (1 << i)]);
}

void updateSubtree(int x)
{
    enumStage(x);

    for(vector<Edge>::iterator itr = Adj[x].begin(); itr != Adj[x].end(); itr++)
        updateSubtree(itr->to);
}

void updateStCnt(int x)
{
    stCnt[stage[x]] = max(stCnt[stage[x]], depth[x]);
}

void insertSubtree(int x)
{
    updateStCnt(x);
    for(vector<Edge>::iterator itr = Adj[x].begin(); itr != Adj[x].end(); itr++)
        insertSubtree(itr->to);
}

void eraseSubtree(int x)
{
    stCnt[stage[x]] = 0;
    for(vector<Edge>::iterator itr = Adj[x].begin(); itr != Adj[x].end(); itr++)
        eraseSubtree(itr->to);
}

void DFS(int cur, bool notRecover = true)
{
    for(vector<Edge>::iterator itr = Adj[cur].begin(); itr != Adj[cur].end(); itr++)
        if(itr->to != maxSon[cur])
            DFS(itr->to, false);
    if(maxSon[cur])
        DFS(maxSon[cur]);
    curDep = depth[cur];

    for(vector<Edge>::iterator itr = Adj[cur].begin(); itr != Adj[cur].end(); itr++)
        ans[cur] = max(ans[cur], ans[itr->to]);
    for(vector<Edge>::iterator itr = Adj[cur].begin(); itr != Adj[cur].end(); itr++)
        if(itr->to != maxSon[cur])
            updateSubtree(itr->to),
            insertSubtree(itr->to);
    enumStage(cur), updateStCnt(cur);
    ans[cur] = max(ans[cur], MAX);

    if(!notRecover)
        eraseSubtree(cur),
        MAX = 0;
}


int main()
{
    int u, v;
    cin >> N ;

    for(int i = 2; i <= N; i++)
        cin >> u >> ch[i] ,
        ch[i] -= 'a',
        AddEdge(u, i);

    enumSon(1);

    DEBUGARR(&depth[1], &depth[N+1]);
    DEBUGARR(&sonCnt[1], &sonCnt[N+1]);
    DEBUGARR(&stage[1], &stage[N+1]);
    DEBUGARR(&maxSon[1], &maxSon[N+1]);

    DFS(1);

    for(int i = 1; i <= N; i++)
        cout << ans[i] << " " ;
    cout << endl ;

    return 0;
}
