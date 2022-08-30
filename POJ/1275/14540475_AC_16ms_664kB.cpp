#include <algorithm>
#include <iostream>
#include <cstring>
#include <vector>
#include <queue>
using namespace std;

struct Edge
{
    int to, w;
};
typedef vector <Edge> vEdge;
typedef vEdge::iterator vitr;
const int MAXN = 30;
const int SHIFT = 8;
const int DAY = 24;

int N;
vEdge Adj[MAXN];
bool inQueue[MAXN];
int cnt[MAXN], dist[MAXN];
int R[MAXN], T[MAXN];

// X[u] - X[v] <= A[w]
void addEdge(int u, int v, int w)
{
    Adj[v].push_back(Edge{u, w});
}

void BuildEdge(int lim)
{
    for (int i = 0; i <= 24; i++)
        Adj[i].clear();

    for (int i = 1; i <= 24; i++)
        addEdge(i, i - 1, T[i]),        // X[i] - X[i-1] <= T[i]
                addEdge(i - 1, i, 0);           // x[i] - x[i-1] >= 0  => x[i-1] - x[i] <= 0

    for (int i = 1; i <= 24; i++)
    {
        if (i < 8)
            addEdge(i - SHIFT + DAY, i, lim - R[i]);
        else
            addEdge(i - SHIFT, i, -R[i]);
    }
    addEdge(0, DAY, -lim);
}

bool SPFA(int lim, int src)
{
    queue <int> q;
    memset(cnt, 0x00, sizeof cnt);
    memset(dist, 0x7F, sizeof dist);
    memset(inQueue, 0x00, sizeof inQueue);

    inQueue[src] = 1, cnt[src] = 1;
    dist[src] = 0, q.push(src);

    while (!q.empty())
    {
        src = q.front();
        q.pop();
        inQueue[src] = false;

        for (vitr itr = Adj[src].begin(); itr != Adj[src].end(); itr++)
        {
            const int & to = itr->to;
            if (dist[to] > dist[src] + itr->w)
            {
                dist[to] = dist[src] + itr->w;

                if (!inQueue[to])
                    inQueue[to] = true, q.push(to), cnt[to]++;
                if (cnt[to] > DAY)
                    return false;
            }
        }
    }
    return (lim != dist[DAY]);
}

int BinarySreach()
{
    int l = 0, r = N;
    bool solved = false;

    while (l + 1 < r)
    {
        int mid = (l + r) >> 1;

        BuildEdge(mid);
        if (SPFA(mid, 0))
        {
            solved = true;
            r = mid;
        }
        else
            l = mid;
    }
    if(!solved)
        return -1;
    return r;
}

int main()
{
    int u, kase;
    cin >> kase;

    while (kase--)
    {
        for (int i = 1; i <= 24; i++)
            cin >> R[i] ;
        cin >> N ;
        for (int i = 1; i <= N; i++)
        {
            cin >> u;
            T[++u]++;
        }
        int ans = BinarySreach();
        //cout << (ans < 0 ? "No Solution" : ans) << endl ;
        if(ans < 0)
            cout << "No Solution" << endl ;
        else
            cout << ans << endl ;
    }

    return 0;
}
