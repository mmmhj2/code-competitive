#include <algorithm>
#include <iostream>
#include <iterator>
#include <cstring>
#include <cstdio>
#include <vector>
using namespace std;

const int MAXN = 10000 + 5;

struct Edge
{
    int v, w;
};

int N, K, ans;
int root, rtCnt, curSubSum;
vector <Edge> Adj[MAXN];
vector <int> distVec;
int dist[MAXN];
bool vist[MAXN];
int sonCnt[MAXN], maxSon[MAXN];

void getSonCnt(int rt, int fa)
{
    sonCnt[rt] = 1;

    for(vector<Edge>::iterator itr = Adj[rt].begin(); itr != Adj[rt].end(); ++itr)
    {
        const int & to = itr->v;

        if(to == fa || vist[to])
            continue;

        getSonCnt(to, rt);
        sonCnt[rt] += sonCnt[to];
        maxSon[rt] = max(maxSon[rt], sonCnt[to]);
    }

    maxSon[rt] = max(maxSon[rt], N - sonCnt[rt]);

    if(maxSon[rt] < rtCnt)
        rtCnt = maxSon[rt], root = rt;
}

void getDist(int rt, int fa, int w)
{
    dist[rt] = dist[fa] + w;
    //cerr << "rt : " << rt << " " << dist[rt] << endl ;
    distVec.push_back(dist[rt]);
    // Re-calculate son count, as the root may be changed
    sonCnt[rt] = 1;
    for(vector<Edge>::iterator itr = Adj[rt].begin(); itr != Adj[rt].end(); ++itr)
    {
        const int & to = itr->v;
        if(to == fa || vist[to])
            continue;

        getDist(to, rt, itr->w);
        sonCnt[rt] += sonCnt[to];
    }
}

int calcSum(int rt, int delta)
{
    distVec.clear();
    getDist(rt, 0, delta);
    sort(distVec.begin(), distVec.end());
    //cerr << "Distance : " ;
    //copy(distVec.begin(), distVec.end(), ostream_iterator<int>(cerr, " "));
    //cerr << endl ;

    int L = 0, R = distVec.size() - 1, ret = 0;
    while(L < R)
        if(distVec[L] + distVec[R] <= K)
            ret += R - L,
            L++;
        else
            R--;
    //cerr << "Calculating : " << L << " " << R << " " << ret << endl ;
    return ret;
}

void divisionOnTree(int cur)
{
    ans += calcSum(cur, 0);
    //cerr << "cur : " << cur << " ans : " << ans << endl ;
    vist[cur] = true;

    for(vector<Edge>::iterator itr = Adj[cur].begin(); itr != Adj[cur].end();++itr)
    {
        const int & to = itr->v;
        if(vist[to])
            continue;

        ans -= calcSum(to, itr->w);
        //cerr << "answer : " << ans << endl ;
        rtCnt = 0x7FFFFFFF, curSubSum = sonCnt[to];
        getSonCnt(to, 0);
        //cerr << "New Root : " << root << endl ;
        divisionOnTree(root);
    }
}

int main()
{
    int u, v, w;

    while(/*cin >> N >> K*/1)
    {
        scanf("%d%d", &N, &K);
        if((!N) && (!K))
            break;

        memset(vist, 0x00, sizeof vist);
        for(int i = 1; i <= N; i++)
            Adj[i].clear();
        ans = 0;

        for(int i = 2; i <= N; i++)
            //cin >> u >> v >> w ,
            scanf("%d%d%d", &u, &v, &w),
            Adj[u].push_back((Edge){v ,w}),
            Adj[v].push_back((Edge){u ,w});

        rtCnt = 0x7FFFFFFF, curSubSum = N;
        getSonCnt(1, 0);
        divisionOnTree(root);

        //cout << ans << endl ;
        printf("%d\n", ans);
    }

    return 0;
}
