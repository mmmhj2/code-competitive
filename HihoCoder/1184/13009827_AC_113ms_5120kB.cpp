#include <iostream>
#include <utility>
#include <vector>
#include <stack>
#include <queue>
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

typedef stack<int> pStack;
typedef set<int> pSet;
typedef set<pair<int, int> > eSet;
typedef vector<edge> AdjTable;

pStack cnctStack;
AdjTable Adj[MAXN+5];
int DFN[MAXN+5], LOW[MAXN+5];
int n, m, curroot, TimeStp ;
int group[MAXN+5], grpcnt;

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
    cout << grpcnt << endl ;
    for(int i = 1; i <= n; i++)
        cout << group[i] << " ";
    cout << endl ;
}

int tarjan(int fa, int cur)
{
    int chcnt = 0;
    TimeStp ++;
    DFN[cur] = TimeStp;
    LOW[cur] = TimeStp;
    cnctStack.push(cur);
    for(int i = 0 ; i < Adj[cur].size(); i++)
    {
        int to = Adj[cur][i];
        if(!DFN[to])
        {
            chcnt++;
            tarjan(cur, to);

            LOW[cur] = min(LOW[cur], LOW[to]);
        }
        else if (to != fa)
        {
            LOW[cur] = min(LOW[cur], DFN[to]);
        }
    }
    if(LOW[cur] == DFN[cur])
    {
        priority_queue <int, vector<int>, greater<int> > SortQueue;
        grpcnt ++;
        //cout << grpcnt << endl ;
        /*while(!cnctStack.empty())
        {
            int tp = cnctStack.top();
            if(tp)
            SortQueue.push();
            cnctStack.pop();
        }*/
        int tp;
        do
        {
            tp = cnctStack.top();
            SortQueue.push(tp);
            cnctStack.pop();
        }while(tp != cur);

        int blockID = SortQueue.top();
        while(!SortQueue.empty())
        {
            tp = SortQueue.top();
            //cout << grpcnt << tp << endl ;
            SortQueue.pop();
            group[tp] = blockID;
        }
    }
    return 0;
}
