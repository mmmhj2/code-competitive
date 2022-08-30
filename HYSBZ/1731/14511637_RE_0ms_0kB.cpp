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
const int MAXN = 1000;

vEdge Adj[MAXN];
int N, MLike, MDislike;
int dist[MAXN], vist[MAXN];
bool inQueue[MAXN];

// Constrain : x[v] - x[u] <= k[w]
void AddConstrain(int u, int v, int w)
{
    Adj[u].push_back(Edge{v, w});
}

int SPFA(int s)
{
    queue <int> q;
    memset(dist, 0x7f, sizeof dist);
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
            if(dist[to] > dist[cur] + itr->w)
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
    int x, y, d;
    cin >> N >> MLike >> MDislike;

    for(int i = 2; i <= N; i++)
        // x[i-1] <= x[i]
        AddConstrain(i, i-1, 0);

    for(int i = 1; i <= MLike; i++)
    {
        // x[x] - x[y] <= d (x > y)
        cin >> x >> y >> d;
        if(x < y)   swap(x, y);
        AddConstrain(y, x, d);
    }

    for(int i = 1; i <= MDislike; i++)
    {
        // x[x] - x[y] >= d (x > y)
        cin >> x >> y >> d;
        if(x < y)   swap(x, y);
        AddConstrain(x, y, -d);
    }

    if(SPFA(1) < 0)
        cout << "-1" << endl ;
    else
    {
        if(dist[N] >= 0x7f7f7f7f)
            cout << "-2" << endl ;
        else
            cout << dist[N] << endl ;
    }

    return 0;
}
