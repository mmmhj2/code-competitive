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
const int MAXN = 100000 + 5;

vEdge Adj[MAXN];
int N, K;
int dist[MAXN], vist[MAXN];
bool inQueue[MAXN];

void AddEdge(int u, int v, int w)
{
    Adj[u].push_back(Edge{v, w});
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
        q.pop();
        inQueue[cur] = false;

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
    cin >> N >> K ;
    while(K--)
    {
        int op, a, b;
        cin >> op >> a >> b ;
        switch(op)
        {
        case 1:
            AddEdge(a, b, 0);
            AddEdge(b, a, 0);
            break;
        case 2:
            if(a == b)
            {
                cout << "-1" << endl ;
                return 0;
            }
            AddEdge(a, b, 1);
            break;
        case 3:
            AddEdge(b, a, 0);
            break;
        case 4:
            if(a == b)
            {
                cout << "-1" << endl ;
                return 0;
            }
            AddEdge(b, a, 1);
            break;
        case 5:
            AddEdge(a, b, 0);
            break;
        }
    }

    for(int i = 1; i <= N; i++)
        AddEdge(0, i, 1);

    if(SPFA(0) < 0)
        cout << "-1" << endl ;
    else
    {
        long long ans = 0;
        for(int i = 1; i <= N; i++)
            ans += dist[i];
        cout << ans << endl ;
    }
    return 0;
}
