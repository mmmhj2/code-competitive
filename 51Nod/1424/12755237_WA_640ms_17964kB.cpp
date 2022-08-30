#include <algorithm>
#include <iostream>
#include <vector>
#include <set>
using namespace std;
const int MAXN = 100000;

int n;
int val[MAXN+5];
int dpadd[MAXN+5];
int dpsub[MAXN+5];
vector <int> Adj[MAXN+5];

int dfs(int = 1, int = 0);

int main()
{
    cin >> n;
    for(int i = 1; i < n; i++)
    {
        int u, v;
        cin >> u >> v;
        Adj[u].push_back(v);
        Adj[v].push_back(u);
    }
    for(int i = 1; i <= n; i++)
        cin >> val[i];

    dfs();

    cout << dpadd[1] + dpsub[1] << endl ;
    return 0;
}

int dfs(int cur, int pre)
{
    for(int i = 0; i < Adj[cur].size(); i++)
    {
        int & to = Adj[cur][i];
        if(to == pre)
            continue;
        dfs(to, cur);
        dpadd[cur] = max(dpadd[cur], dpadd[to]);
        dpsub[cur] = max(dpsub[cur], dpsub[to]);
    }
    val[cur] += dpadd[cur]; val[cur] -= dpsub[cur];

    if(val[cur] < 0)
        dpadd[cur] -= val[cur];
    else
        dpsub[cur] += val[cur];
    return 0;
}
