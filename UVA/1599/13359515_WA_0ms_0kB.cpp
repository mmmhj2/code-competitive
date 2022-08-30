#include <iostream>
#include <iterator>
//#include <fstream>
#include <cstring>
#include <vector>
#include <queue>
using namespace std;
const int MAXN = 100005;
struct _edge
{
    int to, colour;
    _edge(int _to = 0, int _colour = 0)
    {
        to = _to;
        colour = _colour;
    }
};
typedef vector<_edge> EdgeTable;
typedef vector<_edge> AdjTable[MAXN];
typedef bool VisTable[MAXN];

int n, m;
AdjTable Adj;
VisTable vist, InQueue;
int dist[MAXN], ans[MAXN];

void DistBFS(int start)
{
    queue <int> q;

    memset(dist, 0x7F, sizeof dist);
    memset(vist, 0x00, sizeof vist);
    memset(InQueue, 0x00, sizeof InQueue);
    dist[start] = 0;    InQueue[start] = true;
    q.push(start);

    while(!q.empty())
    {
        int cur = q.front();
        q.pop();    InQueue[cur] = false;

        for(EdgeTable::iterator itr = Adj[cur].begin(); itr != Adj[cur].end(); itr++)
        {
            const int & to = itr->to;
            if(dist[to] > dist[cur] + 1)
            {
                dist[to] = dist[cur] + 1;
                if(!InQueue[to])
                    q.push(to);
            }
        }
    }
}

void ColourBFS(int finish)
{
    queue <int> q;

    memset(InQueue, 0x00, sizeof InQueue);
    memset(vist, 0x00, sizeof vist);
    InQueue[1] = vist[1] = 1;
    q.push(1);

    while(!q.empty())
    {
        int cur = q.front();
        q.pop();
        // Do not reset in-queue marks
        vist[cur] = true;
        if(cur == finish)
            return;

        int minCol = 0x7fffffff;
        EdgeTable::iterator itr;
        for(itr = Adj[cur].begin(); itr != Adj[cur].end(); itr++)
            //const int & to = itr->to;
            if(!vist[itr->to] && dist[cur]-1 == dist[itr->to])
                minCol = min(minCol, itr->colour);
        for(itr = Adj[cur].begin(); itr != Adj[cur].end(); itr++)
            if(!vist[itr->to] && dist[cur]-1 == dist[itr->to] && !InQueue[itr->to])
                q.push(itr->to), InQueue[itr->to] = true;

        const int index = dist[1] - dist[cur];
        ans[index] = (ans[index] == 0 ? minCol : min(minCol, ans[index]));
    }

}

int main()
{
    //ofstream cout("1.txt");
    cin >> n >> m ;
    for(int i = 1; i <= m; i++)
    {
        int a, b, c;
        cin >> a >> b >> c ;
        if(a == b)  continue;
        Adj[a].push_back(_edge(b, c));
        Adj[b].push_back(_edge(a, c));
    }
    DistBFS(n);
    //copy(&dist[1], &dist[n+1], ostream_iterator<int>(cerr, " "));
    //cerr << endl ;
    ColourBFS(n);
    cout << dist[1] << endl ;
    copy(&ans[0], &ans[dist[1]-1], ostream_iterator<int>(cout, " "));
    cout << ans[dist[1]-1] << endl ;
}
