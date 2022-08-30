#include <algorithm>
#include <iostream>
#include <cstring>
#include <cstdio>
#include <vector>
#include <queue>
#include <list>
#include <ios>
using namespace std;

struct edge
{
    int to;
    int cost;
};

const int MAXN = 1000l;
const int MAXP = 10000l;
const int MAXL = 1000000l;

vector <edge> Adj[MAXN+5];
int n, p, k;
int dist[MAXN+10];
bool InQueue[MAXN+10];

int SPFA(int limit);
int BinarySearch();

int main()
{
    int s, e, c;
    //cin >> n >> p >> k;
    scanf("%d%d%d", &n, &p, &k);

    for(int i = 1; i <= p; i++)
    {
        //cin >> s >> e >> c;
        scanf("%d%d%d", &s, &e, &c);
        Adj[s].push_back((edge){e, c});
        Adj[e].push_back((edge){s, c});
    }

    //cout << BinarySearch() << endl ;
    int res = BinarySearch();
    if(res > MAXL)
        res = -1;
    printf("%d\n", res);
}

/// @return 长度大于limit的边的条数
int SPFA(int limit)
{
    memset(InQueue, 0x00, sizeof InQueue);
    memset(dist   , 0x7f, sizeof dist);
    dist[1] = 0;    InQueue[1] = true;
    queue <int> q;
    q.push(1);

    while(!q.empty())
    {
        int curpos = q.front(); q.pop();
        InQueue[curpos] = false;

        for(int i = 0; i < Adj[curpos].size(); i++)
        {
            const edge & e = Adj[curpos][i];
            int truecost = (e.cost >= limit);

            if(dist[e.to] > dist[curpos] + truecost && dist[curpos] < 0x7f7f7f7f)
            {
                dist[e.to] = dist[curpos] + truecost;
                if(!InQueue[e.to])
                {
                    InQueue[e.to] = true;
                    q.push(e.to);
                }
            }
        }
    }

    return dist[n];
}

int BinarySearch()
{
    int lb = 0, rb = MAXL+10;

    while(lb+1 < rb)
    {
        int mid = (lb+rb) >> 1;

        if(SPFA(mid) <= k)
            rb = mid;
        else
            lb = mid;
    }
    return lb;
}
