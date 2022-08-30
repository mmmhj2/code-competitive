#include <iostream>
#include <cstdio>
using namespace std;

int N, M;
namespace DynamicSegmentTree
{
    static const int PREALLOCATE_SIZE = 1E5 * 32 + 10;
    typedef struct _tagNode
    {
        _tagNode * ch[2];
        int64_t lz, sum;
    }node, *pnode;
    node preAlloc[PREALLOCATE_SIZE];
    pnode allocCnt;
    pnode root;
    pnode NIL;

    pnode AllocNew()
    {
        pnode ret = ++allocCnt;
        ret->ch[0] = ret->ch[1] = NIL;
        ret->lz = 0;
        ret->sum = 0;
        return ret;
    }

    void initialize()
    {
        allocCnt = &preAlloc[0];
        NIL = &preAlloc[0];
        NIL->ch[0] = NIL->ch[1] = NIL;
        root = AllocNew();
    }

    void Pushup(pnode rt)
    {
        rt->sum = rt->ch[0]->sum + rt->ch[1]->sum;
    }

    void Pushdown(int l, int r, pnode rt)
    {
        int m = (l + r) >> 1;
        rt->ch[0]->lz += rt->lz;
        rt->ch[0]->sum += 1LL * rt->lz * (m - l + 1);
        rt->ch[1]->lz += rt->lz;
        rt->ch[1]->sum += 1LL * rt->lz * (r - m);
        rt->lz = 0;
    }


    void Modify(int L, int R, int val, pnode & rt = root, int l = 1, int r = N)
    {
        if(L <= l && r <= R)
        {
            rt->sum += 1LL * val * (r - l + 1);
            rt->lz += val;
            return;
        }
        if(rt->ch[0] == NIL || rt->ch[1] == NIL)
            rt->ch[0] = AllocNew(), rt->ch[1] = AllocNew();

        Pushdown(l, r, rt);
        int m = (l + r) >> 1;

        if(L <= m)
            Modify(L, R, val, rt->ch[0], l, m);
        if(m < R)
            Modify(L, R, val, rt->ch[1], m+1, r);
        Pushup(rt);
    }

    int64_t Query(int L, int R, pnode rt = root, int l = 1, int r = N)
    {
        if(rt == NIL)
            return 0;
        if(L <= l && r <= R)
            return rt->sum;

        if(rt->ch[0] == NIL || rt->ch[1] == NIL)
            rt->ch[0] = AllocNew(), rt->ch[1] = AllocNew();
        Pushdown(l, r, rt);

        int m = (l + r) >> 1;
        int64_t ret = 0;
        if(L <= m)
            ret += Query(L, R, rt->ch[0], l, m);
        if(m < R)
            ret += Query(L, R, rt->ch[1], m+1, r);
        return ret;
    }
};
using DynamicSegmentTree::root;
int main()
{
    int kase;
    scanf("%d", &kase);
    while(kase--)
    {
        DynamicSegmentTree::initialize();
        scanf("%d%d", &N, &M);

        for(int i = 1; i <= M; i++)
        {
            int op, x, y, val;
            scanf("%d", &op);
            if(op == 0)
            {
                scanf("%d%d%d", &x, &y, &val);
                DynamicSegmentTree::Modify(x, y, val);
            }
            else
            {
                scanf("%d%d", &x, &y);
                printf("%lld\n", DynamicSegmentTree::Query(x, y));
            }
        }
    }
    return 0;
}
