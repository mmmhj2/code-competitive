#include <iostream>
#include <cstring>
#include <vector>
using namespace std;

const int MAXN = 20000 + 5;

class TreeDecomposite
{
    typedef int *pint;

    pint siz;   // size of its subtree
    pint top;   // peak of its chain
    pint son;   // the id of its heavy son
    pint dep;   // its depth
    pint tid;   // newly-allocated id (DFN)
    pint rnk;   // original id
    pint fa;    // its father
    vector <int> *Adj;

    int allocCnt;

    void dfsFindHeavy(int cur, int father)
    {
        dep[cur] = dep[father] + 1;
        siz[cur] = 1;
        fa[cur] = father;

        for(vector<int>::iterator itr = Adj[cur].begin(); itr != Adj[cur].end(); ++itr)
        {
            const int & to = *itr;
            if(to == father)
                continue;

            dfsFindHeavy(to, cur);
            siz[cur] += siz[to];

            if(son[cur] < 0 || siz[to] > siz[son[cur]])
                son[cur] = to;
        }
    }

    /// @p tp The index of the top of current heavy chain
    void dfsLinkHeavy(int cur, int tp)
    {
        top[cur] = tp;
        tid[cur] = ++allocCnt;      // Update DFN
        rnk[allocCnt] = cur;

        if(son[cur] < 0)            // leaf node
            return;
        dfsLinkHeavy(son[cur], tp); // Link heavy edge

        for(vector<int>::iterator itr = Adj[cur].begin(); itr != Adj[cur].end(); ++itr)
        {
            const int & to = *itr;
            if(to == son[cur] || to == fa[cur])
                continue;
            dfsLinkHeavy(to, to);   // Add new chain
        }
    }

public:

    TreeDecomposite(){} ;
    virtual ~TreeDecomposite(){} ;

    void RunDecomp(int * p1, int * p2, int * p3, int * p4, int * p5, int * p6, int * p7, vector<int> * _Adj)
    {
        siz = p1,
        top = p2,
        son = p3,
        dep = p4,
        fa = p5,
        tid = p6,
        rnk = p7,
        Adj = _Adj;

        allocCnt = 0;
        dfsFindHeavy(1, 0);
        dfsLinkHeavy(1, 1);
    }

};

typedef int ARR[MAXN];
int N;
ARR siz, top, son, dep, tid, rnk, fa;
ARR val, w;
TreeDecomposite TD;
vector <int> Adj[MAXN];
vector <int> id[MAXN];

#define LC(x) (x << 1)
#define RC(x) (x << 1 | 1)

int MAX[MAXN * 4];

void PushUp(int cur)
{
    MAX[cur] = max(MAX[LC(cur)], MAX[RC(cur)]);
}

void Build(int cur = 1, int L = 1, int R = N*2 - 1)
{
    if(L == R)
        MAX[cur] = val[rnk[L]];
    else
    {
        int mid = (L + R) >> 1 ;
        Build(LC(cur), L, mid);
        Build(RC(cur), mid+1, R);
        PushUp(cur);
    }
}

void Modify(int pos, int nval, int cur = 1, int L = 1, int R = N*2 - 1)
{
    if(L == R && L == pos)
        MAX[cur] = nval;
    else
    {
        int mid = (L+R) >> 1;
        if(pos <= mid)
            Modify(pos, nval, LC(cur), L, mid);
        else
            Modify(pos, nval, RC(cur), mid+1, R);
        PushUp(cur);
    }
}

int Query(int l, int r, int cur = 1, int L = 1, int R = N*2 - 1)
{
    if(R < l || r < L)
        return 0;
    if(l <= L && r <= R)
        return MAX[cur];

    int mid = (L + R) >> 1;

    return max(Query(l, r, LC(cur), L, mid), Query(l, r, RC(cur), mid+1, R));
}

int QueryLCA(int a, int b)
{
    int ret = 0;
    while(top[a] != top[b])
    {
        if(dep[top[a]] > dep[top[b]])
            swap(a, b);
        ret = max(ret, Query(tid[top[b]], tid[b]));
        b = fa[top[b]];
    }

    if(dep[a] > dep[b])
        swap(a, b);

    ret = max(ret, Query(tid[a], tid[b]));
    return ret;
}

void Init()
{
    memset(son, 0xFF, sizeof (ARR));
    memset(siz, 0x00, sizeof (ARR));
    memset(top, 0x00, sizeof (ARR));
    memset(dep, 0x00, sizeof (ARR));
    memset(tid, 0x00, sizeof (ARR));
    memset(rnk, 0x00, sizeof (ARR));
    memset(fa, 0x00, sizeof (ARR));

    for(int i = 1; i <= N; i++)
        Adj[i].clear(), id[i].clear();
}

int main()
{
    int kase;
    string op;
    int a, b;
    cin >> kase ;

    while(kase--)
    {
        int u, v, w;
        cin >> N ;
        Init();

        for(int i = 1; i < N; i++)
            cin >> u >> v >> w ,
            Adj[u].push_back(N + i),
            Adj[v].push_back(N + i),
            val[N + i] = w;


        TD.RunDecomp(siz, top, son, dep, fa, tid, rnk, Adj);
        Build();

        while(cin >> op)
        {
            if(op[0] == 'D')
                break;
            else if(op[0] == 'C')
                cin >> a >> b,
                Modify(a, b);
            else
                cin >> a >> b,
                cout << QueryLCA(a, b) << endl ;
        }

    }

    return 0;
}
