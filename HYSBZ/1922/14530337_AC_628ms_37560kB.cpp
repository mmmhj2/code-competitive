#include <algorithm>
#include <iostream>
#include <cstring>
#include <queue>
using namespace std;
struct Edge
{
    int to, w;
};
typedef vector<Edge> vEdge;
const int MAXN = 3000 + 10;

int N, M;
int dist1[MAXN], dist2[MAXN];
vEdge Adj[MAXN];
bool vist[MAXN];
int GeneraterPair[MAXN][MAXN];
int BarrierDegree[MAXN];
int GeneraterCnt[MAXN];

struct HeapNode
{
    int dist;       // 距离用于确定堆中的顺序
    int cur;

    bool operator > (const HeapNode & rhs) const
    {
        return dist > rhs.dist;
    }
};

void AddEdge(int u, int v, int w)
{
    Adj[u].push_back(Edge{v, w});
}

void Di_jkstra(int src)
{
    memset(dist1, 0x7f, sizeof dist1);
    dist1[src] = 0;

    priority_queue <HeapNode, vector<HeapNode>, greater<HeapNode> > pq;

    pq.push(HeapNode{dist1[src], src});

    while(!pq.empty())
    {
        int cur = pq.top().cur;
        pq.pop();
        if(vist[cur])
            continue;
        vist[cur] = true;

        int trueDist = max(dist1[cur], dist2[cur]);

        for(vEdge::iterator itr = Adj[cur].begin(); itr != Adj[cur].end(); itr++)
        {
            int & to = itr->to;
            if(trueDist + itr->w < dist1[to])
            {
                dist1[to] = trueDist + itr->w;
                if(!BarrierDegree[to])
                    pq.push(HeapNode{max(dist1[to], dist2[to]), to});
            }
        }

        for(int i = 1; i <= GeneraterCnt[cur]; i++)
        {
            int ProtectedCity = GeneraterPair[cur][i];
            BarrierDegree[ProtectedCity]--;
            dist2[ProtectedCity] = max(dist2[ProtectedCity], trueDist);

            if(!BarrierDegree[ProtectedCity])
                pq.push(HeapNode{max(dist1[ProtectedCity], dist2[ProtectedCity]), ProtectedCity});
        }
    }

}

int main()
{
    int u, v, w;
    cin >> N >> M ;
    for(int i = 1; i <= M; i++)
    {
        cin >> u >> v >> w;
        AddEdge(u, v, w);
    }
    for(int i = 1; i <= N; i++)
    {
        cin >> BarrierDegree[i] ;
        for(int k = 1; k <= BarrierDegree[i]; k++)
        {
            int x;
            cin >> x;
            GeneraterPair[x][++GeneraterCnt[x]] = i;
        }
    }
    Di_jkstra(1);
    cout << max(dist1[N], dist2[N]) << endl ;
}
