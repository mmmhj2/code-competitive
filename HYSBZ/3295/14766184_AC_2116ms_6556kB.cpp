
#include <algorithm>
#include <iostream>
#include <cstring>
#include <cstdio>
using namespace std;

typedef long long i64;

const int MAXN = 110000 ;

struct CDQNode
{
    int x, y, id;
    bool operator < (const CDQNode & rhs) const
    {
        if(x == rhs.x)
            return y < rhs.y;
        return x < rhs.x;
    }
}order[MAXN], aux[MAXN];

int N, M ;

struct BinaryIndexedTree
{
    int data[MAXN];

    #define LoBit(x) (x & (-x));
    /*inline static int LoBit(int x)
    {
        return (x & -x);
    }*/

    void add(int id, int delta)
    {
        while(id <= N)
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
int aend;
int pos[MAXN], a[MAXN];
bool clrFlag[MAXN];
int ans[MAXN];
i64 sum[MAXN];

void CDQProc(int l, int r)
{
    if(l == r)
        return ;

    int mid = (l + r) >> 1;

    CDQProc(l, mid);
    CDQProc(mid+1, r);
    sort(order + l, order + mid + 1);
    sort(order + mid + 1, order + r + 1);
    int j = l;
    for(int i = mid + 1; i <= r; i++)
    {
        for(; j <= mid && order[j].x < order[i].x; j++)
            BIT.add(order[j].y, 1);
        ans[order[i].id] += BIT.query(order[i].y);
    }

    for(int i = l; i < j; i++)
        BIT.add(order[i].y, -1);

    merge(order + l, order + mid + 1, order + mid + 1, order + r + 1, aux);
    //copy(aux, &aux[r-l+1], order + l);
    for(int i = 0; i < r - l + 1; i ++)
        order[i+l] = aux[i];
}

int main()
{
    int t;
    //cin >> N >> M ;
    scanf("%d%d", &N, &M);
    aend = M;

    for(int i = 1; i <= N; i++)
        //cin >> t,   pos[t] = i;
        scanf("%d", &t),   pos[t] = i;

    for(int i = 1; i <= M; i++)
        //cin >> a[i], clrFlag[a[i]] = true;
        scanf("%d", &a[i]), clrFlag[a[i]] = true;

    for(int i = 1; i <= N; i++)
        if(!clrFlag[i])
            a[++aend] = i;

    for(int i = N; i >= 1; i--)
        order[i].id = i,
        order[N-i+1].x = pos[a[i]],
        order[N-i+1].y = N+1-a[i];
    CDQProc(1, N);

    for(int i = N; i >= 1; i--)
        order[i].id = i,
        order[N-i+1].x = N+1-pos[a[i]],
        order[N-i+1].y = a[i];
    CDQProc(1, N);

    sum[0] = 0;
    for(int i = 1; i <= N; i++)
        sum[i] = sum[i-1] + ans[i];

    for(int i = N; i > N - M; i--)
        //cout << sum[i] << endl ;
        printf("%lld\n", sum[i]);

    return 0;
}
