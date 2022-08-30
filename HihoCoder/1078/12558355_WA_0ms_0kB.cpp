#include <iostream>
using namespace std;

const int MAXN = 100000;

struct node
{
    int l, r;
    int lazyTag;
    int val;
} tree[MAXN*4+10];

int build(int, int, int = 1);
int insrt(int, int, int);
int modify(int, int, int, int);
int query(int, int, int);
int pushDown(int);
int pushUp(int);

int main()
{
    int N, Q;
    cin >> N ;
    build(1, N);
    for(int i = 1; i <= N; i++)
    {
        int t;
        cin >> t;
        modify(1, i, i, t);
    }
    cin >> Q;
    int op1, op2, op3, op4;
    while(Q--)
    {
        cin >> op1;
        if(op1 == 0)
        {
            cin >> op2 >> op3;
            cout << query(1, op2, op3) << endl ;
        }
        else if(op1 == 1)
        {
            cin >> op2 >> op3 >> op4;
            modify(1, op2, op3, op4);
        }
    }
}

int pushDown(int i)
{
    node & rt = tree[i];
    node & lc = tree[i*2];
    node & rc = tree[i*2+1];
    if(rt.lazyTag >= 0)      // 下传懒惰标记
    {
        lc.lazyTag = rt.lazyTag;
        lc.val = lc.lazyTag * (lc.r - lc.l + 1);

        rc.lazyTag = rt.lazyTag;
        rc.val = rc.lazyTag * (rc.r - rc.l + 1);

        rt.lazyTag = -1;
    }

    //rt.val = lc.val + rc.val;   //更新根节点
}

int pushUp(int i)
{
    tree[i].val = tree[i*2].val + tree[i*2+1].val;
}

int build(int l, int r, int i)
{
    tree[i].l = l, tree[i].r = r;
    tree[i].val = 0;
    tree[i].lazyTag = -1;

    if(l == r)
        return 0;
    int mid = (l+r) >> 1;
    return build(l, mid, i*2) + build(mid+1, r, i*2+1);
}

int modify(int i, int l, int r, int val)
{
    node & rt = tree[i];
    if(r < rt.l || rt.r < l)
        return 0;
    if(l <= rt.l && rt.r <= r)
    {
        rt.lazyTag = val;
        rt.val = (r-l+1) * val;
        return 0;
    }
    else
    {
        pushDown(i);
        modify(i*2, l, r, val);
        modify(i*2+1, l, r, val);
        pushUp(i);
    }
    return 0;
}

int query(int i, int l, int r)
{
    node & rt = tree[i];
    if(r < rt.l || rt.r < l)
        return 0;
    if(l <= rt.l && rt.r <= r)
        return rt.val;
    else
    {
        pushDown(i);
        int ans1 = query(i*2, l, r);
        int ans2 = query(i*2+1, l, r);
        pushUp(i);
        return ans1 + ans2;
    }
    return 0;
}
