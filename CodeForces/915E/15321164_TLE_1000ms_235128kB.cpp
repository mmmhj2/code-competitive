#include <iostream>

using namespace std;

int N, M;

struct DynamicSegmentTree
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

    pnode AllocNode()
    {
        pnode ret = ++allocCnt;
        ret->ls = NIL, ret->rs = NIL;
        ret->lz = -1;
        ret->sum = 0;
        return ret;
    }

    DynamicSegmentTree()
    {
        allocCnt = &preAlloc[0];
        NIL = &preAlloc[0];
        root = AllocNode();
    }

    void Pushup(pnode cur)
    {
        cur->sum = cur->ls->sum + cur->rs->sum;
    }

    void Pushdown(int l, int r, pnode cur)
    {

        if(cur->lz != -1)
        {
            int m = (l + r) >> 1 ;
            if(l != r)
            {
                if(cur->ls == NIL)
                    cur->ls = AllocNode();
                if(cur->rs == NIL)
                    cur->rs = AllocNode();
                cur->ls->lz = cur->lz;
                cur->rs->lz = cur->lz;
                cur->ls->sum = (m - l + 1) * cur->lz;
                cur->rs->sum = (r - m) * cur->lz;
            }
            cur->lz = -1;
        }
    }


    void Modify(int L, int R, int val, pnode & cur, int l = 1, int r = N)
    {
        if(cur == NIL)
            cur = AllocNode();
        if(L <= l && r <= R)
        {
            cur->lz = val;
            cur->sum = val * (r - l + 1);
            return;
        }

        Pushdown(l, r, cur);

        int m = (l + r) >> 1 ;

        if(L <= m)
            Modify(L, R, val, cur->ls, l, m);
        if(m < R)
            Modify(L, R, val, cur->rs, m+1, r);

        Pushup(cur);
    }
}Main;

int main()
{
    int l, r, k;

    cin >> N >> M ;

    for(int i = 1; i <= M; i++)
    {
        cin >> l >> r >> k ;
        if(k == 1)
            Main.Modify(l, r, 1, Main.root);
        else
            Main.Modify(l, r, 0, Main.root);
        cout << N - Main.root->sum << endl ;
    }

    return 0;
}
