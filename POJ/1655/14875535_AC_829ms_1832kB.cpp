#include <iostream>
#include <vector>
using namespace std;

const int MAXN = 20000 + 10;

vector <int> Adj[MAXN];
int sonCnt[MAXN], maxBal[MAXN], N;

void DFS(int cur, int fa)
{
    sonCnt[cur] = 1;

    int maxSubtree = 0;
    for(vector<int>::iterator itr = Adj[cur].begin(); itr != Adj[cur].end(); itr++)
    {
        const int & to = *itr;
        if(to == fa)
            continue;

        DFS(to, cur);
        sonCnt[cur] += sonCnt[to];
        maxSubtree = max(maxSubtree, sonCnt[to]);
    }

    maxBal[cur] = max(maxSubtree, N - sonCnt[cur]);
}

int main()
{
    int kase ;
    cin >> kase ;

    while(kase--)
    {
        int u, v, ans = 0x7FFFFFFF, ansid;
        cin >> N ;

        for(int i = 1; i <= N; i++)
            Adj[i].clear(), sonCnt[i] = 0, maxBal[i] = 0;

        for(int i = 1; i < N; i++)
        {
            cin >> u >> v ;
            Adj[u].push_back(v);
            Adj[v].push_back(u);
        }

        DFS(1, 0);

        for(int i = 1; i <= N; i++)
            if(ans > maxBal[i])
                ans = maxBal[i], ansid = i ;

        cout << ansid << " " << ans << endl ;

    }

    return 0;
}
