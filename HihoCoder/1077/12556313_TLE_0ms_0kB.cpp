#include <cstdio>
#include <climits>
#include <iostream>
#include <algorithm>
using namespace std;

const int MAXN = 1000000;

int N, Q;

struct node
{
    int l, r;
    int val;
}tree[4*MAXN+10];

void build(int, int, int);
void insrt(int, int, int);
int  query(int, int, int);

int main()
{
    ios::sync_with_stdio(0);    cin.tie(0);
    cin >> N;
    //scanf("%d", &N);
    build(1, 1, N);
    {
        int p;
        for(int i = 1; i <= N; i++)
        {
            cin >> p ;
            //scanf("%d", &p);
            insrt(1, i, p);
        }
    }
    cin >> Q;
    //scanf("%d", &Q);
    int op1, op2, op3;
    while(Q--)
    {
        cin >> op1 >> op2 >> op3;
        //scanf("%d%d%d", &op1, &op2, &op3);
        switch(op1)
        {
        case 0:
            cout << query(1, op2, op3) << endl;
            //printf("%d\n", query(1, op2, op3));
            break;
        case 1:
            insrt(1, op2, op3);
            break;
        }
    }
    return 0;
}

void build(int rt, int l, int r)
{
    tree[rt].l = l;
    tree[rt].r = r;
    tree[rt].val = INT_MAX;

    if(l == r)
        return;
    int mid = (l+r) >> 1;
    build(rt*2  , l, mid);
    build(rt*2+1, mid+1, r);
}

void insrt(int i, int k, int val)
{
    node & rt = tree[i];
    if(k < rt.l || rt.r < k)
        return;
    if(rt.l == k && rt.r == k)
    {
        rt.val = val;
        return;
    }
    insrt(i*2, k, val);
    insrt(i*2+1, k, val);
    rt.val = min(tree[i*2].val, tree[i*2+1].val);
}

int query(int i, int l, int r)
{
    node & rt = tree[i];
    if(r < rt.l || rt.r < l)
        return INT_MAX;

    if(l <= rt.l && rt.r <= r)
        return rt.val;
    return min(query(i*2, l, r), query(i*2+1, l, r));
}
