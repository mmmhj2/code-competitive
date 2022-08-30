#include <algorithm>
#include <iostream>
#include <utility>
#include <cstdio>
#include <cstring>
#include <string>
#include <vector>
using namespace std;
const int MAXN = 500 ;

vector <int> Adj[MAXN+10];

bool vist[MAXN+10];
int  match[MAXN+10];

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
        if(match[to] < 0 || DFS(match[to]))
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
    int N;
    while(cin >> N)
    {
        memset(match, 0xff, sizeof match);
        for(int i = 0; i < N; i++)
            Adj[i].clear();

        for(int i = 0; i < N; i++)
        {
            int id, num;
            scanf("%d: (%d)", &id, &num);
            for(int k = 0; k < num; k++)
            {
                int tmp;
                cin >> tmp;
                //addEdge(tmp, id);
                Adj[id].push_back(tmp);
            }
        }
        int ans = 0;
        for(int i = 0; i < N; i++)
        {
            if(match[i] < 0)
            {
                memset(vist, 0x00, sizeof vist);
                if(DFS(i))
                    ans++;
            }
        }
        cout << N - ans << endl ;
    }
}

