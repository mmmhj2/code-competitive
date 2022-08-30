#include <iostream>
#include <cstring>
#include <vector>
#include <queue>
using namespace std;

struct Edge
{
    int to, w;
};
typedef vector<Edge> vEdge;
const int MAXN = 50000 + 10;

vEdge Adj[MAXN];
int N, MLike, MDislike;
int dist[MAXN], vist[MAXN];
bool inQueue[MAXN];

// Constrain : x[u] - x[v] <= k[w]
void AddConstrain(int u, int v, int w)
{
    Adj[v].push_back(Edge{u, w});
}

int SPFA(int s)
{
    queue <int> q;
    memset(dist, 0x80, sizeof dist);
    memset(vist, 0x00, sizeof vist);
    memset(inQueue, 0x00, sizeof inQueue);

    q.push(s);
    dist[s] = 0;
    vist[s] = 1;
    inQueue[s] = 1;

    while(!q.empty())
    {
        int cur = q.front();
        q.pop();    inQueue[cur] = false;

        for(vEdge::iterator itr = Adj[cur].begin(); itr != Adj[cur].end(); itr++)
        {
            int & to = itr->to;
            if(dist[to] < dist[cur] + itr->w)
            {
                dist[to] = dist[cur] + itr->w;
                if(!inQueue[to])
                {
                    inQueue[to] = true;
                    q.push(to);
                    vist[to]++;
                }
                if(vist[to] > N)
                    return -1;
            }
        }
    }
    return 1;
}

int main()
{
    int a, b, c;
    int Source = 0x7fffffff, Sink = 0;
    cin >> N ;
    for(int i = 1; i <= N; i++)
    {
        cin >> a >> b >> c ;
        b += 1;
        // X[b] - X[a] >= c (Longest Path)
        AddConstrain(b, a, c);
        Source = min(a, Source);
        Sink = max(b, Sink);
    }
    for(int i = Source + 1; i <= Sink; i++)
    {
        // X[i] - X[i-1] >= 0 (Longest Path)
        AddConstrain(i, i-1, 0);
        // X[i-1] - X[i] >= -1(Longest Path)
        AddConstrain(i-1, i, -1);
    }
    SPFA(Source);
    cout << dist[Sink] << endl ;

    return 0;
}
