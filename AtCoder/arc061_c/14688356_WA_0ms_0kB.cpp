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
const int MAXC = 1234567 ;

#define union _union_1337

typedef long long i64;

struct disjointSet
{
    int fa[MAXC];
    int son[MAXC];

    void clear(int N)
    {
        for (int i = 0; i <= N; i++)
            fa[i] = i;
    }

    int find(int x)
    {
        if (fa[x] == x)
            return x;
        return fa[x] = find(fa[x]);
    }

    void union(int x, int y)
    {
        int X = find(x), Y = find(y);
        if (X == Y)
            return;
        if (son[X] < son[Y])
            fa[X] = Y;
        else
        {
            fa[Y] = X;
            if (son[X] == son[Y])
                son[X]++;
        }
    }
} dS;

vector <pair<int, int> > G[MAXC];
vector <int> Adj[MAXC];
queue <int> q;
bool used[MAXC];
int newNo[MAXC];
int dist[MAXC];
int allocCnt;
int N, M;

void BFS()
{
    memset(dist, 0xFF, sizeof dist);
    q.push(1);
    dist[1] = 0;

    while (!q.empty())
    {
        int cur = q.front();
        q.pop();

        for (auto itr = Adj[cur].begin(); itr != Adj[cur].end(); itr++)
            if (dist[*itr] == -1)
                dist[*itr] = dist[cur] + 1,
                             q.push(*itr);
    }
}

int main()
{
    //freopen("in.txt", "r", stdin);
    //freopen("out.txt", "w", stdout);
    //freopen("WA.log", "w", stderr);

    int a, b, c;
    cin >> N >> M ;
    for (int i = 1; i <= M; i++)
        cin >> a >> b >> c,
            G[c].push_back(make_pair(a, b));

    allocCnt = N ;
    for (int k = 1; k <= N; k++)
    {
        if (G[k].empty())
            continue;

        for (auto itr = G[k].begin(); itr != G[k].end(); itr++)
        {
            used[itr->first] = used[itr->second] = false;
            newNo[itr->first] = newNo[itr->second] = -1;
            dS.son[itr->first] = dS.son[itr->second] = 0;
            dS.fa[itr->first] = itr->first;
            dS.fa[itr->second] = itr->second;
        }

        for (auto itr = G[k].begin(); itr != G[k].end(); itr++)
            dS.union(itr->first, itr->second);
        for (auto itr = G[k].begin(); itr != G[k].end(); itr++)
        {
            if (!used[itr->first])
            {
                used[itr->first] = true;
                int fa = dS.find(itr->first);
                if (newNo[fa] == -1)
                    newNo[fa] = ++allocCnt;
                Adj[itr->first].push_back(newNo[fa]);
                Adj[newNo[fa]].push_back(itr->first);
            }
            if (!used[itr->second])
            {
                used[itr->second] = true;
                int fa = dS.find(itr->second);
                if (newNo[fa] == -1)
                    newNo[fa] = ++allocCnt;
                Adj[itr->second].push_back(newNo[fa]);
                Adj[newNo[fa]].push_back(itr->second);
            }
        }
    }

    BFS();

    DEBUGARR(dist, &dist[N + 1]);
    if (dist[N] < 0)
        cout << -1 << endl;
    else
        cout << (dist[N] / 2) << endl ;
}


