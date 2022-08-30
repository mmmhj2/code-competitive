#include <iostream>
#include <iterator>
#include <cstring>
#include <cstdio>
#include <vector>
using namespace std;

const int MAXN = (50000 + 5) * 2;
const int INF = 0x7FFFFFFF;

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

    TreeDecomposite() {} ;
    virtual ~TreeDecomposite() {} ;

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
int N, M, P;
ARR siz, top, son, dep, tid, rnk, fa;
ARR w;
TreeDecomposite TD;
vector <int> Adj[MAXN];

#define LC(x) (x << 1)
#define RC(x) (x << 1 | 1)

struct SegNode
{
    int l, r;
    int val, lazy;
} tree[MAXN * 4];


void PushDown(int cur)
{
    SegNode & rt = tree[cur];
    SegNode & lc = tree[LC(cur)];
    SegNode & rc = tree[RC(cur)];
    if(rt.lazy)
    {
        lc.val += rt.lazy;
        rc.val += rt.lazy;
        lc.lazy += rt.lazy;
        rc.lazy += rt.lazy;
        rt.lazy = 0;
    }
}

void Build(int cur = 1, int L = 1, int R = N)
{
    tree[cur].lazy = tree[cur].val = 0,
    tree[cur].l = L,
    tree[cur].r = R;
    if(L == R)
        tree[cur].val = w[rnk[L]];
    else
    {
        int mid = (L + R) >> 1;
        Build(LC(cur), L, mid);
        Build(RC(cur), mid + 1, R);
    }

}


void Modify(int delta, int cur = 1, int L = 1, int R = N)
{
    SegNode & rt = tree[cur];

    if(rt.l == L && rt.r == R)
    {
        rt.val += delta;
        rt.lazy += delta;
        return;
    }

    PushDown(cur);
    int mid = (rt.l + rt.r) >> 1;

    if(R <= mid)
        Modify(delta, LC(cur), L, R);
    else if(L > mid)
        Modify(delta, RC(cur), L, R);
    else
        Modify(delta, LC(cur), L, mid),
               Modify(delta, RC(cur), mid + 1, R);
}

int Query(int pos, int cur = 1)
{
    SegNode & rt = tree[cur];
    if(pos == rt.l && rt.l == rt.r)
        return rt.val;

    PushDown(cur);

    int mid = (rt.l + rt.r) >> 1;
    if(pos <= mid)
        return Query(pos, LC(cur));
    else
        return Query(pos, RC(cur));
}

void ModifyLCA(int a, int b, int delta)
{
    while(top[a] != top[b])
    {
        if(dep[top[a]] < dep[top[b]])
            swap(a, b);
        Modify(delta, 1, tid[top[a]], tid[a]);
        a = fa[top[a]];
    }

    if(dep[a] > dep[b])
        swap(a, b);
    Modify(delta, 1, tid[a], tid[b]);
}

void Init()
{
    memset(tree, 0x00, sizeof (tree));
    memset(son, 0xFF, sizeof (ARR));
    memset(siz, 0x00, sizeof (ARR));
    memset(top, 0x00, sizeof (ARR));
    memset(dep, 0x00, sizeof (ARR));
    memset(tid, 0x00, sizeof (ARR));
    memset(rnk, 0x00, sizeof (ARR));
    memset(fa, 0x00, sizeof (ARR));

    for(int i = 1; i <= N; i++)
        Adj[i].clear();

}

int main()
{
    char c[10];
    int u, v, t;
    while(~scanf("%d%d%d", &N, &M, &P))
    {
        Init();
        for(int i = 1; i <= N; i++)
            scanf("%d", &w[i]);
        for(int i = 1; i <= M; i++)
            scanf("%d%d", &u, &v),
                  Adj[u].push_back(v),
                  Adj[v].push_back(u);

        TD.RunDecomp(siz, top, son, dep, fa, tid, rnk, Adj);
        Build();

        while(P--)
        {

            scanf("%s", c);

            switch(c[0])
            {
            case 'Q':
                scanf("%d", &t);
                printf("%d\n", Query(tid[t]));
                break;
            case 'I':
                scanf("%d%d%d", &u, &v, &t);
                ModifyLCA(u, v, t);
                break;
            case 'D':
                scanf("%d%d%d", &u, &v, &t);
                ModifyLCA(u, v, -t);
                break;
            }
        }
    }
    return 0;
}
