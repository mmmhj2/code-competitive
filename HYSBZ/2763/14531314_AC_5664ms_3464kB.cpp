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
const int MAXN = 10000 + 10;
const int MAXK = 10 + 5;

int M, N, K, S, T;
vEdge Adj[MAXN];
bool inQueue[MAXN][MAXK];
int dist[MAXN][MAXK];

void AddEdge(int u, int v, int w)
{
    Adj[u].push_back(Edge{v, w});
    Adj[v].push_back(Edge{u, w});
}

bool SPFA(int src)
{
    queue <pair<int, int> > q;

    memset(dist, 0x7f, sizeof dist);
    memset(inQueue, 0x00, sizeof inQueue);

    dist[src][0] = 0;
    inQueue[src][0] = true;
    q.push(make_pair(src, 0));

    while(!q.empty())
    {
        int cur = q.front().first;
        int k   = q.front().second;
        q.pop();
        inQueue[cur][k] = false;

        for(vEdge::iterator itr = Adj[cur].begin(); itr != Adj[cur].end(); itr++)
        {
            int & to = itr->to;
            if(dist[to][k] > dist[cur][k] + itr->w)
            {
                dist[to][k] = dist[cur][k] + itr->w;
                if(!inQueue[to][k])
                    inQueue[to][k] = true,
                    q.push(make_pair(to, k));
            }

            if(k + 1 <= K)
                if(dist[to][k+1] > dist[cur][k])
                    dist[to][k+1] = dist[cur][k],
                    q.push(make_pair(to, k+1)),
                    inQueue[to][k+1] = true;
        }
    }
    return true;
}

int main()
{
    int u, v, w;
    cin >> N >> M >> K ;
    cin >> S >> T ;
    for(int i = 1; i <= M; i++)
    {
        cin >> u >> v >> w;
        AddEdge(u, v, w);
    }

    SPFA(S);
    cout << dist[T][K] << endl ;
    return 0;
}
