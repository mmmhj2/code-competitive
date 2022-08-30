#include <iostream>
#include <algorithm>
#include <map>
using namespace std;

const int MAXN = 100000;

map <int, int> hashmap;

struct node
{
    int l, r;
    int lazyTag;
    int color;
} tree[MAXN*2*4+10];

int tmp[2][MAXN*2+10];
int ans;
bool app[MAXN+10];

int build(int, int, int = 1);
int insrt(int, int, int, int);
int modify(int, int, int, int);
int query(int, int, int);
int pushDown(int);
int pushUp(int);

int main()
{
    int N, L;
    cin >> N >> L;

    for(int i = 1; i <= N; i++)
        cin >> tmp[0][i] >> tmp[0][i+N];

    copy(&tmp[0][1], &tmp[0][N*2+1], &tmp[1][1]);
    sort(&tmp[0][1], &tmp[0][N*2+1]);
    int cnt = unique(&tmp[0][1], &tmp[0][N*2+1])-tmp[0];

    for(int i = 1; i <= N*2; i++)
    {
        int loc = lower_bound(&tmp[0][1], &tmp[0][cnt+1], tmp[1][i]) - tmp[0];
        hashmap[tmp[1][i]] = loc;
    }

    //for(int i = 1; i <= N*2; i++)
    //    cout << "[HASH] "<< tmp[1][i] << " " << hashmap[tmp[1][i]] << endl;


    build(1, cnt, 1);
    for(int i = 1; i <= N; i++)
    {
        modify(1, hashmap[tmp[1][i]], hashmap[tmp[1][i+N]], i);
    }
    query(1, 1, cnt);
    cout << ans << endl;
    return 0;
}

int pushDown(int i)
{
    node & rt = tree[i];
    node & lc = tree[i*2];
    node & rc = tree[i*2+1];
    if(rt.lazyTag >= 0)      // 下传懒惰标记
    {
        lc.lazyTag = rt.lazyTag;
        lc.color = rt.color;

        rc.lazyTag = rt.lazyTag;
        rc.color = rt.color;

        rt.lazyTag = -1;
    }
    return 0;
}

int pushUp(int i)
{
    node & rt = tree[i];
    node & lc = tree[i*2];
    node & rc = tree[i*2+1];
    if(lc.color == rc.color)
        rt.color = lc.color;
    else
        rt.color = -1;
    return rt.color;
}

int build(int l, int r, int i)
{
    tree[i].l = l, tree[i].r = r;
    tree[i].color = 0;
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
        rt.color = val;
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
        if(rt.color > 0)
        {
            if(!app[rt.color])
                ans++, app[rt.color]++;
            return 0;
        }
    pushDown(i);
    query(i*2, l, r);
    query(i*2+1, l, r);
    pushUp(i);
    return 0;
}
