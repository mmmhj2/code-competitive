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
#define DEBUGVAR(x)
#define DEBUGARR(l, r)
#endif // LOCAL
const int MAXN = 100000 + 5;
typedef long long i64;
typedef struct
disjointSet{

    int fa[MAXN+20];
    int rnk[MAXN+20];

    void clear(int N)
    {
        for(int i = 0; i <= N; i++)
            fa[i] = i, rnk[i] = 1;
    }

    disjointSet()
    {
    }

    disjointSet(int N)
    {
        clear(N);
    }

    int getRnk(int x)
    {
        return rnk[find(x)];
    }

    int find(int x)
    {
        if(fa[x] == x)
            return x;
        return fa[x] = find(fa[x]);
    }

    void unite(int x, int y)
    {
        x = find(x), y = find(y);
        if(x != y)
        {
            fa[x] = y;
            rnk[y] += rnk[x];
        }
    }
}CDSU, *pCDSU;


struct Edge
{
    int u, v, w, id;
    bool operator < (const Edge & rhs)  const;
    int getDepth() const;


};
ostream & operator << (ostream & _out, const Edge & e)
{
    _out << "(" << e.u << "," << e.v << "," << e.w << ")" ;
    return _out;
}
typedef vector<Edge> vEdge;

//// !subscript of array sum is the original number
i64 sum[MAXN];
CDSU DSU;
int N, depth[MAXN], tsum[MAXN];
vEdge edge;
vector<int> G[MAXN], ans;

int Edge::getDepth() const
{
    return depth[u];
}

bool Edge::operator < (const Edge & rhs)  const
{
        if(w != rhs.w)
            return w < rhs.w;
        return getDepth() > rhs.getDepth();
}

void DFS(int cu, int fa = 0, int dp = 0)
{
    depth[cu] = dp;
    for(int to : G[cu])
        if(to != fa)
            DFS(to, cu, dp+1);
}

void AddEdge(int u, int v)
{
    G[u].push_back(v);
    G[v].push_back(u);
}

int main()
{
    i64 ansnum = 0;
    int u, v, w;
    cin >> N ;
    DSU.clear(N+1);
    for(int i = 0; i < N-1; i++)
    {
        cin >> u >> v >> w ;
        edge.push_back(Edge{u, v, w, i});
        AddEdge(u, v);
    }

    DFS(1);

    DEBUGARR(&depth[1], &depth[N+1]);

    for(vEdge::iterator itr = edge.begin(); itr != edge.end(); itr++)
        if(depth[itr->u] < depth[itr->v])
            swap(itr->u, itr->v);
    sort(edge.begin(), edge.end());

    DEBUGARR(edge.begin(), edge.end());

    for(int i = 0, k = i; i < N-1; i = k)
    {
        // Seek edges with the same weight
        int j;
        for(j = i; j < N-1 && edge[j].w == edge[i].w; j++)
        {
            DEBUGVAR(edge[i].w);
            DEBUGVAR(edge[j].w);
            tsum[j] = DSU.getRnk(edge[j].u);
            DEBUGVAR(tsum[j]);
            DSU.unite(edge[j].u, edge[j].v);
        }


        for(k = i; k < j; k++)
            sum[edge[k].id] += 2LL * tsum[k] * (DSU.getRnk(edge[k].u) - tsum[k]);
    }
    DEBUGARR(&DSU.rnk[1], &DSU.rnk[N+1]);
    ans.clear();
    for(int i = 0; i < N-1; i++)
    {
        if(ansnum < sum[i])
        {
            ansnum = sum[i];
            ans = {i+1};
        }
        else if(ansnum == sum[i])
            ans.push_back(i+1);
    }

    cout << ansnum << " " << ans.size() << endl ;
    copy(ans.begin(), ans.end(), ostream_iterator<int>(cout, " "));
    cout << endl ;
}



