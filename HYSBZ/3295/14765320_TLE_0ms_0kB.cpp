#include <algorithm>
#include <iostream>
#include <cstring>
#include <cstdio>
using namespace std;

typedef long long i64;

const int MAXN = 100000 + 50 ;
const int MAXM = 50000 + 10 ;

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

template <typename T, typename Index = int>
class BinaryIndexedTree
{
    T * data;
    Index N;

    inline static Index LoBit(Index x)
    {
        return (x & -x);
    }

public:
    void setN(Index _N)
    {
        this->N = _N;
    }
    BinaryIndexedTree()
    {
        data = new T[MAXN];
    }
    ~BinaryIndexedTree()
    {
        delete[] data;
    }

    void add(Index id, T delta)
    {
        while(id <= N)
            data[id] += delta,
            id += LoBit(id);
    }

    T query(Index id)
    {
        T ans = 0;
        while(id)
            ans += data[id],
            id -= LoBit(id);
        return ans ;
    }
};

BinaryIndexedTree <i64> BIT;
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
    copy(aux, &aux[r-l+1], order + l);
}

int main()
{
    int t;
    //cin >> N >> M ;
    scanf("%d%d", &N, &M);
    aend = M;
    BIT.setN(N);

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
        printf("%d\n", sum[i]);

    return 0;
}
