#include <iostream>
#include <cstdio>
#include <map>
using namespace std;

int N, Q;

const int PREALLOCATE_SIZE = 100010 * 32;
typedef struct _tagNode
{
    _tagNode *lson, *rson;
    int sum;
    int lsum ,rsum;
    int pos, len;   // POS : the position of the next possible plug
}node, *pnode;
node preAlloc[PREALLOCATE_SIZE];
pnode allocCnt, NIL, root;

pnode AllocNew(int l = 0, int r = 0)
{
    pnode p = ++allocCnt;
    p->lson = p->rson = NIL;
    p->sum = p->len = 0;
    p->lsum = p->rsum = r - l + 1;
    return p;
}

void initialize()
{
    root = NIL = allocCnt = &preAlloc[0];
}

inline int getMid(int L, int R)
{
    if((L + R) & 1)
        return ((L + R) >> 1) + 1;
    return (L + R) >> 1;
}

void Pushup(pnode p, int l, int r)
{
    int mid = (l + r) >> 1 ;
    int lcl = p->lson->lsum, lcr = p->lson->rsum, lclen = p->lson->len, lcp = p->lson->pos;
    int rcl = p->rson->lsum, rcr = p->rson->rsum, rclen = p->rson->len, rcp = p->rson->pos;

    if(p->lson == NIL)
        lcl = lcr = lclen = mid - l + 1, lcp = getMid(l, mid);
    if(p->rson == NIL)
        rcl = rcr = rclen = r - mid, rcp = getMid(mid + 1, r);

    p->sum = p->lson->sum + p->rson->sum;
    p->len = max(lcr + rcl, max(lclen, rclen));

    if(p->len == rclen)
        p->pos = rcp;
    else if (p->len == lclen)
        p->pos = lcp;
    else
        p->pos = getMid(mid - lcr + 1, mid + rcl);

    if(lcl == mid - l + 1)
        p->lsum = lcl + rcl;
    else
        p->lsum = lcl;
    if(rcr == r - mid)
        p->rsum = lcr + rcr;
    else
        p->rsum = rcr;
}

void Modify(int toModify, int val, pnode & p = root, int l = 1, int r = N)
{
    if(p == NIL)
        p = AllocNew();
    if(l == r)
    {
        if(val)             // Plug in
            p->pos = -1;
        else                // Remove the plug
            p->pos = l;
        p->lsum = p->rsum = p->len = 1 - val;
        p->sum = val;
        return;
    }

    int mid = (l + r) >> 1;
    if(toModify <= mid)
        Modify(toModify, val, p->lson, l, mid);
    else
        Modify(toModify, val, p->rson, mid+1, r);
    Pushup(p, l, r);
    return;
}

int Query(int ql, int qr, pnode p = root, int l = 1, int r = N)
{
    if(p == NIL)
        return 0;
    if(l == ql && r == qr)
        return p->sum;

    int mid = (l + r) >> 1;

    if(qr <= mid)
        return Query(ql, qr, p->lson, l, mid);
    else if(mid < ql)
        return Query(ql, qr, p->rson, mid+1, r);
    else
        return Query(ql, mid, p->lson, l, mid) + Query(mid+1, qr, p->rson, mid+1, r);
}

map <int, int> usedPlug;
int k, l, r;
int main()
{
    initialize();
    bool isFirst = true;
    scanf("%d%d", &N, &Q);

    for(int i = 1; i <= Q; i++)
    {
        scanf("%d", &k);
        if(!k)
        {
            int l, r;
            scanf("%d%d", &l, &r);
            printf("%d\n", Query(l, r));
        }
        else
        {
            if(usedPlug[k])
            {
                Modify(usedPlug[k], 0);
                usedPlug[k] = 0;
            }
            else
            {
                int cnt;
                if(isFirst)
                    cnt = getMid(1, N), isFirst = false;
                else
                    cnt = root->pos;
                Modify(cnt, 1);
                usedPlug[k] = cnt;
            }
        }
    }

    return 0;
}
