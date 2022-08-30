#include <iostream>
#include <vector>
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

const int MAXN = 500*2+10;

bool inStack[MAXN];
vector <int> Adj[MAXN];
int DFN[MAXN], LOW[MAXN];
int SCCid[MAXN];
int X[MAXN], Y[MAXN];

int main()
{
    SCCFinder sf;
    int m, n;
    
    cin >> n >> m ;

    for(int i = 1; i <= m; i++)
    {
        cin >> X[i] >> Y[i];
        X[i]++, Y[i]++;
        if(X[i] > Y[i])
            swap(X[i], Y[i]);
    }

    for(int i = 1; i <= m; i++)
    {
        for(int j = i+1; j <= m; j++)
        {
            if((X[i] <= X[j] && Y[i] >= X[j] && Y[i] <= Y[j]) || \
               (X[i] >= X[j] && Y[i] <= X[j] && Y[i] >= Y[j]))
            {
                Adj[i].push_back(j+m);
                Adj[j].push_back(i+m);
                Adj[i+m].push_back(j);
                Adj[j+m].push_back(i);
            }
        }
    }

    sf.SCCFinderInit(SCCid, LOW, DFN, inStack, Adj);

    for(int i = 1; i <= m*2; i++)
    {
        //cerr << i << endl ;
        //for(int k = 0; k < Adj[i].size(); k++)
        //    cerr << " " << Adj[i][k];
        //cerr << endl ;
        if(!DFN[i])
            sf.FindSCC(i);
    }


    for(int i = 1; i <= m; i++)
        if(SCCid[i] == SCCid[i+m])
        {
            cout << "the evil panda is lying again" << endl ;
            return 0;
        }
    cout << "panda is telling the truth..." << endl ;
    return 0;
}

