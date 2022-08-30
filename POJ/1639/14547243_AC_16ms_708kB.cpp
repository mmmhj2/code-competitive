#include <algorithm>
#include <iterator>
#include <iostream>
#include <cstring>
#include <string>
#include <vector>
#include <map>
using namespace std;

struct Edge
{
    int u, v, w;

    static bool SortByWeight(const Edge & lhs, const Edge & rhs)
    {
        return lhs.w < rhs.w;
    }
};
typedef vector<Edge> vEdge;

class disjointSet
{
    const static int MAXN = 20 + 5;
    int fa[MAXN];
public:
    disjointSet()
    {
        for(int i = 0; i < MAXN; i++)
            fa[i] = i;
    }

    // With compression
    int find(int x)
    {
        if(x == fa[x])
            return x;
        return fa[x] = find(fa[x]);
    }

    void unite(int x, int y)
    {
        fa[find(x)] = find(y);
    }
};

const int MAXN = 20 + 10;
const int INF  = 0x7F7F7F7F;

disjointSet dS;
int ans;
int N, M, K, connected;
vEdge EdgeList;
Edge DP[MAXN];
int G[MAXN][MAXN];
bool Forest[MAXN][MAXN];
map <string, int> nameSet;

void Kruskal()
{
    sort(EdgeList.begin(), EdgeList.end(), Edge::SortByWeight);

    for(vEdge::iterator itr = EdgeList.begin(); itr != EdgeList.end(); itr++)
    {
        int & u = itr->u;
        int & v = itr->v;
        int & w = itr->w;

        if(dS.find(u) != dS.find(v))
        {
            dS.unite(u, v);
            Forest[u][v] = true;
            Forest[v][u] = true;
            ans += w;
        }
    }
}

void ExpandRootToBlk()
{
    int chosenPoint[MAXN];
    int chosenEdge[MAXN];
    memset(chosenEdge, 0x7f, sizeof chosenEdge);

    for(int i = 2; i <= N; i++)
    {
        int curBlk = dS.find(i);
        if(chosenEdge[curBlk] > G[1][i])
        {
            //cerr << "Updated : " << i << " " << curBlk << " " << G[1][i] << endl ;
            chosenEdge[curBlk] = G[1][i];
            chosenPoint[curBlk] = i;
        }
    }

    for(int i = 1; i <= N; i++)
    {
        if(chosenEdge[i] < 0x7f7f7f7f)
        {
            connected++;
            Forest[1][chosenPoint[i]] = true;
            Forest[chosenPoint[i]][1] = true;
            ans += G[1][chosenPoint[i]];
        }
    }
}

// 树上DP
void DFS(int cur, int fa)
{
    for(int i = 2; i <= N; i++)
    {
        if(i == fa || !Forest[cur][i])
            continue;
        if(DP[i].w == -1)
        {
            // dp(v) = max(dp(father(v)),ω(father(v),v))
            if(DP[cur].w > G[cur][i])
                DP[i] = DP[cur];
            else
                DP[i].u = cur,
                DP[i].v = i,
                DP[i].w = G[cur][i];
        }
        DFS(i ,cur);
    }
}

void ExpandRootFinal()
{
    //cerr << "Connected : " << connected << endl ;
    for(int i = connected + 1; i <= K; i++)
    {
        // 未计算的边记为 -1(0xFFFFFFFF)
        memset(DP, 0xFF, sizeof DP);
        // 边界条件 dp[v0]=-∞ ,dp[v’]=-∞|(v0,v’)∈E(T);
        DP[1].w = -INF;
        for(int j = 2; j <= N; j++)
            if(Forest[1][j])
                DP[j].w = -INF;

        DFS(1, 0);

        int minid, minAdd(INF);
        for(int j = 2; j <= N; j++)
            if(minAdd > G[1][j] - DP[j].w)
            {
                minAdd = G[1][j] - DP[j].w;
                minid = j;
            }
        if(minAdd >= 0)
            return;
        Forest[minid][1] = Forest[1][minid] = 1;
        Forest[DP[minid].u][DP[minid].v] = 0;
        Forest[DP[minid].v][DP[minid].u] = 0;

        ans += minAdd;
    }
}

int main()
{
    string n1, n2;
    int u, v, w;
    N = 1;
    nameSet.insert(make_pair("Park", 1));
    memset(G, 0x7f, sizeof G);

    cin >> M ;

    for(int i = 1; i <= M; i++)
    {
        cin >> n1 >> n2 >> w;
        if(!nameSet[n1])
            nameSet[n1] = ++N;
        if(!nameSet[n2])
            nameSet[n2] = ++N;

        u = nameSet[n1], v = nameSet[n2];

        G[u][v] = w;
        G[v][u] = w;

        if(n1 == "Park" || n2 == "Park")
            continue;
        EdgeList.push_back(Edge{u, v, w});
    }
    cin >> K ;

    Kruskal();
    ExpandRootToBlk();
    ExpandRootFinal();

    cout << "Total miles driven: " << ans << endl ;

    return 0;
}
