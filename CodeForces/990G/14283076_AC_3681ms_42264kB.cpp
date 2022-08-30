#include <iostream>
#include <vector>
#include <map>
using namespace std;

typedef long long i64;
const int MAXN = 200000 + 10 ;

int val[MAXN] ;
i64 cnt[MAXN] ;

vector <int> Adj[MAXN];
map <int, i64> c[MAXN];

int GCD(int x, int y)
{
    if(y == 0)
        return x;
    return GCD(y, x % y);
}

void DFS(int cur, int fa)
{
    c[cur][val[cur]]++;

    for(auto nxt : Adj[cur])
    {
        if(nxt == fa)
            continue;

        DFS(nxt, cur);
        for(auto pr1 : c[cur])
            for(auto pr2 : c[nxt])
                cnt[GCD(pr1.first, pr2.first)] += pr1.second * pr2.second;

        for(auto pr2 : c[nxt])
            c[cur][GCD(val[cur], pr2.first)] += pr2.second ;
        c[nxt].clear();
    }
}

int main()
{
    ios::sync_with_stdio(false), cin.tie(0);
    int n ;
    cin >> n ;

    for(int i = 1; i <= n; i++)
    {
        cin >> val[i] ;
        cnt[val[i]]++;
    }

    for(int i = 1; i < n; i++)
    {
        int u, v;
        cin >> u >> v ;
        Adj[u].push_back(v);
        Adj[v].push_back(u);
    }

    DFS(1, 0);

    for(int i = 1; i <= MAXN; i++)
        if(cnt[i])
            cout << i << " " << cnt[i] << endl ;
}

