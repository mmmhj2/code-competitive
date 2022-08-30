#include <algorithm>
#include <iostream>
#include <iterator>
#include <cstring>
#include <utility>
#include <vector>

#define D "%d"

using namespace std;
const int MAXN = 20000 + 5;

struct Product
{
    int p, d;
};
bool cmp (const Product & a, const Product & b)
{
    return a.p > b.p;
}

int N;
int DSU[MAXN];
Product vP[MAXN];

int Find(int x)
{
    if(DSU[x] == -1)
        return x;
    DSU[x] = Find(DSU[x]);
    return DSU[x];
}

int main()
{
    while(~scanf(D, &N))
    {
        memset(DSU, 0xFF, sizeof DSU);
        int u, v, ans = 0;
        if(!N)
            break;

        for(int i = 0; i < N; i++)
        {
            //cin >> u >> v ;
            scanf(D D, &u, &v);
            vP[i].p = u,
            vP[i].d = v;
        }

        sort(vP, vP + N, cmp);

        for(int i = 0; i < N; i++)
        {
            int date = Find(vP[i].d);
            if(date > 0)
            {
                DSU[date] = date-1;
                ans += vP[i].p;
            }
        }

        //cout << ans << endl ;
        printf(D"\n", ans);

    }
    return 0;
}
