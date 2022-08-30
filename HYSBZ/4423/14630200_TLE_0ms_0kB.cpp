#include <algorithm>
#include <iostream>
#include <iterator>
#include <cstring>
#include <utility>
#include <vector>
using namespace std;
const int MAXN = 1500 + 5;

int DSU[MAXN * MAXN];
int PosMap[MAXN][MAXN];

int Find(int x)
{
    if(DSU[x] == x)
        return x;
    return DSU[x] = Find(DSU[x]);
}
void joint(int u, int v)
{
    DSU[u] = v;
}

int N, Q;
bool lastAns;

int main()
{
    cin >> N >> Q ;
    for(int i = 1; i <= N*N; i++)
        DSU[i] = i ;
    for(int i = 0; i <= N; i++)
        for(int j = 0; j <= N; j++)
            PosMap[i][j] = (N - 1) * (N - 1) + 1;
    int cnt = 1;
    for(int i = 1; i < N; i++)
        for(int j = 1; j < N; j++)
            PosMap[i][j] = cnt++;

    while(Q--)
    {
        int u, v, t1, t2;
        char op;

        cin >> u >> v >> op;
        if(lastAns)
            cin >> u >> v >> op;

        t1 = PosMap[u][v];
        if(op == 'E')
            t2 = PosMap[u][v-1];
        else
            t2 = PosMap[u-1][v];

        if(!lastAns)
            cin >> u >> v >> op;

        t1 = Find(t1), t2 = Find(t2);
        lastAns = false;
        if(t1 == t2)
            lastAns = true;

        if(!lastAns)
            joint(t1, t2);

        if(lastAns)
            cout << "NIE" << endl ;
        else
            cout << "TAK" << endl ;
    }

    return 0;
}
