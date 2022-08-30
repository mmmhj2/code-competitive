/*
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

struct BinaryIndexedTree
{
    int data[MAXN];
    int N;

    inline static int LoBit(int x)
    {
        return (x & -x);
    }
    BinaryIndexedTree()
    {
        //data = new T[MAXN];
    }
    ~BinaryIndexedTree()
    {
        //delete[] data;
    }

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
int N, M , aend;
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
    int j;
    for(int i = mid + 1; i <= r; i++)
    {
        for(j = l; j <= mid && order[j].x < order[i].x; j++)
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
    BIT.N = N;

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
*/

#include<cstdio>
#include<iostream>
#include<algorithm>
#include<cstring>
using namespace std;
#define maxn 111111
typedef long long ll;
int n,m,cnt[maxn],a[maxn],pos[maxn],flag[maxn];
ll ans[maxn];
struct node
{
    int x,y,id;
    bool  operator <(const node &a)const
    {
        if(x!=a.x)
            return x<a.x;
        return y<a.y;
    }
} p[maxn],q[maxn];
struct BIT
{
#define lowbit(x) (x&(-x))
    int b[maxn];
    void init()
    {
        memset(b,0,sizeof(b));
    }
    void update(int x,int v)
    {
        while(x<=n)
        {
            b[x]+=v;
            x+=lowbit(x);
        }
    }
    int query(int x)
    {
        int ans=0;
        while(x)
        {
            ans+=b[x];
            x-=lowbit(x);
        }
        return ans;
    }
} bit;
void CDQ(int l,int r)
{
    if(l==r)
        return ;
    int mid=(l+r)>>1;
    CDQ(l,mid);
    CDQ(mid+1,r);
    sort(p+l,p+mid+1);
    sort(p+mid+1,p+r+1);
    int j=l;
    for(int i=mid+1; i<=r; i++)
    {
        for(; j<=mid&&p[j].x<p[i].x; j++)
            bit.update(p[j].y,1);
        cnt[p[i].id]+=bit.query(p[i].y);
    }
    for(int i=l; i<j; i++)
        bit.update(p[i].y,-1);
    merge(p+l,p+mid+1,p+mid+1,p+r+1,q);
    for(int i=0; i<r-l+1; i++)
        p[l+i]=q[i];
}
int main()
{
    scanf("%d%d",&n,&m);
    int tm=m;
    memset(flag,0,sizeof(flag));
    memset(cnt,0,sizeof(cnt));
    bit.init();
    for(int i=1; i<=n; i++)
    {
        scanf("%d",&a[i]);
        pos[a[i]]=i;
    }
    for(int i=1; i<=m; i++)
    {
        scanf("%d",&a[i]);
        flag[a[i]]=1;
    }
    for(int i=1; i<=n; i++)
        if(!flag[i])
            a[++tm]=i;
    for(int i=n; i>=1; i--)
        p[i].id=i,p[n+1-i].x=pos[a[i]],p[n+1-i].y=n+1-a[i];
    CDQ(1,n);
    for(int i=n; i>=1; i--)
        p[i].id=i,p[n+1-i].x=n+1-pos[a[i]],p[n+1-i].y=a[i];
    CDQ(1,n);
    ans[0]=0;
    for(int i=1; i<=n; i++)
        ans[i]=ans[i-1]+cnt[i];
    for(int i=n; i>n-m; i--)
        printf("%lld\n",ans[i]);
    return 0;
}
