#include <algorithm>
#include <iostream>
#include <vector>
#include <set>
using namespace std;

const int MAXN = 200000;

set <int> Adj[MAXN+5];
set <int> unused;
vector <int> components;
int cnt = 0;

int DFS(int i)
{
    unused.erase(i);
    components[cnt] ++;

    int cur = -1;
    while(true)
    {
        set<int>::iterator itr = unused.upper_bound(cur);
        if(itr == unused.end())
            break;
        cur = *itr;
        if(Adj[i].count(cur))
            continue;
        DFS(cur);
    }
    return 0;
}

int main()
{
    int n, m;
    cin >> n >> m;
    for(int i = 1; i <= m; i++)
    {
        int x, y;
        cin >> x >> y;
        Adj[x].insert(y);
        Adj[y].insert(x);
    }
    for(int i = 1; i <= n; i++)
        unused.insert(i);
    for(int i = 1; i <= n; i++)
    {
        if(unused.count(i))
        {
            components.push_back(0);
            DFS(i);
            cnt++;
        }
    }
    cout << components.size() << endl;
    sort(components.begin(), components.end());
    for(int i = 0; i < components.size(); i++)
        cout << components[i] << " " ;
}
