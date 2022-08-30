#include <algorithm>
#include <iterator>
#include <iostream>
#include <cstring>
#include <string>
#include <vector>
#include <cmath>
#include <set>
using namespace std;

typedef long long i64;
const int MAXN = 100000 + 5;
const int MAXM = 300000 + 5;
// 追踪的祖先(2^DEPTH)个数
const int MAXDEP = 17 + 5;
const i64 INF  = 0x7F7F7F7F7F7F7F7FLL;

struct Edge
{
    int u, v, w;

    static bool SortByWeight(const Edge & lhs, const Edge & rhs)
    {
        return lhs.w < rhs.w;
    }
};
struct sigEdge
{
    int v, w;
};

ostream & operator << (ostream & _out, const sigEdge & out)
{
    _out << "(" << out.v << "," << out.w << ")";
    return _out;
}

typedef vector<Edge> vEdge;
typedef vector<sigEdge> AdjList;
class disjointSet
{
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

i64 ans;
int delta = 0x7FFFFFFF;
int N, M;
disjointSet dS;
vEdge EdgeList;
bool EdgeInTree[MAXM];
AdjList SpanTree[MAXN];

int fa[MAXN][MAXDEP], Max1st[MAXN][MAXDEP], Max2nd[MAXN][MAXDEP];
int depth[MAXN];

void AddEdge(int u, int v, int w)
{
    SpanTree[u].push_back(sigEdge{v, w});
    SpanTree[v].push_back(sigEdge{u, w});
}

void Kruskal()
{
    sort(EdgeList.begin(), EdgeList.end(), Edge::SortByWeight);

    for (vEdge::iterator itr = EdgeList.begin(); itr != EdgeList.end(); itr++)
    {
        int & u = itr->u;
        int & v = itr->v;
        int & w = itr->w;

        if (dS.find(u) != dS.find(v))
            EdgeInTree[itr-EdgeList.begin()] = true,
            dS.unite(u, v),
            ans += w,
            AddEdge(u, v, w);
    }
}

void depthFirstSearchPrepare(int cur)
{
    int cmp1, cmp2, cmp3, cmp4;
    for(int i = 1; i < MAXDEP; i++)
    {
        fa[cur][i] = fa[fa[cur][i-1]][i-1] ;
        cmp1 = Max1st[cur][i-1], cmp2 = Max1st[fa[cur][i-1]][i-1],
        cmp3 = Max2nd[cur][i-1], cmp4 = Max2nd[fa[cur][i-1]][i-1];
        Max1st[cur][i] = max(cmp1, cmp2);
        Max2nd[cur][i] = max(cmp3, cmp4);
        if(cmp1 != cmp2)
            Max2nd[cur][i] = max(Max2nd[cur][i], min(cmp1, cmp2));
    }

    for(AdjList::iterator itr = SpanTree[cur].begin(); itr != SpanTree[cur].end(); itr++)
    {
        int & to = itr->v;
        if(to == fa[cur][0])
            continue;

        depth[to] = depth[cur] + 1;
        fa[to][0] = cur;
        Max1st[to][0] = itr->w;
        depthFirstSearchPrepare(to);
    }
}

int LCA(int x, int y)
{
    if(depth[x] < depth[y])
        swap(x, y);

    int h = depth[x] - depth[y];
    for(int i = MAXDEP-1; i >= 0 && h; i--)
        if(h & (1 << i))
            x = fa[x][i];
    if(x == y)
        return x;

    for(int i = 18; i >= 0; i--)
        if(fa[x][i] != fa[y][i])
            x = fa[x][i], y = fa[y][i];
    return fa[x][0];
}

int getDelta(int u, int v, int oldW)
{
    int max1 = 0, max2 = 0;

    int h = depth[u] - depth[v];
    for(int i = MAXDEP-1; i >= 0; i--)
        if(h & (1 << i))
        {
            if(Max1st[u][i] > max1)
                max2 = max1, max1 = Max1st[u][i];
            max2 = max(max2, Max2nd[u][i]);
            h -= (1 << i);
        }

    if(oldW == max1)
        return (delta = min(delta, oldW - max2));
    return (delta = min(delta, oldW - max1));
}

void Solve(int x)
{
    const int   u1 = EdgeList[x].u,
                u2 = EdgeList[x].v,
                v = LCA(u1, u2),
                w = EdgeList[x].w;
    getDelta(u1, v, w),
    getDelta(u2, v, w);
}

int main()
{
    int u, v, w;
    cin >> N >> M ;

    for(int i = 1; i <= M; i++)
    {
        cin >> u >> v >> w ;
        EdgeList.push_back(Edge{u, v, w});
    }

    Kruskal();
/*
    cerr << "Minimal Spanning Tree : " << ans << endl ;
    for(int i = 1; i <= N; i++)
    {
        cerr << i << " : " ;
        copy(SpanTree[i].begin(),
             SpanTree[i].end(),
             ostream_iterator<sigEdge>(cerr, " "));
        cerr << endl ;
    }
*/
    depthFirstSearchPrepare(1);
/*
    cerr << "After Preparation : " << endl ;
    for(int i = 1; i <= N; i++)
    {
        cerr << i << " : " << endl ;
        cerr << "Father : " ;
        for(int j = 0; j < MAXDEP; j++)
            cerr << fa[i][j] << " " ;
        cerr << endl ;
        cerr << "Max 1st : " ;
        for(int j = 0; j < MAXDEP; j++)
            cerr << Max1st[i][j] << " " ;
        cerr << endl ;
        cerr << "Max 2nd : " ;
        for(int j = 0; j < MAXDEP; j++)
            cerr << Max2nd[i][j] << " " ;
        cerr << endl ;
        cerr << "Depth : " << depth[i] << endl ;
    }
*/
    for(int i = 0;i < M; i++)
        if(!EdgeInTree[i])
        {
            //cerr << "Edge " << i+1 << " is being checked " << endl ;
            Solve(i);
        }

    cout << ans + delta << endl ;
    return 0;
}
