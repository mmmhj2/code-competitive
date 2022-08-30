#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<iterator>
#include<cmath>
#include<set>
using namespace std;

#ifdef LOCAL
#define DEBUGMSG()                                                              \
{                                                                               \
    cerr << "[调试 @" << __PRETTY_FUNCTION__ << ":" << __LINE__ << "]" ;        \
}
#define DEBUGVAR(x)                                                             \
{                                                                               \
    cerr << "[调试 @" << __PRETTY_FUNCTION__ << ":" << __LINE__ << "]:" ;       \
    cerr << "([" << typeid(x).name() << "]" << #x << ")" << x << endl ;         \
}
#define DEBUGARR(l, r)                                                          \
{                                                                               \
    cerr << "[调试 @" << __PRETTY_FUNCTION__ << ":" << __LINE__ << "]:" ;       \
    copy(l, r, ostream_iterator<decltype(*l)>(cerr, " "));                      \
    cerr << endl ;                                                              \
}
#else
#define DEBUGMSG()
#define DEBUGVAR(x)
#define DEBUGARR(l, r)
#endif // LOCAL

int read()
{
    int x = 0, f = 1;
    char ch = getchar();

    while (ch < '0' || ch > '9')
    {
        if (ch == '-')
            f = -1;

        ch = getchar();
    }

    while (ch >= '0' && ch <= '9')
    {
        x = x * 10 + ch - '0';
        ch = getchar();
    }

    return x * f;
}
#define MAXN 200010
#define INF 0x3f3f3f3f
int N;
struct CompanyNode
{
    int s, t, id;
} c[MAXN], tmp[MAXN], b[MAXN];
bool cmp1(CompanyNode A, CompanyNode B)
{
    return A.s == B.s ? A.t > B.t : A.s < B.s;
}
bool cmp2(CompanyNode A, CompanyNode B)
{
    return A.id < B.id;
}
struct SetNode
{
    int x, f;
    SetNode (int x, int f) : x(x), f(f) {}
    bool operator < (const SetNode & A) const
    {
        return x < A.x;
    }
};
set<SetNode>st;
set<SetNode>::iterator lst, rst;
int f[MAXN << 1][20];
int Cal(int l, int r)
{
    int re = 0;

    for (int i = 17; i >= 0; i--)
        if (f[l][i] <= r)
            l = f[l][i] + 1, re += 1 << i; //一定要+1

    return re;
}
int ls[MAXN << 1], tp, top;
int main()
{
    //freopen("data.in","r",stdin); freopen("data.out","w",stdout);
    N = read();

    for (int i = 1; i <= N; i++)
        ls[++tp] = c[i].s = read(), ls[++tp] = c[i].t = read(), c[i].id = i;

    sort(ls + 1, ls + tp + 1);
    top = unique(ls + 1, ls + tp + 1) - ls - 1;

    for (int i = 1; i <= N; i++)
        c[i].s = lower_bound(ls + 1, ls + top + 1, c[i].s) - ls, c[i].t = lower_bound(ls + 1, ls + top + 1, c[i].t) - ls;

    sort(c + 1, c + N + 1, cmp1);
    int last = INF;
    tp = 0;

    for (int i = N; i >= 1; i--)
        if (c[i].t < last)
            tmp[++tp] = c[i], last = c[i].t;

    reverse(tmp + 1, tmp + tp + 1);

    //for (int i = 1; i <= tp; i++)
     //   printf("%d %d %d\n", tmp[i].s, tmp[i].t, tmp[i].id);

    memset(f, 0x3f, sizeof(f));

//    printf("%d %d\n",f[1],INF);
    for (int i = top, j = tp; i >= 1; i--)
    {
        f[i][0] = f[i + 1][0];

        if (tmp[j].s == i)
            f[i][0] = min(f[i][0], tmp[j].t);

        for (int k = 1; k <= 17; k++)
            if (f[i][k - 1] != INF)
                f[i][k] = f[f[i][k - 1] + 1][k - 1];

        while (tmp[j].s == i)
            j--;
    }

//    for (int i=1; i<=N; i++) printf("%d %d %d\n",c[i].id,c[i].s,c[i].t);
    DEBUGARR(&f[1][0], &f[1][15]);
    DEBUGARR(&f[2][0], &f[2][15]);
    DEBUGVAR(top);

    printf("%d\n", Cal(1, top));
    sort(c + 1, c + N + 1, cmp2);
    st.insert(SetNode(0, -1));
    st.insert(SetNode(top + 1, 1));
    int cnt = 0;

    for (int i = 1; i <= N; i++)
    {
        DEBUGVAR(st.size());
        SetNode ls = SetNode(c[i].s, 1), rs = SetNode(c[i].t, -1);
        lst = st.lower_bound(ls);
        rst = st.upper_bound(rs);

        if (lst != rst || (*rst).f == -1)
            continue;

        lst--;
        int L = (*lst).x + 1, R = (*rst).x - 1;

        if (Cal(L, c[i].s - 1) + Cal(c[i].t + 1, R) + 1 == Cal(L, R))
        {
            st.insert(ls), st.insert(rs);
            cnt++;

            if (cnt == 1)
                printf("%d", c[i].id);
            else
                printf(" %d", c[i].id);
        }
    }

    puts("");
    return 0;
}
