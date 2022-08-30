#include <iostream>
#include <cstring>
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
        DFN[cur] = TmStp;
        LOW[cur] = DFN[cur];
        vexStack.push(cur);
        inStack[cur] = true;

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
                vexStack.pop();
                inStack[tmp] = false;
            }
            until(tmp == cur);
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
        LOW = _LOW;
        DFN = _DFN;
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

const int MAXN = 100005;

bool InStack[MAXN*2];
int LOW[MAXN*2], DFN[MAXN*2];
int SCCid[MAXN*2];
vector<int> Adj[MAXN*2];

int Age[MAXN], sum;
int n, m;

int getAB(int x)
{
    if(Age[x] * n < sum)
        return 1;
    return 0;
}

int main()
{
    SCCFinder SF;
    while(1)
    {
        cin >> n >> m ;
        if(n == 0 && m == 0)
            break;

        for(int i = 1; i <= n*2; i++)
            Adj[i].clear();
        memset(InStack, 0x00, sizeof InStack);
        memset(SCCid, 0x00, sizeof SCCid);
        memset(LOW, 0x00, sizeof LOW);  memset(DFN, 0x00, sizeof DFN);
        memset(Age, 0x00, sizeof Age);

        for(int i = 1; i <= n; i++)
            cin >> Age[i], sum += Age[i];
        for(int i = 1; i <= m; i++)
        {
            int a, b;
            cin >> a >> b ;
            if(getAB(a) == getAB(b))
            {
                Adj[a].push_back(b+n);
                Adj[b].push_back(a+n);
            }
            Adj[a+n].push_back(b);
            Adj[b+n].push_back(a);
        }

        SF.SCCFinderInit(SCCid, LOW, DFN, InStack, Adj);
        for(int i = 1; i <= 2 * n; i++)
            if(!DFN[i])
                SF.FindSCC(i);

        for(int i = 1; i <= n; i++)
            if(SCCid[i] == SCCid[i+n])
            {
                cout << "No solution." << endl ;
            }

        for(int i = 1; i <= n; i++)
            if(SCCid[i] < SCCid[i+n])
            {
                //cout << "Find A/B" << endl ;
                if(getAB(i))
                    cout << 'B' << endl ;
                else
                    cout << 'A' << endl ;
            }
            else
            {
                //cout << "Find C" << endl ;
                cout << 'C' << endl ;
            }
    }
    return 0;
}

