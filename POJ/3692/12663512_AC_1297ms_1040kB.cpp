#include <algorithm>
#include <iostream>
#include <utility>
#include <cstdio>
#include <cstring>
#include <string>
#include <vector>
using namespace std;
const int MAXN = 210;
const int OFFSET = 200;

vector <int> Adj[MAXN*2+10];

bool vist[MAXN*2+10];
int  match[MAXN*2+10];
bool MAP[MAXN+10][MAXN+10];

void addEdge(int u, int v)
{
    Adj[u].push_back(v);
    Adj[v].push_back(u);
}

int DFS(int cur)
{
    for(int i = 0; i < Adj[cur].size(); i++)
    {
        int & to = Adj[cur][i];
        if(vist[to])
            continue;
        vist[to] = true;
        if(match[to] <= 0 || DFS(match[to]))
        {
            match[to] = cur;
            match[cur] = to;
            return true;
        }
    }
    return false;
}

int main()
{
    int G, B, M;
    int kase = 0;
    while(cin >> G >> B >> M)
    {
        if(G == 0 && B == 0 && M == 0)
            break;

        for(int i = 1; i <= G+B; i++)
            Adj[i].clear();
        memset(match, 0x00, sizeof match);
        memset(MAP  , 0x00, sizeof MAP);

        int tg, tb;
        for(int i = 1; i <= M; i++)
        {
            cin >> tg >> tb;
            MAP[tg][tb] = true;
        }

        for(int i = 1; i <= G; i++)
            for(int j = 1; j <= B; j++)
                if(!MAP[i][j])
                    addEdge(i, j+G);

        int ans = 0;
        for(int i = 1; i <= G+B; i++)
        {
            if(!match[i])
            {
                memset(vist, 0x00, sizeof vist);
                if(DFS(i))
                    ans++;
            }
        }

        cout << "Case " << ++kase << ": " << G+B-ans << endl;
    }
}

