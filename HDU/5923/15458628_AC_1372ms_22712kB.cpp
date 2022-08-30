#include <algorithm>
#include <iostream>
#include <cstring>
#include <vector>
using namespace std;

constexpr int MAXN = 500 + 10;
constexpr int MAXM = 10000 + 10;

namespace PersistentDisjointSet
{
    int fa[MAXM][MAXN];

    void init(int n, int m)
    {
        for(int i = 0; i <= m; i++)
            for(int j = 0; j <= n; j++)
                fa[i][j] = j;
    }

    int find(int version, int x)
    {
        if(fa[version][x] == x)
            return x;
        return fa[version][x] = find(version, fa[version][x]);
    }

    void merge(int version, int x, int y)
    {
        /*
        #ifndef ONLINE_JUDGE
        clog << "Merging : " << version << " " << x << " " << y << endl ;
        #endif // ONLINE_JUDGE
        */
        x = find(version, x), y = find(version, y);
        if(x != y)
            fa[version][y] = x;
    }

    void CloneOldVersion(int src, int dist)
    {
        /*
        #ifndef ONLINE_JUDGE
        clog << "Cloning : " << src << " to " << dist << endl ;
        #endif // ONLINE_JUDGE
        */
        memcpy(fa[dist], fa[src], sizeof fa[0]);
    }
};
using namespace PersistentDisjointSet;

vector <int> Adj[MAXM];
vector <pair<int, int>> G;

void DFS(int cur)
{
    for(auto itr = Adj[cur].begin(); itr != Adj[cur].end(); ++itr)
    {
        const int & to = *itr;

        CloneOldVersion(cur, to);
        merge(to, G[to - 1].first, G[to - 1].second);
        DFS(to);
    }
}

int st[MAXM], stSiz;
bool rtVis[MAXN];
int main()
{
    ios::sync_with_stdio(false), cin.tie(nullptr);
    int T;
    //cin >> T ;
    scanf("%d", &T);

    for(int kase = 1; kase <= T; kase++)
    {
        int N, M, Q, u, v;
        //cout << "Case #" << kase << ":\n";
        printf("Case #%d:\n", kase);
        //cin >> N >> M ;
        scanf("%d%d", &N, &M);

        init(N, M);
        for(int i = 1; i <= M; i++)
            Adj[i].clear();
        G.clear();

        for(int i = 2; i <= M; i++)
            //cin >> u , Adj[u].push_back(i);
            scanf("%d", &u), Adj[u].push_back(i);
        for(int i = 1; i <= M; i++)
            //cin >> u >> v , G.emplace_back(u, v);
            scanf("%d%d", &u, &v), G.emplace_back(u, v);
        merge(1, G[0].first, G[0].second);
        DFS(1);

        /*
        for(int i = 1; i <= M; i++)
        {
            for(int j = 1; j <= N; j++)
                clog << fa[i][j] << " " ;
            clog << endl ;
        }
        */

        //cin >> Q ;
        scanf("%d", &Q);
        while(Q--)
        {
            memset(rtVis, 0x00, sizeof rtVis);
            //cin >> stSiz;
            scanf("%d", &stSiz);
            for(int i = 1; i <= stSiz; i++)
                //cin >> st[i];
                scanf("%d", &st[i]);
            CloneOldVersion(st[1], M + 1);

            for(int i = 2; i <= stSiz; i++)
                for(int j = 1; j <= N; j++)
                    merge(M + 1, find(st[i], j), j);

            int ans = 0;
            for(int i = 1; i <= N; i++)
            {
                int fa = find(M + 1, i);
                if(!rtVis[fa])
                    rtVis[fa] = true, ans++;
            }

            //cout << ans << "\n" ;
            printf("%d\n", ans);
        }
    }

	return 0;
}
