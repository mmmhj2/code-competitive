#include <iostream>
#include <cstring>
#include <vector>
#include <stack>
#include <cmath>
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
typedef pair<int, int> pii;

int myabs(int t)
{
    return (t < 0 ? -t : t);
}

inline int ManDist(int x1, int y1, int x2, int y2)
{
    return myabs(x1 - x2) + myabs(y1 - y2);
}

const int MAXN = 500 * 2 + 5;
const int MAXV = 505;

//pii Hated[MAXN], Liked[MAXN];
SCCFinder SF;
int n, a, b;
int sx[2], sy[2];
int x[MAXV], y[MAXV];
int dist[MAXV][2];
bool InStack[MAXN];
int LOW[MAXN], DFN[MAXN];
int SCCid[MAXN];
vector <int> Adj[MAXN];
vector <int> NeoGraph[MAXN];

inline void AddEdge(int a, int b)
{
    Adj[a].push_back(b);
}

inline void AddNeoEdge(int a, int b)
{
    NeoGraph[a].push_back(b);
}

inline void LinkHated(int a, int b)
{
    // a ⊕ b = T
    AddEdge(a, b+n);
    AddEdge(b, a+n);
    AddEdge(a+n, b);
    AddEdge(b+n, a);
}

inline void LinkLiked(int a, int b)
{
    // a ⊕ b = F
    AddEdge(a, b);
    AddEdge(b, a);
    AddEdge(a+n, b+n);
    AddEdge(b+n, a+n);
}

inline void LinkDistSame(int a, int b)
{
    // a ∧ b = F
    AddNeoEdge(a, b+n);
    AddNeoEdge(b, a+n);
}

inline void LinkDistDiff(int a, int b)
{
    // a ∧ !b = F
    AddNeoEdge(a, b);
    AddNeoEdge(a+n, b+n);
}

int check(int maxDist);

int BinarySearch()
{
    // Pre-calculate distances

    dist[0][0] = ManDist(sx[1], sy[1], sx[0], sy[0]);
    for(int i = 1; i <= n; i++)
    {
        dist[i][0] = ManDist(x[i], y[i], sx[0], sy[0]);
        dist[i][1] = ManDist(x[i], y[i], sx[1], sy[1]);
    }

    // Get maximum distance

    int maxDist = 0;

    for(int i = 1; i <= n; i++)
        for(int j = i+1; j <= n; j++)
            for(int k = 0; k < 2; k++)
            {
                maxDist = max(maxDist, dist[i][k] + dist[j][k]);
                maxDist = max(maxDist, dist[i][k] + dist[j][1-k] + dist[0][0]);
            }

    // Binary Search
    int l = -1, r = maxDist+1;
    while(l + 1 < r)
    {
        int mid = (l + r) >> 1;
        if(check(mid))
            r = mid;
        else
            l = mid;
    }
    if(r == maxDist+1)
        return -1;
    return r;
}

int main()
{

    cin >> n >> a >> b ;
    cin >> sx[0] >> sy[0] >> sx[1] >> sy[1];
    for(int i = 1; i <= n; i++)
        cin >> x[i] >> y[i] ;
    for(int i = 1; i <= a; i++)
    {
        int u, v;
        cin >> u >> v ;
        LinkHated(u, v);
    }
    for(int i = 1; i <= b; i++)
    {
        int u, v;
        cin >> u >> v ;
        LinkLiked(u, v);
    }
    SF.SCCFinderInit(SCCid, LOW, DFN, InStack, NeoGraph);
    cout << BinarySearch() << endl ;
}

int check(int maxDist)
{
    memset(LOW, 0x00, sizeof LOW);
    memset(DFN, 0x00, sizeof DFN);
    memset(InStack, 0x00, sizeof InStack);
    memset(SCCid, 0x00, sizeof SCCid);

    for(int i = 0; i <= 2 * n; i++)
    {
        NeoGraph[i].clear();
        NeoGraph[i].assign(Adj[i].begin(), Adj[i].end());
    }
    for(int i = 1; i <= n; i++)
        for(int j = i+1; j <= n; j++)
            for(int k = 0; k < 2; k++)
            {
                if(dist[i][k] + dist[j][k] > maxDist)
                    LinkDistSame(i, j);
                if(dist[i][k] + dist[j][1-k] + dist[0][0] > maxDist)
                    LinkDistDiff(i, j);
            }

    for(int i = 1; i <= n * 2; i++)
        if(!DFN[i])
            SF.FindSCC(i);

    for(int i = 1; i <= n; i++)
        if(SCCid[i] == SCCid[i+n])
            return false;
    return true;
}
