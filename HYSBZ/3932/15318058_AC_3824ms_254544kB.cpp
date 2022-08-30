#include <algorithm>
#include <iostream>
#include <cstdio>
#pragma GCC diagnostic ignored "-Wformat-extra-args"
#pragma GCC diagnostic ignored "-Wformat"
using namespace std;

typedef long long i64;
const int MAXN = 100000 + 50;

int discrete[MAXN], disLen;
int M, N;
struct Task
{
    int time, priority, delta;

    static bool CmpTime(const Task & lhs, const Task & rhs)
    {
        return lhs.time < rhs.time;
    }
} tsk[MAXN * 2];


const int PREALLOCATE_MULTI = 128;
const int PREALLOCATE_SIZE = MAXN * PREALLOCATE_MULTI + 10;

typedef struct tagNode
{
    int tot;
    i64 sum;
    tagNode * ch[2];
} node, *pnode;

node  data[PREALLOCATE_SIZE];
pnode root[MAXN];
pnode NIL = &data[0];
pnode allocCnt = NIL;

/*
PersistentSegmentTree()
{
    NIL = &data[0];
    allocCnt = &data[0];
    for(int i = 0; i < MAXN; i++)
        root[i] = NIL;
}
*/

pnode AllocNew()
{
    pnode p = ++allocCnt;
    p->ch[0] = NIL;
    p->ch[1] = NIL;
    p->tot = p->sum = 0;
    return p;
}

pnode build(int l, int r)
{
    pnode rt = AllocNew();

    if(l >= r)
        return rt;
    int mid = (l + r) >> 1 ;
    rt->ch[0] = build(l, mid);
    rt->ch[1] = build(mid + 1, r);
    return rt;
}

pnode update(pnode x, int l, int r, int toUpdate, int delta)
{
    pnode rt = AllocNew();

    rt->ch[0] = x->ch[0], rt->ch[1] = x->ch[1];
    rt->sum = x->sum + 1LL * discrete[toUpdate] * delta;
    rt->tot = x->tot + delta;

    if(l == r)
        return rt;

    int mid = (l + r) >> 1;
    if(toUpdate <= mid)
        rt->ch[0] = update(x->ch[0], l, mid, toUpdate, delta);
    else
        rt->ch[1] = update(x->ch[1], mid + 1, r, toUpdate, delta);
    return rt;
}

/*
void output(pnode rt)
{
    cout << "(" << rt->l << "," << rt->r << "," << rt->tot << "," << rt->sum << ")\n";
    if(rt->ch[0] != NULL)
        output(rt->ch[0]);
    if(rt->ch[1] != NULL)
        output(rt->ch[1]);
}
*/

i64 query(pnode x, int l, int r, i64 k)
{
    if(k >= x->tot)
        return x->sum;
    if(l == r)
        return (x->sum / x->tot * k);

    int mid = (l + r) >> 1;

    if(x->ch[0]->tot >= k)
        return query(x->ch[0], l, mid, k);
    else
        return query(x->ch[1], mid + 1, r, k - x->ch[0]->tot) + x->ch[0]->sum;
}

void prepare()
{
    //cin >> M >> N ;
    scanf("%d%d", &M, &N);
    for(int i = 1; i <= M; i++)
    {
        int s, e, p;
        //cin >> s >> e >> p ;
        scanf("%d%d%d", &s, &e, &p);
        tsk[i * 2 - 1] = (Task)
        {
            s, p, 1
        };
        tsk[i * 2]     = (Task)
        {
            e + 1, p, -1
        };
        discrete[i] = p;
    }
    sort(discrete + 1, discrete + 1 + M);
    disLen = unique(discrete + 1, discrete + 1 + M) - (discrete + 1);

    M = M * 2;
    sort(tsk + 1, tsk + 1 + M, Task::CmpTime);
    root[0] = build(1, disLen);

    for(int i = 1; i < MAXN; i++)
        root[i] = root[0];

    for(int i = 1; i <= M; i++)
    {
        int toUpdate = lower_bound(discrete + 1, discrete + disLen + 1, tsk[i].priority) - discrete;
        const int & tm = tsk[i].time;

        if(i == 1 || tm != tsk[i - 1].time)
        {
            if(i != 1)
                for(int t = tsk[i - 1].time + 1; t < tm; t++)
                    root[t] = root[t - 1];
            root[tm] = update(root[tm - 1], 1, disLen, toUpdate, tsk[i].delta);
        }
        else
        {
            root[tm] = update(root[tm], 1, disLen, toUpdate, tsk[i].delta);
        }
    }
}

int main()
{
    //freopen("query7.in", "r", stdin);
    //freopen("ans.txt", "w", stdout);
    i64 x, a, b, c, k, pre(1LL);

    prepare();

    for(int i = 1; i <= N; i++)
    {
        //cin >> x >> a >> b >> c ;
        scanf("%lld%lld%lld%lld", &x, &a, &b, &c);
        k = 1 + (i64)(a * pre + b) % c;
        i64 ans = query(root[x], 1, disLen, k);
        //cout << (pre = Main.query(Main.root[x], 1, disLen, k)) << endl ;
        printf("%lld\n", ans);
        pre = ans;
    }

    return 0;
}
