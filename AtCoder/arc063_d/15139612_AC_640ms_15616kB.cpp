#include <algorithm>
#include <iostream>
#include <cstring>
#include <vector>
using namespace std;

#define PX(p) (p.first)
#define PY(p) (p.second)
typedef pair <int, int> p2i;

const int MAXN = 3 * 100000 + 5;

int N, W, H, ans;
p2i pnts[MAXN];

class SegTree
{
public:
    int mx[MAXN * 4];
    int lz[MAXN * 4];

    inline int LC(int x)
    {
        return (x << 1);
    }
    inline int RC(int x)
    {
        return (x << 1) | 1 ;
    }

    void reset()
    {
        memset(mx, 0x00, sizeof mx);
        memset(lz, 0x00, sizeof lz);
    }
    void Pushup(int x)
    {
        mx[x] = max(mx[LC(x)], mx[RC(x)]) + lz[x];
    }

    void Modify(int CL, int CR, int CV, int L = 1, int R = ::N, int x = 1)
    {
        if(CL <= L && R <= CR)
        {
            mx[x] += CV, lz[x] += CV;
            return;
        }

        int mid = (L + R) >> 1 ;

        if(CL <= mid)
            Modify(CL, CR, CV, L, mid, LC(x));
        if(mid < CR)
            Modify(CL, CR, CV, mid + 1, R, RC(x));
        Pushup(x);
    }
}ST;

p2i stk1[MAXN], stk2[MAXN];
void solve()
{
    sort(&pnts[1], &pnts[N+1]);
    ST.reset();

    int topa(0), topb(0);

    int MID = H / 2;

    for(int i = 1; i <= N - 1; i++)
    {
        int nxt = i - 1;
        if(pnts[i].second <= MID)
        {
            while(topa && stk1[topa].second < pnts[i].second)
            {
                ST.Modify(stk1[topa].first, nxt, stk1[topa].second - pnts[i].second);
                nxt = stk1[topa].first - 1;
                topa--;
            }
            if(nxt != i - 1)
                stk1[++topa] = make_pair(nxt+1, pnts[i].second);
        }
        else
        {
            while(topb && pnts[i].second < stk2[topb].second)
            {
                ST.Modify(stk2[topb].first, nxt, pnts[i].second - stk2[topb].second);
                nxt = stk2[topb].first - 1;
                topb--;
            }
            if(nxt != i - 1)
                stk2[++topb] = make_pair(nxt+1, pnts[i].second);
        }

        stk1[++topa] = make_pair(i, 0);
        stk2[++topb] = make_pair(i, H);

        ST.Modify(i, i, H - pnts[i].first);
        ans = max(ans, ST.mx[1] + pnts[i+1].first);
    }
}

int main()
{
    int u, v;
    cin >> W >> H >> N ;

    for(int i = 1; i <= N; i++)
        cin >> u >> v , pnts[i] = (make_pair(u, v));
    pnts[++N] = (make_pair(0, 0));
    pnts[++N] = (make_pair(W, H));

    solve();

    for(int i = 1; i <= N; i++)
        swap(pnts[i].first, pnts[i].second);
    swap(W, H);

    solve();

    cout << (ans << 1) << endl ;
    return 0;
}
