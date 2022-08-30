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

const int MAXN = (10000 + 5);
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
struct Edge
{
    int u, v, w;
};
vector <Edge> edge;
////////////////////////////////////////////////////////////
typedef int ARR[MAXN];
int N;
int allocCnt;
ARR siz, top, son, dep, tid, rnk, fa;
ARR weight;
bool hasWeight[MAXN];
TreeDecomposite TD;
vector <int> Adj[MAXN];
////////////////////////////////////////////////////////////

#define LC(x) (x << 1)
#define RC(x) (x << 1 | 1)

struct SegNode
{
    int l, r;
    int mn, mx, lz;
} tree[MAXN * 4];

void Negate(int x)
{
    swap(tree[x].mn, tree[x].mx),
         tree[x].mn *= -1,
                       tree[x].mx *= -1;
}

void Pushup(int x)      // Update current node
{
    tree[x].mn = min(tree[LC(x)].mn, tree[RC(x)].mn);
    tree[x].mx = max(tree[LC(x)].mx, tree[RC(x)].mx);
}

void Pushdown(int x)    // Push down Lazy Tags
{
    if(tree[x].lz)
    {
        tree[LC(x)].lz ^= 1;
        tree[RC(x)].lz ^= 1;
        Negate(LC(x));
        Negate(RC(x));
        tree[x].lz = 0;
    }
}

void Build(int cur, int l, int r)   // Build tree
{
    tree[cur].l = l, tree[cur].r = r;
    tree[cur].mx = -INF;
    tree[cur].mn = INF;
    tree[cur].lz = 0;

    if(l == r)
    {
        if(hasWeight[rnk[l]])
            tree[cur].mn = tree[cur].mx = weight[rnk[l]];
    }
    else
    {
        int mid = (l + r) >> 1 ;
        Build(LC(cur), l, mid);
        Build(RC(cur), mid+1, r);
        Pushup(cur);
    }
}

int Query(int x, int l, int r)
{
    Pushdown(x);
    if(tree[x].l == l && tree[x].r == r)
        return tree[x].mx;

    int mid = (tree[x].l + tree[x].r) >> 1 ;

    if(r <= mid)
        return Query(LC(x), l, r);
    else if(mid < l)
        return Query(RC(x), l, r);
    else
        return max(Query(LC(x), l, mid), Query(RC(x), mid+1, r));
}

int QueryLCA(int a, int b)
{
    int ans = -INF;
    while(top[a] != top[b])
    {
        if(dep[top[a]] < dep[top[b]])
            swap(a, b);
        ans = max(ans, Query(1, tid[top[a]], tid[a]));
        a = fa[top[a]];
    }

    if(dep[a] > dep[b])
        swap(a, b);
    ans = max(ans, Query(1, tid[son[a]], tid[b]));

    if(ans == -INF)
        return 0;
    return ans;
}

void Modify(int x, int p, int val)
{
    Pushdown(x);
    if(tree[x].l == tree[x].r && tree[x].l == p)
    {
        tree[x].mn = tree[x].mx = val;
        return;
    }

    int mid = (tree[x].l + tree[x].r) >> 1;

    if(p <= mid)
        Modify(LC(x), p, val);
    else
        Modify(RC(x), p, val);

    Pushup(x);
}

void NegateSeg(int x, int l, int r)
{
    Pushdown(x);
    if(tree[x].l == l && tree[x].r == r)
    {
        tree[x].lz = 1;
        Negate(x);
        return;
    }

    int mid = (tree[x].l + tree[x].r) >> 1;

    if(r <= mid)
        NegateSeg(LC(x), l, r);
    else if(mid < l)
        NegateSeg(RC(x), l, r);
    else
        NegateSeg(LC(x), l, mid),
        NegateSeg(RC(x), mid+1, r);

    Pushup(x);
}
void NegateLCA(int a, int b)
{
    if(top[a] != top[b])
    {
        if(dep[top[a]] < dep[top[b]])
            swap(a, b);
        NegateSeg(1, tid[top[a]], tid[a]);
        a = fa[top[a]];
    }

    if(dep[a] > dep[b])
        swap(a, b);
    NegateSeg(1, tid[son[a]], tid[b]);
}

////////////////////////////////////////////////////////////
void Init()
{
    allocCnt = 0;
    edge.clear();

    for(int i = 1; i <= N; i++)
    {
        Adj[i].clear();
        hasWeight[i] = false;

        siz[i] = top[i] = 0;
        son[i] = -1;
        dep[i] = 0;
        tid[i] = rnk[i] = 0;
        fa[i] = 0;
    }

}

void PushDownEdge()
{
    for(vector<Edge>::iterator itr = edge.begin(); itr != edge.end() ; ++itr)
    {
        if(dep[itr->u] > dep[itr->v])
            swap(itr->u, itr->v);
        weight[itr->v] = itr->w;
        hasWeight[itr->v] = true;
    }
}

int main()
{
    int kase;
    char c[10];
    int u, v, w;

    getInteger(kase);

    while(kase--)
    {
        getInteger(N);
        Init();
        for(int i = 1; i < N; i++)
        {
            getInteger(u), getInteger(v), getInteger(w);
            edge.push_back((Edge)
            {
                u, v, w
            });
            Adj[u].push_back(v), Adj[v].push_back(u);
        }

        TD.RunDecomp(siz, top, son, dep, fa, tid, rnk, Adj);
        PushDownEdge();
        Build(1, 1, N);
        DEBUGARR(&weight[1], &weight[N+1]);
        DEBUGARR(&tree[1].l, &tree[2].l);

        bool bExt = false;
        while(!bExt)
        {
            scanf("%s", c);

            if(c[0] == 'D') // DONE
                bExt = true;
            else
            {
                getInteger(u), getInteger(v);
                switch(c[0])
                {
                case 'C':       // CHANGE
                    Modify(1, tid[edge[u-1].v], v);
                    break;
                case 'N':       // NEGATE
                    NegateLCA(u, v);
                    break;
                case 'Q':       // QUERY
                    putInteger(QueryLCA(u, v));
                    break;
                }
            }
        }
    }
    return 0;
}
