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
using namespace std ;

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

const int N = 1234567;
vector <pair<int, int> > G[N] ;
vector <int> newg[N] ;
queue <int> q ;
int f[N], son[N], id[N], dp[N] ;
bool use[N] ;
int n, m ;
inline void init(int i)
{
    f[i] = i;
    son[i] = 0;
    id[i] = -1;
    use[i] = false ;
}
int find(int x)
{
    return (x == f[x]) ? x : f[x] = find(f[x]) ;
}
inline void merge(int x, int y)
{
    int X = find(x), Y = find(y) ;
    if (X == Y)
        return ;
    if (son[X] < son[Y])
        f[X] = Y ;
    else
    {
        f[Y] = X ;
        if (son[X] == son[Y])
            son[X]++ ;
    }
}
int main()
{

    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
    freopen("AC.log", "w", stderr);

    //n = read();
    scanf("%d%d", &n, &m);
    //m = read() ;
    for (int i = 1; i <= m; i++)
    {
        int a, b, c ;
        /*
        a = read();
        b = read();
        c = read();
        */
        scanf("%d%d%d", &a, &b, &c);
        G[c].push_back(make_pair(a, b)) ;
    }
    int cnt = n;
    for (int i = 1; i <= N; i++)
    {
        if (G[i].empty())
            continue ;
        for (int j = 0; j < G[i].size(); j++)
        {
            init(G[i][j].first) ;
            /*
            f[i] = i;
            son[i] = 0;
            id[i] = -1;
            use[i] = false ;
            */
            init(G[i][j].second) ;
        }
        for (int j = 0; j < G[i].size(); j++)
            merge(G[i][j].first, G[i][j].second) ;
        for (int j = 0; j < G[i].size(); j++)
        {
            if (!use[G[i][j].first])
            {
                use[G[i][j].first] = true ;
                int X = find(G[i][j].first) ;
                if (id[X] == -1)
                    id[X] = ++cnt ;
                newg[G[i][j].first].push_back(id[X]) ;
                newg[id[X]].push_back(G[i][j].first) ;
            }
            if (!use[G[i][j].second])
            {
                use[G[i][j].second] = true ;
                int X = find(G[i][j].second) ;
                if (id[X] == -1)
                    id[X] = ++cnt ;
                newg[G[i][j].second].push_back(id[X]) ;
                newg[id[X]].push_back(G[i][j].second) ;
            }
        }
    }
    q.push(1) ;
    memset(dp, -1, sizeof(dp)) ;
    dp[1] = 0;
    while (!q.empty())
    {
        int v = q.front();
        q.pop() ;
        for (int i = 0; i < newg[v].size(); i++)
        {
            int to = newg[v][i] ;
            if (dp[to] == -1)
            {
                dp[to] = dp[v] + 1 ;
                q.push(to) ;
            }
        }
    }
    DEBUGARR(dp, &dp[n+1]);
    if (dp[n] == -1)
        cout << -1 ;
    else
        cout << dp[n] / 2 ;
}
