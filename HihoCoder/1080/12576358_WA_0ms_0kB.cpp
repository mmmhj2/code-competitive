#include <iostream>

using namespace std;

const int MAXN = 1e5;

struct tagNode
{
    int l, r;
    int sum;
    int lztagSet, lztagRaise;
};

tagNode tree[MAXN*4+10];

void PushDown(int i);
void PushUp(int i);
void build(int l, int r, int i = 1);
void modifyRaise(int i, int l, int r, int val);
void modifySet(int i, int l, int r, int val);
int query(int i, int l, int r);

int main()
{
    int N, M, t;
    int op1, op2, op3, op4;
    ios::sync_with_stdio(0);    cin.tie(0);
    cin >> N >> M;  N++;
    build(1, N);
    for(int i = 1; i <= N; i++)
    {
        cin >> t;
        modifySet(1, i, i, t);
    }

    for(int i = 1; i <= M; i++)
    {
        cin >> op1 >> op2 >> op3 >> op4;
        switch(op1)
        {
        case 0:
            modifyRaise(1, op2+1, op3+1, op4);
            break;
        case 1:
            modifySet(1, op2+1, op3+1, op4);
            break;
        }
        cout << query(1, 1, N) << endl;
    }
}

void PushDown(int i)
{
    tagNode & rt = tree[i];
    if(rt.r - rt.l == 0)
        return;
    tagNode & lc = tree[i*2];
    tagNode & rc = tree[i*2+1];
    if(rt.lztagSet >= 0)
    {
        rc.lztagSet = lc.lztagSet = rt.lztagSet;
        rc.lztagRaise = lc.lztagRaise = 0;
        rt.lztagSet = -1;

        lc.sum = (lc.r-lc.l+1)*lc.lztagSet;
        rc.sum = (rc.r-rc.l+1)*rc.lztagSet;
    }
    if(rt.lztagRaise != 0)
    {
        lc.lztagRaise += rt.lztagRaise;
        rc.lztagRaise += rt.lztagRaise;

        lc.sum += (lc.r-lc.l+1)*rt.lztagRaise;
        rc.sum += (rc.r-rc.l+1)*rt.lztagRaise;

        rt.lztagRaise = 0;

    }
}

void PushUp(int i)
{
    tree[i].sum = tree[i*2].sum + tree[i*2+1].sum;
}

void build(int l, int r, int i)
{
    tree[i].l = l,  tree[i].r = r;
    tree[i].lztagRaise = 0;
    tree[i].lztagSet = -1;

    if(l == r)
        return;
    int mid = (l+r) >> 1;
    build(l, mid, i*2);
    build(mid+1, r, i*2+1);
}

void modifyRaise(int i, int l, int r, int val)
{
    tagNode & rt = tree[i];
    if(r < rt.l || rt.r < l)
        return ;
    if(l <= rt.l && rt.r <= r)
    {
        rt.lztagRaise = val;
        rt.sum += (rt.r - rt.l + 1) * val;
        return ;
    }
    PushDown(i);
    modifyRaise(i*2, l, r, val);
    modifyRaise(i*2+1, l, r, val);
    PushUp(i);
}

void modifySet(int i, int l, int r, int val)
{
    tagNode & rt = tree[i];
    if(r < rt.l || rt.r < l)
        return ;
    if(l <= rt.l && rt.r <= r)
    {
        rt.lztagSet = val;
        rt.sum = (rt.r - rt.l + 1) * val;
        return ;
    }
    PushDown(i);
    modifySet(i*2, l, r, val);
    modifySet(i*2+1, l, r, val);
    PushUp(i);
}

int query(int i, int l, int r)
{
    tagNode & rt = tree[i];
    if(r < rt.l || rt.r < l)
        return 0;
    if(l <= rt.l && rt.r <= r)
        return rt.sum;
    PushDown(i);
    int ans1 = query(i*2, l, r);
    int ans2 = query(i*2+1, l, r);
    PushUp(i);
    return ans1 + ans2;
}


