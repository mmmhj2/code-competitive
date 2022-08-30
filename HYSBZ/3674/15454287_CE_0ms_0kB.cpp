#include <algorithm>
#include <iostream>
#include <cstdio>
using namespace std;

typedef long long i64;
const int PREALLOC_SIZE = 10000000 + 10;
const int MAXN = 200000 + 10;

int N, M;

struct PersistentSegmentTree
{
    int root[MAXN], ls[PREALLOC_SIZE], rs[PREALLOC_SIZE];
    int fa[PREALLOC_SIZE], dep[PREALLOC_SIZE];
    int AllocCnt;
    int & sz = AllocCnt;

    void Build(int & k, int l, int r)
    {
        if(k == 0)
            k = ++AllocCnt;
        if(l == r)
        {
            fa[k] = l ;
            return ;
        }
        int mid = (l + r) >> 1 ;
        Build(ls[k], l, mid);
        Build(rs[k], mid+1, r);
    }

    void Modify(int l, int r, int x, int & y, int pos, int val)
    {
        y = ++AllocCnt;
        if(l == r)
        {
            fa[y] = val;
            dep[y] = dep[x];
            return;
        }
        ls[y] = ls[x], rs[y] = rs[x];
        int mid = (l + r) >> 1;
        if(pos <= mid)
            Modify(l, mid, ls[x], ls[y], pos, val);
        else
            Modify(mid + 1, r, rs[x], rs[y], pos, val);
    }

    int Query(int k, int l, int r, int pos)
    {
        if(l == r)
            return k;
        int mid = (l + r) >> 1;
        if(pos <= mid)
            return Query(ls[k], l, mid, pos);
        else
            return Query(rs[k], mid+1, r, pos);
    }

    void Add(int k, int l, int r, int pos)
    {
        if(l == r)
        {
            dep[k]++;
            return;
        }
        int mid = (l + r) >> 1;
        if(pos <= mid)
            Add(ls[k], l, mid, pos);
        else
            Add(rs[k], mid+1, r, pos);
    }

    int Find(int k, int x)
    {
        int p = Query(k, 1, N, x);
        if(x == fa[p])
            return p;
        return Find(k, fa[p]);
    }
}Main;


int main()
{
    scanf("%d%d", &N, &M);
    Main.Build(Main.root[0], 1, N);

    int op, a, b, k, last = 0;
    for(int i = 1; i <= M; i++)
    {
        scanf("%d", &op);
        switch(op)
        {
        case 1:
            Main.root[i] = Main.root[i-1];
            scanf("%d%d", &a, &b);
            a ^= last, b ^= last;
            a = Main.Find(Main.root[i], a), b = Main.Find(Main.root[i], b);

            if(Main.fa[a] == Main.fa[b])
                continue;
            if(Main.dep[a] > Main.dep[b])
                swap(a, b);

            Main.Modify(1, N, Main.root[i-1], Main.root[i], Main.fa[a], Main.fa[b]);

            if(Main.dep[a] == Main.dep[b])
                Main.Add(Main.root[i], 1, N, Main.fa[b]);

            break;
        case 2:
            scanf("%d", &k);
            k ^= last;
            Main.root[i] = Main.root[k];
            break;
        case 3:
            Main.root[i] = Main.root[i-1];
            scanf("%d%d", &a, &b);
            a ^= last, b ^= last;
            a = Main.Find(Main.root[i], a);
            b = Main.Find(Main.root[i], b);

            if(Main.fa[a] == Main.fa[b])
                last = 1;
            else
                last = 0;

            printf("%d\n", last);
            break;
        default:
            ;
        }
    }

    return 0;
}
