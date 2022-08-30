#include <iostream>
#include <cstring>
#include <vector>
using namespace std;

const int MAXN = 100000;
vector <int> Adj[MAXN + 5];
int n;

int TreeDFS(int cur, int fa);

int main()
{
    ios::sync_with_stdio(false);
    int kase;
    cin >> kase ;
    while(kase--)
    {
        cin >> n ;
        for(int i = 1; i <= n; i++)
            Adj[i].clear();
        for(int i = 1; i <  n; i++)
        {
            int u, v;
            cin >> u >> v ;
            Adj[u].push_back(v);
            Adj[v].push_back(u);
        }

        if(TreeDFS(1, 0))               // SG != 0
            cout << "Alice" << endl ;
        else
            cout << "Bob" << endl ;
    }
}

int TreeDFS(int cur, int fa)
{
    //if(Adj[cur].size() == 1)
    //    return 0;
    int ans = 0;
    for(vector<int>::iterator itr = Adj[cur].begin(); itr != Adj[cur].end(); itr++)
    {
        if(*itr == fa)
            continue;
        // SG[fa] = XOR_SUM(SG[son]+1)
        ans ^= (TreeDFS(*itr, cur) + 1);
    }
    return ans ;
}
