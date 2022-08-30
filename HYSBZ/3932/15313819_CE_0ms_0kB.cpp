#include <algorithm>
#include <iostream>
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
}tsk[MAXN * 2];


struct PersistentSegmentTree
{
    static const int MAXN = 100000 + 50;
    static const int PREALLOCATE_MULTI = 150;
    static const int PREALLOCATE_SIZE = MAXN * PREALLOCATE_MULTI + 10;

    typedef struct tagNode
    {
        int tot;
        i64 sum;
        tagNode * ch[2];
    }node, *pnode;

    node  data[PREALLOCATE_SIZE];
    pnode root[MAXN];
    pnode allocCnt;


    PersistentSegmentTree()
    {
        allocCnt = &data[0];
    }

    void build(pnode & rt, int l, int r)
    {
        rt = allocCnt++;
        rt->sum = 0, rt->tot = 0;

        if(l == r)
            return;
        int mid = (l + r) >> 1 ;
        build(rt->ch[0], l, mid);
        build(rt->ch[1], mid + 1, r);
    }

    void update(pnode & x, pnode & y, int l, int r, int toUpdate, int delta)
    {
        x = allocCnt++;
        *x = *y;

        x->sum = x->sum + 1LL * discrete[toUpdate] * delta;
        x->tot = x->tot + delta;

        if(l == r)
            return;

        int mid = (l + r) >> 1;
        if(toUpdate <= mid)
            update(x->ch[0], y->ch[0], l, mid, toUpdate, delta);
        else
            update(x->ch[1], y->ch[1], mid+1, r, toUpdate, delta);
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
            return query(x->ch[1], mid+1, r, k - x->ch[0]->tot) + x->ch[0]->sum;
    }

}Main;

void prepare()
{
    //cin >> M >> N ;
    scanf("%d%d", &M, &N);
    for(int i = 1; i <= M; i++)
    {
        int s, e, p;
        //cin >> s >> e >> p ;
        scanf("%d%d%d", &s, &e, &p);
        tsk[i*2 - 1] = (Task){s  ,p, 1};
        tsk[i*2]     = (Task){e+1,p,-1};
        discrete[i] = p;
    }
    sort(discrete+1, discrete+1+M);
    disLen = unique(discrete+1, discrete+1+M) - (discrete + 1);
    M *= 2;
    sort(tsk+1, tsk+1+M, Task::CmpTime);

    Main.build(Main.root[0], 1, disLen);

    for(int i = 1; i <= M; i++)
    {
        int toUpdate = lower_bound(discrete+1, discrete + disLen + 1, tsk[i].priority) - discrete;
        const int & tm = tsk[i].time;

        if(i == 1 || tm != tsk[i-1].time)
        {
            if(i != 1)
                for(int t = tsk[i-1].time+1; t < tm; t++)
                    Main.root[t] = Main.root[t-1];
            Main.update(Main.root[tm], Main.root[tm-1], 1, disLen, toUpdate, tsk[i].delta);
        }
        else
        {
            PersistentSegmentTree::pnode tmp;
            Main.update(tmp, Main.root[tm], 1, disLen, toUpdate, tsk[i].delta);
            Main.root[tm] = tmp;
        }
    }
}

int main()
{
    i64 x, a, b, c, k, pre(1LL);

    prepare();

    for(int i = 1; i <= N; i++)
    {
        //cin >> x >> a >> b >> c ;
        scanf("%lld%lld%lld%lld", &x, &a, &b, &c);
        k = 1 + (i64)(a * pre + b) % c;
        //cout << (pre = Main.query(Main.root[x], 1, disLen, k)) << endl ;
        printf("%lld\n", pre = Main.query(Main.root[x], 1, disLen, k));
    }

    return 0;
}
