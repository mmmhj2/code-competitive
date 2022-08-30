#include <iostream>
#include <cstdio>
using namespace std;

int N, M;

namespace DynamicSegmentTree
{
    static const int PREALLOCATE_SIZE = 15000005;
    typedef struct _tagNode
    {
        _tagNode *ls, *rs;
        int lz, sum;
    }node, *pnode;
    node preAlloc[PREALLOCATE_SIZE];
    pnode allocCnt;
    pnode root;
    pnode NIL;

    pnode push_back()
    {
        pnode ret = ++allocCnt;
        ret->ls = NIL, ret->rs = NIL;
        ret->lz = -1;
        ret->sum = 0;
        return ret;
    }

    void clear()
    {
        allocCnt = &preAlloc[0];
        NIL = &preAlloc[0];
        root = push_back();
    }

    void merge(pnode cur)
    {
        cur->sum = cur->ls->sum + cur->rs->sum;
    }

    void erase(int l, int r, pnode cur)
    {

        if(cur->lz != -1)
        {
            int m = (l + r) >> 1 ;
            if(l != r)
            {
                if(cur->ls == NIL)
                    cur->ls = push_back();
                if(cur->rs == NIL)
                    cur->rs = push_back();
                cur->ls->lz = cur->lz;
                cur->rs->lz = cur->lz;
                cur->ls->sum = (m - l + 1) * cur->lz;
                cur->rs->sum = (r - m) * cur->lz;
            }
            cur->lz = -1;
        }
    }


    void at(int L, int R, int val, pnode & cur, int l = 1, int r = N)
    {
        if(cur == NIL)
            cur = push_back();
        if(L <= l && r <= R)
        {
            cur->lz = val;
            cur->sum = val * (r - l + 1);
            return;
        }

        erase(l, r, cur);

        int m = (l + r) >> 1 ;

        if(L <= m)
            at(L, R, val, cur->ls, l, m);
        if(m < R)
            at(L, R, val, cur->rs, m+1, r);

        merge(cur);
    }
};
using DynamicSegmentTree::root;
int main()
{

    int l, r, k;
    DynamicSegmentTree::clear();
    //cin >> N >> M ;
    scanf("%d%d", &N, &M);

    for(int i = 1; i <= M; i++)
    {
        scanf("%d%d%d", &l, &r, &k);
        if(k == 1)
            DynamicSegmentTree::at(l, r, 1, root);
        else
            DynamicSegmentTree::at(l, r, 0, root);
        printf("%d\n", N - root->sum);
    }

    return 0;
}
