#include <algorithm>
#include <iostream>
#include <iterator>
//#include <cassert>
#include <cstring>
#include <cstdio>
#include <vector>
#include <cmath>

using namespace std;

const int MAXN = 200000 + 5;
const int LOG = 20;

struct Edge
{
    int v, w;
    Edge() {};
    Edge(int _v, int _w) :
        v(_v), w(_w) {};

    static bool cmp(const Edge & lhs, const Edge & rhs)
    {
        return lhs.w < rhs.w ;
    }
};
struct biEdge:
    Edge
{
    int u, id;
    biEdge(int _u, int _v, int _w, int _id) :
        Edge(_v, _w), u(_u), id(_id) {};

};
class disjointSet
{
    const static int MAXN = ::MAXN;
    int fa[MAXN];
public:
    disjointSet()
    {
        for (int i = 0; i < MAXN; i++)
            fa[i] = i;
    }

    // With compression
    int find(int x)
    {
        if (x == fa[x])
            return x;
        return fa[x] = find(fa[x]);
    }

    void unite(int x, int y)
    {
        fa[find(x)] = find(y);
    }
};

typedef vector<biEdge> krsklEdgeVec;
typedef vector<Edge> edgeVec;

long long sum, ans[MAXN];
int N, M;
bool used[MAXN];
edgeVec Adj[MAXN];
krsklEdgeVec vecEdge;
disjointSet dS;

int dep[MAXN], fa[MAXN][LOG], mx[MAXN][LOG];

void DFSinit(int cur, int far, int dpt)
{
    dep[cur] = dpt;
    fa[cur][0] = far;

    for (edgeVec::iterator itr = Adj[cur].begin(); itr != Adj[cur].end(); itr++)
    {
        int & v = itr->v;
        if (v == far)
            continue;

        mx[v][0] = itr->w;
        DFSinit(v, cur, dpt + 1);
    }
}

void Init(int N)
{
    for (int k = 1; k < LOG; k++)
    {
        for (int i = 1; i <= N; i++)
        {
            if (fa[i][k - 1] == 0 || fa[fa[i][k - 1]][k - 1] == 0)
                continue;
            fa[i][k] = fa[fa[i][k - 1]][k - 1];
            mx[i][k] = max(mx[i][k-1], mx[fa[i][k - 1]][k - 1]);
        }
    }
}

int findMax(int u, int v)
{
    if(dep[u] > dep[v]) swap(u, v);
    int ret = 0;

    for(int k = LOG-1; k >= 0; k--)
        if(dep[v] - (1 << k) >= dep[u])
            ret = max(ret, mx[v][k]),
            v = fa[v][k];
    if(u == v)
        return ret;

    for(int k = LOG-1; k >= 0; k--)
        if(dep[u] - (1 << k) > 0 && fa[u][k] != fa[v][k])
            ret = max(ret, max(mx[u][k], mx[v][k])),
            v = fa[v][k],
            u = fa[u][k];
    ret = max(ret, max(fa[u][0], fa[v][0]));
    return ret;
}

void AddEdge(int u, int v, int w)
{
    Adj[u].push_back(Edge(v, w));
    Adj[v].push_back(Edge(u, w));
}

void Kruskal()
{
    for (krsklEdgeVec::iterator itr = vecEdge.begin(); itr != vecEdge.end(); itr++)
    {
        int & u = itr->u,
              & v = itr->v,
                & w = itr->w;
        if (dS.find(u) == dS.find(v))
            continue;

        dS.unite(u, v);
        used[itr - vecEdge.begin()] = true;
        sum += w;
        AddEdge(u, v, w);
    }
}


int main()
{
    int u, v, w;
    cin >> N >> M ;
    for (int i = 1; i <= M; i++)
    {
        cin >> u >> v >> w ;
        vecEdge.push_back(biEdge(u, v, w, i));
    }

    sort(vecEdge.begin(), vecEdge.end(), biEdge::cmp);
    Kruskal();

    DFSinit(1, 0, 1);
    Init(N);
/*
    for(int i = 1; i <= N; i++)
    {
        for(int j = 1; j <= N; j++)
            if(i != j)
                cerr << i << " " << j << " : " << findMax(i ,j) << endl ;
    }
*/
    // i is the number of sorted edges
    for(int i = 0; i < M; i++)
    {
        int id = vecEdge[i].id;
        if(used[i])
            ans[id] = sum;
        else
            ans[id] = sum + vecEdge[i].w - findMax(vecEdge[i].u, vecEdge[i].v);
    }

    for(int i = 1; i <= M; i++)
        cout << ans[i] << endl ;
}
