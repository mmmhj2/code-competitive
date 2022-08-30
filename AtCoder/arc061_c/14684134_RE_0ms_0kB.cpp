#include <algorithm>
#include <iterator>
#include <iostream>
//#include <iomanip>
//#include <cstring>
//#include <cstdlib>
#include <cstring>
#include <string>
#include <vector>
#include <queue>
//#include <cmath>
//#include <set>
#include <map>
using namespace std;
#ifdef LOCAL
#define DEBUGMSG()                                                              \
{                                                                               \
    cerr << "[调试 @" << __PRETTY_FUNCTION__ << ":" << __LINE__ << "]" ;        \
}
#define DEBUGVAR(x)                                                             \
{                                                                               \
    cerr << "[调试 @" << __PRETTY_FUNCTION__ << ":" << __LINE__ << "]:" ;       \
    cerr << "([" << typeid(x).name() << "]" << #x << ")" << x << endl ;         \
}
#define DEBUGARR(l, r)                                                          \
{                                                                               \
    cerr << "[调试 @" << __PRETTY_FUNCTION__ << ":" << __LINE__ << "]:" ;       \
    copy(l, r, ostream_iterator<decltype(*l)>(cerr, " "));                      \
    cerr << endl ;                                                              \
}
#else
#define DEBUGMSG()
#define DEBUGVAR(x)
#define DEBUGARR(l, r)
#endif // LOCAL
const int MAXN = 100000 + 5;
const int MAXC = 1200000 ;

#define union _union_1337
#define ITRF itr->first
#define ITRS itr->second

typedef long long i64;

struct disjointSet
{
    int fa[MAXC];

    void clear(int N)
    {
        for(int i = 0; i <= N; i++)
            fa[i] = i;
    }

    int find(int x)
    {
        if(fa[x] == x)
            return x;
        return fa[x] = find(fa[x]);
    }

    void union(int x, int y)
    {
        fa[x] = y;
    }
}dS;

vector <pair<int, int>> G[MAXC];
vector <int> Adj[MAXC];
queue <int> q;
bool used[MAXC];
int newNo[MAXC];
int dist[MAXC];
int allocCnt;
int N, M;

void BFS()
{
    memset(dist, 0x7f, sizeof dist);
    q.push(1);
    dist[1] = 0;

    while(!q.empty())
    {
        int cur = q.front();
        q.pop();

        for(auto itr = Adj[cur].begin(); itr != Adj[cur].end(); itr++)
            if(dist[*itr] >= 0x7f7f7f7f)
                dist[*itr] = dist[cur]+1,
                q.push(*itr);
    }
}

int main()
{
    int a, b, c;
    cin >> N >> M ;
    for(int i = 1; i <= M; i++)
        cin >> a >> b >> c ,
        G[c].push_back(make_pair(a, b));

    allocCnt = N ;
    for(int k = 1; k <= N; k++)
    {
        int fa;
        if(G[k].empty())
            continue;

        for(auto itr = G[k].begin(); itr != G[k].end(); itr++)
        {
            used[ITRF] = used[ITRS] = false,
            newNo[ITRF] = newNo[ITRS] = -1,
            dS.fa[ITRF] = ITRF, dS.fa[ITRS] = ITRS;
        }

        for(auto itr = G[k].begin(); itr != G[k].end(); itr++)
            dS.union(ITRF, ITRS);
        for(auto itr = G[k].begin(); itr != G[k].end(); itr++)
        {
            if(!used[ITRF])
            {
                used[ITRF] = true;
                fa = dS.find(ITRF);
                if(newNo[fa] <= 0)
                    newNo[fa] = ++allocCnt;
                Adj[ITRF].push_back(newNo[fa]);
                Adj[newNo[fa]].push_back(ITRF);
            }
            if(!used[ITRS])
            {
                used[ITRS] = true;
                fa = dS.find(ITRS);
                if(newNo[fa] <= 0)
                    newNo[fa] = ++allocCnt;
                Adj[ITRS].push_back(newNo[fa]);
                Adj[newNo[fa]].push_back(ITRS);
            }
        }
    }

    BFS();

    if(dist[N] >= 0x7F7F7F7F)
        cout << -1 << endl;
    else
        cout << dist[N] / 2 << endl ;
}


