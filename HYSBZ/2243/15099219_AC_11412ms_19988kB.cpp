#include <iostream>
#include <iterator>
#include <cstring>
#include <cstdio>
#include <vector>
using namespace std;

#ifdef LOCAL
#include <iterator>
#define DEBUGMSG()                                                              \
{                                                                               \
    cerr << "[调试 @" << __PRETTY_FUNCTION__ << ":" << __LINE__ << "]" ;        \
}
#define DEBUGVAR(x)                                                             \
{                                                                               \
    cerr << "[调试 @" << __PRETTY_FUNCTION__ << ":" << __LINE__ << "]:" ;       \
    cerr << "([" << typeid(x).name() << "]" << #x << ")" << x << endl ;         \
}
#define DEBUGARR(l, r)                                                          \
{                                                                               \
    cerr << "[调试 @" << __PRETTY_FUNCTION__ << ":" << __LINE__ << "]:" ;       \
    copy(l, r, ostream_iterator<decltype(*l)>(cerr, " "));                      \
    cerr << endl ;                                                              \
}
#else
#define DEBUGMSG()
#define DEBUGVAR(x)
#define DEBUGARR(l, r)
#endif // LOCAL

const int MAXN = (100000 + 5);          // 10^5
const int INF = 0x7FFFFFFF;

#define getInteger(x) scanf("%d", &x)
#define putInteger(x) printf("%d\n", x)

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
////////////////////////////////////////////////////////////
typedef int ARR[MAXN];
int N, Q;
int allocCnt;
ARR siz, top, son, dep, tid, rnk, fa;
ARR col;
TreeDecomposite TD;
vector <int> Adj[MAXN];
////////////////////////////////////////////////////////////

#define LC (x << 1)
#define RC (x << 1 | 1)

struct SegNode
{
    int l, r;
    int lz;
    int cl, cr;
    int sum;
} tree[MAXN * 4];

void push_down(int x)
{
    if(tree[x].l == tree[x].r)
        return;
    if(tree[x].lz)
    {
        tree[LC].lz = tree[RC].lz = 1;
        tree[LC].cl = tree[LC].cr = tree[x].cl;
        tree[RC].cl = tree[RC].cr = tree[x].cl;
        tree[LC].sum = tree[RC].sum = 1;
        tree[x].lz = 0;
    }
}

void push_up(int x)
{
    tree[x].cl = tree[LC].cl;
    tree[x].cr = tree[RC].cr;
    tree[x].sum = tree[LC].sum + tree[RC].sum;

    if(tree[LC].cr == tree[RC].cl)
        tree[x].sum --;
}

void Build(int L, int R, int x)
{
    tree[x].l = L, tree[x].r = R;
    tree[x].lz = 0;

    if(L == R)
    {
        tree[x].cl = tree[x].cr = col[rnk[L]] ;
        tree[x].sum = 1 ;
        return ;
    }

    int mid = (L + R) >> 1 ;
    Build(L, mid, LC);
    Build(mid+1, R, RC);

    push_up(x);
}

void Modify(int l, int r, int val, int x)
{
    if(tree[x].l == l && tree[x].r == r)
    {
        tree[x].cl = tree[x].cr = val;
        tree[x].sum = 1;
        tree[x].lz = 1;
        return;
    }
    push_down(x);
    int mid = (tree[x].l + tree[x].r) >> 1 ;
    if(r <= mid)
        Modify(l ,r, val, LC);
    else if(l > mid)
        Modify(l, r, val, RC);
    else
        Modify(l, mid, val, LC), Modify(mid + 1, r, val, RC);
    push_up(x);
}

int ansLC, ansRC;
int Query(int l, int r, int x, int L, int R)
{
    push_down(x);
    if(tree[x].l == L)
        ansLC = tree[x].cl;
    if(tree[x].r == R)
        ansRC = tree[x].cr;
    if(tree[x].l == l && tree[x].r == r)
        return tree[x].sum;

    int mid = (tree[x].l + tree[x].r) >> 1 ;

    if(r <= mid)
        return Query(l, r, LC, L, R);
    else if(l > mid)
        return Query(l ,r, RC, L, R);
    else
    {
        int ret = Query(l, mid, LC, L, R) \
                + Query(mid+1, r, RC, L, R);
        if(tree[LC].cr == tree[RC].cl)
            ret--;
        return ret;
    }
}

void ModifyLCA(int a, int b, int val)
{
    while(top[a] != top[b])
    {
        if(dep[top[a]] < dep[top[b]])
            swap(a, b);
        Modify(tid[top[a]], tid[a], val, 1);
        a = fa[top[a]];
    }

    if(dep[a] > dep[b])
        swap(a, b);
    Modify(tid[a], tid[b], val, 1);
}

int QueryLCA(int a, int b)
{
    int col1(-1), col2(-1);
    int ret = 0;

    while(top[a] != top[b])
    {
        if(dep[top[a]] < dep[top[b]])
            swap(a, b), swap(col1, col2);
        ret += Query(tid[top[a]], tid[a], 1, tid[top[a]], tid[a]);

        if(col1 == ansRC)
            ret--;
        col1 = ansLC;
        a = fa[top[a]];
    }
    if(dep[a] > dep[b])
        swap(a, b), swap(col1, col2);
    ret += Query(tid[a], tid[b], 1, tid[a], tid[b]);

    if(ansRC == col2)
        ret--;
    if(ansLC == col1)
        ret--;
    return ret;
}

////////////////////////////////////////////////////////////

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    string op;
    int u, v, w;
    cin >> N >> Q ;

    for(int i = 1; i <= N; i++)
        cin >> col[i] ;
    for(int i = 1; i < N; i++)
        cin >> u >> v ,
        Adj[u].push_back(v),
        Adj[v].push_back(u);

    memset(son, 0xFF, sizeof son);
    TD.RunDecomp(siz, top, son, dep, fa, tid, rnk, Adj);
    Build(1, N, 1);

    while(Q--)
    {
        cin >> op ;
        if(op[0] == 'C')
        {
            cin >> u >> v >> w ;
            ModifyLCA(u, v, w);
        }
        if(op[0] == 'Q')
        {
            cin >> u >> v ;
            cout << QueryLCA(u, v) << endl ;
        }
    }

    return 0;
}
