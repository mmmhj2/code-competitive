#include <algorithm>
#include <iostream>
#include <cstring>
#include <cstdio>
using namespace std;

typedef long long i64;

const int MAXN = 100000 + 100;

struct CDQNode
{
    int x, y, z;
    int cnt, ans;
    static bool cmpX(const CDQNode & lhs, const CDQNode & rhs)
    {
        if(lhs.x != rhs.x)
            return lhs.x < rhs.x;
        if(lhs.y != rhs.y)
            return lhs.y < rhs.y;
        return lhs.z < rhs.z;
    }

    static bool cmpY(const CDQNode & lhs, const CDQNode & rhs)
    {
        if(lhs.y != rhs.y)
            return lhs.y < rhs.y;
        if(lhs.z != rhs.z)
            return lhs.z < rhs.z;
        return lhs.x < rhs.x;
    }
}q[MAXN], aux[MAXN];

int N, K;
//int ans[MAXN];
long long sum[MAXN];

struct BinaryIndexedTree
{
    int data[MAXN * 2];
    int N;
    //#define LoBit(x) (x & (-x));
    inline static int LoBit(int x)
    {

        return (x & -x);
    }

    void add(int id, int delta)
    {
        while(id <= this->N)
            data[id] += delta,
            id += LoBit(id);
    }

    int query(int id)
    {
        int ans = 0;
        while(id)
            ans += data[id],
            id -= LoBit(id);
        return ans ;
    }
};

BinaryIndexedTree BIT;


void CDQProc(int l, int r)
{
    if(l == r)
    {
        q[l].ans += (q[l].cnt-1);
        return ;
    }

    int mid = (l + r) >> 1;

    CDQProc(l, mid);
    CDQProc(mid+1, r);
    sort(q+l    , q+mid+1   , CDQNode::cmpY);
    sort(q+mid+1, q+r+1     , CDQNode::cmpY);

    int j = l;
    for(int i = mid + 1; i <= r; i++)
    {
        while(j <= mid && q[j].y <= q[i].y)
            BIT.add(q[j].z, q[j].cnt),
            j++;
        q[i].ans += BIT.query(q[i].z);
    }

    for(int i = l; i < j; i++)
        BIT.add(q[i].z, -q[i].cnt);

    merge(q+l, q+mid+1, q+mid+1, q+r+1, aux, CDQNode::cmpY);
    copy(aux, &aux[r-l+1], q+l);
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int tot = 0;
    cin >> N >> K ;
    BIT.N = K ;

    for(int i = 1; i <= N; i++)
        cin >> q[i].x >> q[i].y >> q[i].z ,
        q[i].ans = 1;
    sort(&q[1], &q[N+1], CDQNode::cmpX);

    // Discretization & Merging
    for(int i = 1; i <= N; i++)
        if(i != 1 && q[i].x == q[i-1].x && q[i].y == q[i-1].y && q[i].z == q[i-1].z)
            q[tot].cnt++;
        else
            q[++tot] = q[i] ,q[tot].cnt = 1;

    CDQProc(1, tot);
    sort(&q[1], &q[tot+1], CDQNode::cmpX);

    for(int i = 1; i <= tot; i++)
        sum[q[i].ans] += q[i].cnt;

    for(int i = 1; i <= N; i++)
        cout << sum[i] << endl ;

    return 0;
}
