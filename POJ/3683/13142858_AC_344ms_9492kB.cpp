#include <iostream>
#include <iomanip>
#include <cstdio>
#include <vector>
#include <string>
#include <stack>
using namespace std;
////////////////////////////////////////////Template Start////////////////////////////////////////////

/// @b Tarjan Algorithm to find Strongly Connected Components
class SCCFinder
{
protected:
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
                SCCid[tmp] = SCCcnt;    // ID of each component is in the topology order
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

class SATSolver : public SCCFinder
{
public:
    inline static int getCurVex(int n)
    {
        return (n << 1);
    }
    inline static int getOppVex(int n)
    {
        return (n << 1) | 1 ;
    }
    /// @b Check if the problem is solved
    /// @p n Number of vertix
    bool solved(int n, int start = 1)
    {
        for(int i = start; i < n+start; i++)
            if(SCCid[getCurVex(i)] != SCCid[getOppVex(i)])
                return false;
        return true;
    }
};
////////////////////////////////////////////Template End////////////////////////////////////////////

struct iTime
{
    int s, e;
};

const int MAXN = 1000*2+10;

bool inStack[MAXN];
vector <int> Adj[MAXN];
int DFN[MAXN], LOW[MAXN];
int SCCid[MAXN];
iTime Time[MAXN];
int Length[MAXN/2];

inline int getHour(int hr, int mn)
{
    return hr*60+mn;
}

inline bool overlap(const iTime & a, const iTime & b)
{
    if(a.s >= b.e || b.s >= a.e)
        return false;
    return true;
}

inline void addEdge(int u, int v)
{
    Adj[u].push_back(v);
}

void printAns(int id)
{
    cout << setfill('0') << setw(2);
    cout << Time[id].s / 60 << ":" ;
    cout << setfill('0') << setw(2);
    cout << Time[id].s % 60 << " " ;
    cout << setfill('0') << setw(2);
    cout << Time[id].e / 60 << ":" ;
    cout << setfill('0') << setw(2);
    cout << Time[id].e % 60 << endl ;
}

int main()
{
    int n, h1, m1, h2, m2, l;
    SATSolver st;
    cin >> n ;

    for(int i = 1; i <= n; i++)
    {
        scanf("%d:%d %d:%d %d", &h1, &m1, &h2, &m2, &l);
        Time[i].s = getHour(h1, m1);
        Time[i+n].e = getHour(h2, m2);
        Time[i].e = Time[i].s + l;
        Time[i+n].s = Time[i+n].e - l;
    }

    for(int i = 1; i <= n; i++)
        for(int j = 1 ; j <= n; j++)
        {
            if(i == j)
                continue;
            if(overlap(Time[i], Time[j]))
                addEdge(i, j+n);
            if(overlap(Time[i], Time[j+n]))
                addEdge(i, j);
            if(overlap(Time[i+n], Time[j]))
                addEdge(i+n, j+n);
            if(overlap(Time[i+n], Time[j+n]))
                addEdge(i+n, j);
        }

    st.SCCFinderInit(SCCid, LOW, DFN, inStack, Adj);

    for(int i = 1; i <= n*2; i++)
        if(!DFN[i])
            st.FindSCC(i);

    for(int i = 1; i <= n; i++)
        if(SCCid[i] == SCCid[i+n])
        {
            cout << "NO" << endl ;
            return 0;
        }
    cout << "YES" << endl ;
    for(int i = 1; i <= n; i++)
    {
        if(SCCid[i] < SCCid[i+n])
            printAns(i);
        else
            printAns(i+n);
    }
}
