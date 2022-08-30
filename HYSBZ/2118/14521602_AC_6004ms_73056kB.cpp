#include <iostream>
#include <iomanip>
#include <cstring>
#include <cstdio>
#include <vector>
#include <queue>
#include <stack>
using namespace std;
typedef long long i64;
const int INF = 0x7f7f7f7f;
const int MAXN = 500000 + 10;

struct Edge
{
    int to;
    i64 w;
};
typedef vector<Edge> vEdge;

vEdge Adj[MAXN];
int N;
i64 MINB, MAXB, a[15];
i64 MINA = 0x7fffffffffffffffLL;       // the modular
i64 dist[MAXN]; bool inQueue[MAXN];

void AddEdge(int u, int v, i64 w)
{
    Adj[u].push_back(Edge{v, w});
}

i64 query(i64 lim)
{
    //      k * T + i <= lim
    //  =>  k <= (lim - i) / T
    i64 ans = 0;
    for(int i = 0; i < MINA; i++)
        if(dist[i] <= lim)
            ans += (lim - dist[i]) / MINA + 1;
    return ans;
}

bool SPFA(int st)
{
    memset(dist, 0x7f, sizeof dist);
    memset(inQueue, 0x00, sizeof inQueue);
    queue <int> q;

    q.push(st);
    inQueue[st] = true;
    dist[st] = 0;

    while(!q.empty())
    {
        st = q.front();
        q.pop();    inQueue[st] = false;

        for(vEdge::iterator itr = Adj[st].begin(); itr != Adj[st].end(); itr++)
        {
            int & to = itr->to;
            if(dist[to] > dist[st] + itr->w)
            {
                dist[to] = dist[st] + itr->w;
                if(!inQueue[to])
                {
                    inQueue[to] = true;
                    q.push(to);
                }
            }
        }
    }
    return true;
}

int main()
{
    cin >> N >> MINB >> MAXB ;
    for(int i = 1; i <= N; i++)
        cin >> a[i], MINA = min(MINA, a[i]);

    for(i64 i = 0; i <= MINA; i++)
        for(i64 j = 1; j <= N; j++)
        {
            AddEdge(i, (i+a[j]) % MINA, a[j]);
        }
    SPFA(0);

    cout << query(MAXB) - query(MINB-1) << endl ;
}
