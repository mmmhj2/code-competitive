#include <algorithm>
#include <iostream>
#include <iomanip>
#include <cstring>
#include <string>
#include <vector>
#include <queue>
#include <cmath>
using namespace std;

const int MAXN = 200000 + 10;
const int MAXL = 100000 + 10;

struct DSU
{
    int fa[MAXN];

    int find(int x)
    {
        if(x == fa[x])
            return x;
        return fa[x] = find(fa[x]);
    }

    void merge(int x, int y)
    {
        fa[find(x)] = find(y);
    }
}d1, d2;

int tmp[MAXN], ans[MAXN], cnt[MAXN];

void init(DSU & d)
{
    for(int i = 0; i < MAXN; i++)
        d.fa[i] = i;
}

int N, K, L;
int main()
{
    init(d1);
    init(d2);
    int u, v;
    cin >> N >> K >> L ;

    for(int i = 1; i <= K; i++)
        cin >> u >> v, d1.merge(u, v);
    for(int i = 1; i <= L; i++)
        cin >> u >> v, d2.merge(u, v);

    for(int i = 1; i <= N; i++)
        tmp[i] = i;
    sort(tmp+1, tmp+N+1, [](int x, int y)-> bool {return d1.fa[x] < d1.fa[y];});
    for(int i = 1; i <= N; i++)
        d1.fa[i] = d1.find(i);

    for(int i = 1; i <= N; i++)
    {
        int j = i;
        while(j < N && d1.fa[tmp[j]] == d1.fa[tmp[j+1]])
            j++;

        for(int t = i; t <= j; t++)
            cnt[d2.fa[tmp[t]]]++;
        for(int t = i; t <= j; t++)
            ans[tmp[t]] = cnt[d2.fa[tmp[t]]];
        for(int t = i; t <= j; t++)
            cnt[d2.fa[tmp[t]]]--;
        i = j ;
    }

    for(int i = 1; i <= N; i++)
        cout << ans[i] << " " ;

    return 0;
}
