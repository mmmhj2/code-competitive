#include <iostream>
#include <utility>
#include <vector>
#include <stack>
using namespace std;
const int MAXN = 20000;
const int MAXM = 100000;
struct edge
{
    int to;
    edge(){};
    edge(int t){to = t;};
    operator int(){return to;};
};

typedef pair<int, int> biEdge;
typedef vector<edge> AdjTableHead;
typedef vector<edge> AdjTable[MAXN+5];
typedef vector<biEdge> EdgeTable;
typedef stack<int> VexStack;

VexStack vexStack;
AdjTable Adj, newAdj;

//EdgeTable edgeTable;
int newWeight[MAXN+5];        // Used to build new map

bool inStack[MAXN+5], DFSVist[MAXN+5];
int SCCid[MAXN+5], SCCcnt;

int LOW[MAXN+5], DFN[MAXN+5], TmStp;

int Weight[MAXN+5];
int ans;
int n, m;

void Tarjan(int cur, int fa);
void DFS(int cur, int sum = 0);
void BuildGraph(void);

int main()
{
    cin >> n >> m ;
    for(int i = 1; i <= n; i++)
        cin >> Weight[i];
    for(int i = 1; i <= m; i++)
    {
        int u, v;
        cin >> u >> v;
        Adj[u].push_back(v);
        //edgeTable.push_back(make_pair(u, v));
        //Adj[v].push_back(u);
    }
    Tarjan(1, 1);

    /*
    cerr << SCCcnt << endl ;
    for(int i = 1; i <= n; i++)
        cerr << newWeight[SCCid[i]] << " " ;
    cerr << endl ;
    */

    BuildGraph();
    DFS(SCCid[1], newWeight[SCCid[1]]);
    cout << ans << endl ;
}

void Tarjan(int cur, int fa)
{
    TmStp ++;
    DFN[cur] = TmStp;
    LOW[cur] = DFN[cur];
    vexStack.push(cur);
    inStack[cur] = true;

    for(int i = 0; i < Adj[cur].size(); i++)
    {
        int to = Adj[cur][i];
        if(!DFN[to])
        {
            Tarjan(to, cur);
            LOW[cur] = min(LOW[cur], LOW[to]);
        }
        if(inStack[to])
            LOW[cur] = min(LOW[cur], DFN[to]);
    }

    if(DFN[cur] == LOW[cur])
    {
        SCCcnt++;
        int tp;
        do
        {
            tp = vexStack.top();
            inStack[tp] = false;
            vexStack.pop();
            SCCid[tp] = SCCcnt;
            newWeight[SCCcnt] += Weight[tp];
        }while(tp != cur);
    }
}

void DFS(int cur, int sum)
{
    ans = max(ans, sum);

    for(int i = 0; i < newAdj[cur].size(); i++)
    {
        int to = newAdj[cur][i];
        if(!DFSVist[to])
        {
            DFSVist[to] = true;
            DFS(to, sum + newWeight[to]);
            DFSVist[to] = false;
        }
    }
}

void BuildGraph()
{
    AdjTableHead::iterator itr;
    for(int i = 1; i <= n; i++)
    {
        for(itr = Adj[i].begin(); itr != Adj[i].end(); itr++)
        {
            int u(i), v(*itr);
            //cerr << "Attempted Build Edge:" << u << " " << v << endl ;
            u = SCCid[u], v = SCCid[v];
            if(u == v)
                continue;
            if((!u) || (!v))
                continue;
            //cerr << "Successful:" << u << " " << v << endl ;
            newAdj[u].push_back(v);
        }
    }
}
