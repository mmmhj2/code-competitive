#include <iostream>
#include <cstring>
#include <vector>
#include <queue>
using namespace std;

const int MAXV = 100000 + 5;
const int MAXN = 1000 + 5;

struct _edge
{
    int to, w;
};
typedef vector<_edge> EdgeTable;
EdgeTable For[MAXV], Rev[MAXV];

struct node
{
    int f, g;
    int id;
    node(){};
    node(int id, int f, int g)
    {
        node::id = id;
        node::f = f;
        node::g = g;
    }
    bool operator < (const node & rhs) const
    {
        return ((this->f == rhs.f) ? (this->g > rhs.g) : (this->f > rhs.f));
    }
};

bool InQueue[MAXN]; int Dist[MAXN];
int n, m, s, t, k;

void AddEdge(int u, int v, int w)
{
    For[u].push_back((_edge){v, w});
    Rev[v].push_back((_edge){u, w});
}

void SPFA(int t)
{
    memset(Dist, 0x7f, sizeof Dist);
    memset(InQueue, 0x00, sizeof InQueue);
    Dist[t] = 0;    InQueue[t] = true;
    queue <int> q;
    q.push(t);
    while(!q.empty())
    {
        int to = q.front(); q.pop();
        InQueue[to] = false;

        for(EdgeTable::iterator itr = Rev[to].begin(); itr != Rev[to].end(); itr++)
            if(Dist[itr->to] > Dist[to] + itr->w)
            {
                Dist[itr->to] = Dist[to] + itr->w;
                if(!InQueue[itr->to])
                {
                    InQueue[itr->to] = true;
                    q.push(itr->to);
                }
            }
    }
}

int Astar(int S, int T, int K)
{
    int cnt = 0;
    if(S == T)
        K++;
    if(Dist[S] == 0x7f7f7f7f)
        return 0xffffffff;
    priority_queue <node> pq;
    pq.push((node){S, 0, 0});

    while(!pq.empty())
    {
        node cur = pq.top();
        pq.pop();
        if(cur.id == T)
            if(++cnt == K)
                return cur.f;
        for(EdgeTable::iterator itr = For[cur.id].begin(); itr != For[cur.id].end(); itr++)
        {
            int h = Dist[itr->to], g = cur.g + itr->w;
            pq.push((node){itr->to, h + g, g});
        }
    }
    return -1;
}

int main()
{
    cin >> n >> m ;
    for(int i = 1; i <= m; i++)
    {
        int u, v, w;
        cin >> u >> v >> w ;
        AddEdge(u, v, w);
    }
    cin >> s >> t >> k ;
    SPFA(t);
    cout << Astar(s, t, k) << endl ;
}
