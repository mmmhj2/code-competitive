#include <iostream>
#include <vector>
#include <string>
#include <stack>
using namespace std;
////////////////////////////////////////////Template Start////////////////////////////////////////////

/// @b Tarjan Algorithm to find Strongly Connected Components
class SCCFinder
{
private:
    typedef int *pint;
    typedef vector<int> AdjTable;
    typedef stack<int>  vStk;

    #define until(x) while(!(x))

    pint SCCid, LOW, DFN;
    bool * inStack;
    AdjTable * Adj;

    int TmStp, SCCcnt;
    vStk vexStack;

    void Tarjan(int cur)
    {
        TmStp++;
        DFN[cur] = TmStp;   LOW[cur] = DFN[cur];
        vexStack.push(cur); inStack[cur] = true;

        AdjTable::iterator itr;
        for(itr = Adj[cur].begin(); itr < Adj[cur].end(); itr++)
        {
            int to = *itr;
            if(!DFN[to])
            {
                Tarjan(to);
                LOW[cur] = min(LOW[cur], LOW[to]);
            }
            if(inStack[to])
                LOW[cur] = min(LOW[cur], DFN[to]);
        }

        if(DFN[cur] == LOW[cur])
        {
            int tmp = vexStack.top();
            SCCcnt++;
            do
            {
                tmp = vexStack.top();
                SCCid[tmp] = SCCcnt;
                vexStack.pop(); inStack[tmp] = false;
            }until(tmp == cur);
        }
    }

public:
    SCCFinder()
    {
        TmStp = 0;
        SCCcnt = 0;
    }
    void SCCFinderInit(pint _SCCid, pint _LOW, pint _DFN, bool * _inStack, AdjTable * _Adj)
    {
        SCCid = _SCCid;
        LOW = _LOW; DFN = _DFN;
        inStack = _inStack;
        Adj = _Adj;
    }
    void FindSCC(int s)
    {
        if(SCCid == NULL)
            return;
        if(LOW == NULL || DFN == NULL)
            return;
        if(inStack == NULL)
            return;
        if(Adj == NULL)
            return;

        Tarjan(s);
    }
};
////////////////////////////////////////////Template End////////////////////////////////////////////

const int MAXN = 1000*2+10;

bool inStack[MAXN];
vector <int> Adj[MAXN];
int DFN[MAXN], LOW[MAXN];
int SCCid[MAXN];
int X[MAXN], Y[MAXN];

void add_edge(int a, int b)
{
    Adj[a].push_back(b);
    //return Adj[a].size();
}

int MapString(const string & op)
{
    if(op == "OR")
        return 1;
    if(op == "AND")
        return 2;
    if(op == "XOR")
        return 3;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    SCCFinder sf;
    int m, n;

    cin >> n >> m ;

    int a, b, c;
    string op;

    for(int i = 1; i <= m; i++)
    {
        cin >> a >> b >> c >> op ;
        switch(MapString(op))
        {
        case 1:             // OR
            if(c == 0)
            {
                Adj[a].push_back(a+n);
                Adj[b].push_back(b+n);
            }
            else
            {
                Adj[a+n].push_back(b);
                Adj[b+n].push_back(a);
            }
            break;
        case 2:             // AND
            if(c == 0)
            {
                Adj[a].push_back(b+n);
                Adj[b].push_back(a+n);
            }
            else
            {
                Adj[a+n].push_back(a);
                Adj[b+n].push_back(b);
            }
            break;
        case 3:             // XOR
            if(c == 0)
            {
                add_edge(a+n, b+n);
                add_edge(a, b);
                add_edge(b+n, a+n);
                add_edge(b, a);
            }
            else
            {
                add_edge(a+n, b);
                add_edge(a, b+n);
                add_edge(b+n, a);
                add_edge(b, a+n);
            }
            break;

        }
    }

    sf.SCCFinderInit(SCCid, LOW, DFN, inStack, Adj);

    for(int i = 1; i <= n; i++)
    {
        //cerr << i << endl ;
        //for(int k = 0; k < Adj[i].size(); k++)
        //    cerr << " " << Adj[i][k];
        //cerr << endl ;
        if(!DFN[i])
            sf.FindSCC(i);
    }


    for(int i = 1; i <= n; i++)
        if(SCCid[i] == SCCid[i+m])
        {
            cout << "NO" << endl ;
            return 0;
        }
    cout << "YES" << endl ;
    return 0;
}
