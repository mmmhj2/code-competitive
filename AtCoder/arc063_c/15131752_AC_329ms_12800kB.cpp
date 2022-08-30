#include <iostream>
#include <vector>
using namespace std;

const int MAXN = 100000 + 5 ;

bool noSolution;
int N, K;
pair <int, int> pnt[MAXN];
struct node
{
    int l, r, oe;
}rng[MAXN];
vector <int> Adj[MAXN];

void UpdateNode(int toUpdate, int evidence)
{
    int l = rng[evidence].l-1, r = rng[evidence].r+1;
    if(rng[evidence].oe != -1)
    {
        if(rng[toUpdate].oe == -1)
            rng[toUpdate].oe = rng[evidence].oe ^ 1;
        else if(rng[toUpdate].oe == rng[evidence].oe)
            noSolution = true ;
    }
    rng[toUpdate].l = max(rng[toUpdate].l, l), rng[toUpdate].r = min(rng[toUpdate].r, r);

    if(rng[toUpdate].l > rng[toUpdate].r)
        noSolution = true ;
}

void DFSPushUp(int x, int fa)
{
    if(noSolution)
        return ;
    for(int & to : Adj[x])
        if(to != fa)
            DFSPushUp(to, x),   UpdateNode(x, to);
}

void DFSPushDown(int x, int fa)
{
    if(noSolution)
        return;
    if(fa)
        UpdateNode(x, fa);
    for(int & to : Adj[x])
        if(to != fa)
            DFSPushDown(to, x);
}

int main()
{
    int u, v, w;
    cin >> N ;

    for(int i = 1; i < N; i++)
        cin >> u >> v , Adj[u].push_back(v), Adj[v].push_back(u);

    cin >> K ;
    for(int i = 1; i <= N; i++)
        rng[i].l = 0x80808080, rng[i].r = 0x7F7F7F7F, rng[i].oe = -1;
    for(int i = 1; i <= K; i++)
        cin >> pnt[i].first >> pnt[i].second, rng[pnt[i].first].l = pnt[i].second, rng[pnt[i].first].r = pnt[i].second, rng[pnt[i].first].oe = pnt[i].second & 1;

    DFSPushUp(1, 0);
    DFSPushDown(1, 0);

    if(noSolution)
        puts("No");
    else
    {
        puts("Yes");
        for(int i = 1; i <= N; i++)
            cout << rng[i].l << endl ;
    }

    return 0;
}
