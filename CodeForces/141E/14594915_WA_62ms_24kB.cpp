#include <algorithm>
#include <iterator>
#include <iostream>
#include <iomanip>
#include <cstring>
#include <cstdlib>
#include <cassert>
#include <string>
#include <vector>
#include <queue>
#include <cmath>
#include <set>
using namespace std;

#define _DEF(x, i) x = vEdge[i].x
#define DEF(i) _DEF(u, i), _DEF(v, i)

const int MAXN = 1000 + 5;
const int MAXM = 100000 + 5;

struct Edge{
    int u, v;
    char col;
};

struct disjointSet{
    int fa[MAXN];

    void clear(int N)
    {
        for(int i = 1; i <= N; i++)
            fa[i] = i;
    }

    disjointSet(int N)
    {
        clear(N);
    }

    int find(int x)
    {
        if(fa[x] == x)
            return x;
        return fa[x] = find(fa[x]);
    }

    void unite(int x, int y)
    {
        fa[find(x)] = find(y);
    }
};

int N, M;
int cnt1, cnt2;
disjointSet dS1(MAXN), dS2(MAXN);
bool used[MAXN];
Edge vEdge[MAXN];

int main()
{
    int u, v;
    char c;
    cin >> N >> M ;
    for(int i = 1; i <= M; i++)
    {
        cin >> u >> v >> c;
        vEdge[i] = Edge{u, v, c};
    }

    if(!(N & 1))
        cout << -1 << endl, exit(0);


    // Connecting "M" edges, generating tree 1
    for(int i = 1; i <= M; i++)
    {
        if(vEdge[i].col == 'S')
            continue;
        DEF(i);
        if(dS1.find(u) != dS1.find(v))
        {
            dS1.unite(u, v);
            cnt1++;
        }
    }

    if(cnt1 * 2 < N - 1)
        cout << -1 << endl, exit(0);
    // Connecting "S" edges, generating tree 1 and 2
    for(int i = 1; i <= M; i++)
    {
        if(vEdge[i].col == 'M')
            continue;
        DEF(i);
        if(dS1.find(u) != dS1.find(v))
        {
            dS1.unite(u, v);
            dS2.unite(u, v);
            cnt2++;
            used[i] = true;
        }
    }

    for(int i = 1; i <= N; i++)
        if(dS1.find(i) != dS1.find(i))
            cout << -1 << endl, exit(0);
    // Replacing "S" edges, generating tree 2
    for(int i = 1; i <= M && cnt2 < cnt1; i++)
    {
        if(vEdge[i].col == 'M')
            continue;
        DEF(i);
        if(dS2.find(u) != dS2.find(v))
        {
            dS2.unite(u, v);
            cnt1--, cnt2++;
            used[i] = true;
        }
    }
    if(cnt2 < cnt1)
        cout << -1 << endl, exit(0);
    // Obtain a feasible solution by adding "M" edges
    // Generating tree 2
    for(int i = 1; i <= M; i++)
    {
        if(vEdge[i].col == 'S')
            continue;
        DEF(i);
        if(dS2.find(u) != dS2.find(v))
        {
            dS2.unite(u, v);
            cnt2++;
            used[i] = true;
        }
    }

    cout << cnt2 / 2 << endl ;
    for(int i = 1; i <= M; i++)
    {
        if(used[i])
            cout << i << " " ;
    }
}
