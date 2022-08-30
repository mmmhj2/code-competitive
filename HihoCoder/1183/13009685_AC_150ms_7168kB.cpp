// Articulation Points And Bridges
#include <iostream>
#include <utility>
#include <vector>
#include <set>
using namespace std;
const int MAXN = 20000;

struct edge
{
    int to;
    edge(){};
    edge(int t)
    {
        to = t;
    }
    operator int()
    {
        return to;
    }
};

typedef set<int> pSet;
typedef set<pair<int, int> > eSet;
typedef vector<edge> AdjTable;

pSet AnsP;  eSet AnsE;
AdjTable Adj[MAXN+5];
int DFN[MAXN+5], LOW[MAXN+5];
int n, m, curroot, TimeStp ;

int tarjan(int fa, int cur);

int main()
{
    cin >> n >> m ;
    for(int i = 1; i <= m; i++)
    {
        int u, v;
        cin >> u >> v;
        Adj[u].push_back(v);
        Adj[v].push_back(u);
    }

    for(int i = 1; i <= n; i++)
        if(!DFN[i])
        {
            curroot = i;
            tarjan(i, i);
        }

    if(AnsP.begin() == AnsP.end())
        cout << "Null" << endl;
    else
    {
        pSet::iterator itr ;
        for(itr = AnsP.begin(); itr != AnsP.end(); itr++)
            cout << *itr << " " ;
        cout << endl ;
    }
    if(AnsE.begin() != AnsE.end())
    {
        eSet::iterator itr;
        for(itr = AnsE.begin(); itr != AnsE.end(); itr++)
            cout << itr->first << " " << itr->second << endl ;
    }
}

int tarjan(int fa, int cur)
{
    int chcnt = 0;
    TimeStp ++;
    DFN[cur] = TimeStp;
    LOW[cur] = TimeStp;
    for(int i = 0 ; i < Adj[cur].size(); i++)
    {
        int to = Adj[cur][i];
        if(!DFN[to])
        {
            chcnt++;
            tarjan(cur, to);

            LOW[cur] = min(LOW[cur], LOW[to]);

            if(cur == curroot && chcnt >= 2)
                AnsP.insert(cur);
            if(cur != curroot && DFN[cur] <= LOW[to])
                AnsP.insert(cur);
            if(DFN[cur] < LOW[to])
                AnsE.insert(make_pair(min(cur, to), max(cur, to)));

        }
        else if (to != fa)
        {
            LOW[cur] = min(LOW[cur], DFN[to]);
        }
    }
    return 0;
}
