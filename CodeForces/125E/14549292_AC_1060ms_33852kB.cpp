#include <algorithm>
#include <iterator>
#include <iostream>
#include <cstring>
#include <string>
#include <vector>
#include <set>
using namespace std;

struct Edge
{
    int u, v, w, id;

    static bool SortByWeight(const Edge & lhs, const Edge & rhs)
    {
        return lhs.w < rhs.w;
    }
};
struct sigEdge
{
    int v, w, id;
};
typedef vector<Edge> vEdge;
typedef vector<sigEdge> AdjList;

class disjointSet
{
    const static int MAXN = 5000 + 5;
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

const int MAXN = 5000 + 10;
const int INF  = 0x7F7F7F7F;

disjointSet dS, connectivityCheck;
int ans;
int N, M, K, connected;
vEdge EdgeList;
Edge DP[MAXN];
//int G[MAXN][MAXN];
AdjList Adj[MAXN];
bool Forest[MAXN][MAXN], has_Sol = true;
set <int> chosen;

void Kruskal()
{
    sort(EdgeList.begin(), EdgeList.end(), Edge::SortByWeight);

    for (vEdge::iterator itr = EdgeList.begin(); itr != EdgeList.end(); itr++)
    {
        int & u = itr->u;
        int & v = itr->v;
        int & w = itr->w;

        if (dS.find(u) != dS.find(v))
        {
            dS.unite(u, v);
            Forest[u][v] = true;
            Forest[v][u] = true;
            chosen.insert(itr->id);
        }
    }
}

void ExpandRootToBlk()
{
    int chosenPoint[MAXN];
    int chosenEdge[MAXN];
    int chosenEdgeId[MAXN];
    memset(chosenEdge, 0x7f, sizeof chosenEdge);

    for (AdjList::iterator itr = Adj[1].begin(); itr != Adj[1].end(); itr++)
    {
        int & to = itr->v;
        int curBlk = dS.find(to);

        if (chosenEdge[curBlk] > itr->w)
        {
            chosenEdgeId[curBlk] = itr->id;
            chosenEdge[curBlk] = itr->w;
            chosenPoint[curBlk] = to;
        }
    }

    for (int i = 1; i <= N; i++)
    {
        if (chosenEdge[i] < 0x7f7f7f7f)
        {
            connected++;
            Forest[1][chosenPoint[i]] = true;
            Forest[chosenPoint[i]][1] = true;
            chosen.insert(chosenEdgeId[i]);
        }
    }

    //cerr << "Spanning Forest Generated, Stage : " << connected << endl ;
    //copy(chosen.begin(), chosen.end(), ostream_iterator<int>(cerr, " "));
    //cerr << endl ;
}

// 树上DP
void DFS(int cur, int fa)
{
    for (AdjList::iterator itr = Adj[cur].begin(); itr != Adj[cur].end(); itr++)
    {
        int & t = itr->v;
        if (t == fa || !Forest[cur][t])
            continue;
        if (DP[t].w == -1)
        {
            if (DP[cur].w > itr->w)
                DP[t] = DP[cur];
            else
                DP[t].u = cur,
                      DP[t].v = t,
                            DP[t].w = itr->w,
                                  DP[t].id = itr->id;
        }

        DFS(t, cur);
    }
}

// 由最小m度限制生成树得到最小m+1度限制生成树。
void ExpandRootFinal()
{
    //cerr << "Connected : " << connected << endl ;
    if (connected > K)
    {
        has_Sol = false;
        return ;
    }
    for (int i = connected + 1; i <= K; i++)
    {
        // 未计算的边记为 -1(0xFFFFFFFF)
        memset(DP, 0xFF, sizeof DP);
        // 边界条件 dp[v0]=-∞ ,dp[v’]=-∞|(v0,v’)∈E(T);
        DP[1].w = -INF;
        for (int j = 2; j <= N; j++)
            if (Forest[1][j])
                DP[j].w = -INF;

        DFS(1, 0);

        //枚举所有和V0相邻点v,找到替换后,增加权值最小的一次替换(如果找不到这样的边,就说明已经求出)
        int minid, minto, minAdd(INF);
        for (AdjList::iterator itr = Adj[1].begin(); itr != Adj[1].end(); itr++)
            if (minAdd > itr->w - DP[itr->v].w)
            {
                minAdd = itr->w - DP[itr->v].w;
                minto = itr->v;
                minid = itr->id;
            }

        Forest[minto][1] = Forest[1][minto] = 1;
        Forest[DP[minto].u][DP[minto].v] = 0;
        Forest[DP[minto].v][DP[minto].u] = 0;
        chosen.erase(DP[minto].id);
        chosen.insert(minid);

        //cerr << "Replace Edge " << DP[minto].id << " -> " << minid << endl ;

        //cerr << "Spanning Forest Generated, Stage : " << i << endl ;
        //copy(chosen.begin(), chosen.end(), ostream_iterator<int>(cerr, " "));
        //cerr << endl ;
    }
}

int main()
{
    int u, v, w;
    cin >> N >> M >> K ;

    for (int i = 1; i <= M; i++)
    {
        cin >> u >> v >> w ;
        //G[u][v] = G[v][u] = w;
        Adj[u].push_back(sigEdge{v, w, i});
        Adj[v].push_back(sigEdge{u, w, i});
        connectivityCheck.unite(u, v);
        if (u == 1 || v == 1)
            continue;
        EdgeList.push_back(Edge{u, v, w, i});
    }

    for (int i = 1; i < N; i++)
        if (connectivityCheck.find(u) != connectivityCheck.find(v))
        {
            has_Sol = false;
            break;
        }

    if (has_Sol)
        Kruskal(),
                ExpandRootToBlk(),
                ExpandRootFinal();

    if (has_Sol)
    {
        cout << chosen.size() << endl ;
        copy(chosen.begin(), chosen.end(), ostream_iterator<int>(cout, " "));
    }
    else
        cout << -1 << endl ;
    return 0;
}
