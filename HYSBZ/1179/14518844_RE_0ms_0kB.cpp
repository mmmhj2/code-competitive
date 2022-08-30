#include <iostream>
#include <cstring>
#include <cstdio>
#include <vector>
#include <queue>
#include <stack>
using namespace std;
const int INF = 0x7f7f7f7f;
const int MAXN = 500000 + 10;

typedef vector<int> AdjTable;

class Tarjan
{
    typedef int *pint;
    typedef bool *pbol;
    typedef vector<int> vint, *pvint;
    pint SCCid;
    pint LOW, DFN;
    pint w, newW;
    pbol inStk;
    int tmStp;
    pvint pAdj, pNewAdj;

    stack <int> Stk;

    void TarjanMainProcess(int cur, int fa)
    {
        tmStp++;
        LOW[cur] = DFN[cur] = tmStp;
        Stk.push(cur), inStk[cur] = true;

        //for (int to : pAdj[cur])
        for (vint::iterator itr = pAdj[cur].begin(); itr != pAdj[cur].end(); itr++)
        {
            int & to = *itr;
            if (!DFN[to])
            {
                TarjanMainProcess(to, cur);
                LOW[cur] = min(LOW[cur], LOW[to]);
            }
            if (inStk[to])
                LOW[cur] = min(LOW[cur], DFN[to]);
        }

        if (DFN[cur] == LOW[cur])
        {
            SCCcnt++;
            int tp;

            do
            {
                tp = Stk.top();
                Stk.pop();
                inStk[tp] = false;
                SCCid[tp] = SCCcnt;
                newW[SCCcnt] += w[tp];
            }
            while (tp != cur);
        }
    }

    Tarjan() {}
public:
    int SCCcnt;

    Tarjan(pbol _inStk, pint _SCCid, pint _LOW, pint _DFN, pint _w, pint _newW, pvint _Adj, pvint _NewAdj)
    {
        inStk = _inStk;
        SCCid = _SCCid,
        LOW = _LOW,
        DFN = _DFN,
        w = _w,
        newW = _newW;

        SCCcnt = tmStp = 0;
        pAdj = _Adj,
        pNewAdj = _NewAdj;
    }

    void RunTarjan(int sp)
    {
        TarjanMainProcess(sp, sp);
    }

    void Shrink(int N)
    {
        int u, v;
        for (int i = 1; i <= N; i++)
        {
            for (vint::iterator itr = pAdj[i].begin(); itr != pAdj[i].end(); itr++)
            {
                u = i, v = *itr;
                u = SCCid[u], v = SCCid[v];

                if (u == v)
                    continue;
                if ((!u) || (!v))
                    continue;

                pNewAdj[u].push_back(v);
            }
        }
    }
};

int N, M, S, P;
AdjTable Adj[MAXN];
AdjTable newAdj[MAXN];
int LOW[MAXN], DFN[MAXN], SCCid[MAXN], dist[MAXN];
bool InStack[MAXN];
int Weight[MAXN], newWeight[MAXN];

bool SPFA(int st)
{
    st = SCCid[st];
    cerr << "Starting point : " << st << endl ;
    queue <int> q;

    memset(InStack, 0x00, sizeof InStack);
    memset(dist, 0x7f, sizeof dist);

    q.push(st);
    dist[st] = newWeight[st];
    InStack[st] = 1;

    while (!q.empty())
    {
        st = q.front();
        q.pop();
        InStack[st] = false;

        for (vector<int>::iterator itr = newAdj[st].begin(); itr != newAdj[st].end(); itr++)
        {
            int & to = *itr;
            if (dist[to] > dist[st] + newWeight[st])
            {
                dist[to] = dist[st] + newWeight[to];
                if (!InStack[to])
                {
                    InStack[to] = true;
                    q.push(to);
                }
            }
        }
    }
    return true;
}

void AddEdge(int u, int v)
{
    Adj[u].push_back(v);
}




int main()
{
    int u, v, w;
    cin >> N >> M ;
    for (int i = 1 ; i <= M ; i++)
    {
        cin >> u >> v ;
        AddEdge(u, v);
    }
    for (int i = 1 ; i <= N ; i++)
    {
        cin >> w ;
        Weight[i] = w ;
    }
    Tarjan TarjanProc(InStack, SCCid, LOW, DFN, Weight
                      , newWeight, Adj, newAdj);
    cin >> S >> P ;

    TarjanProc.RunTarjan(S);
    TarjanProc.Shrink(N);

    for (int i = 1; i <= N; i++)
        cerr << "Crossing " << i << " is in " << SCCid[i] << " which has the weight " << newWeight[SCCid[i]] << endl ;
    for (int i = 1; i <= TarjanProc.SCCcnt; i++)
    {
        cerr << "SCC " << i << " is connected to : " ;
        for (int j = 0; j < newAdj[i].size(); j++)
            cerr << newAdj[i][j] << " " ;
        cerr << endl ;
    }

    SPFA(S);

    for(int i = 1; i <= P; i++)
    {
        cin >> u ;
        w = max(w, dist[SCCid[u]]);
    }

    cout << w << endl ;

    return 0;
}
