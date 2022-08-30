#include <iostream>
#include <cstring>
#include <vector>
using namespace std;
typedef vector <int> AdjTable;
const int MAXN = 100;

AdjTable Adj[MAXN+2];
int vist[MAXN+2];
int cnt = 0;

int makeMarker(int fa, int root, int id)
{
    vist[root] = id;
    for(int i = 0; i < Adj[root].size(); i++)
    {
        int to = Adj[root][i];
        if(to != fa)
            makeMarker(root, to, id);
    }
    return root;
}

int getPath(int fa, int cur, int dist)
{
    if(cur == dist)
        return makeMarker(fa, cur, ++cnt);

    for(int i = 0; i < Adj[cur].size(); i++)
    {
        int to = Adj[cur][i];
        if(to != fa)
            getPath(cur, to, dist);
    }
}

int main()
{
    int kase;
    cin >> kase;
    while(kase--)
    {
        cnt = 1;
        memset(vist, 0x00, sizeof vist);
        for(int i = 0; i <= MAXN; i++)
            Adj[i].clear();

        int N, M, u, v;
        vector <int> VisSeq;
        cin >> N;
        for(int i = 1; i < N; i++)
        {
            cin >> u >> v;
            Adj[u].push_back(v);
            Adj[v].push_back(u);
        }
        cin >> M;
        for(int i = 1; i <= M; i++)
        {
            cin >> u;
            VisSeq.push_back(u);
        }
        bool solution = true;
        while(!VisSeq.empty())
        {
            if(vist[VisSeq.front()] == cnt)
            {
                VisSeq.erase(VisSeq.begin());
                continue;
            }
            if(vist[VisSeq.front()] != 0)
            {
                //cout << "NO" << endl ;
                solution = false;
                break ;
            }
            getPath(0, 1, VisSeq.front());
        }
        if(solution)
            cout << "YES" << endl ;
        else
            cout <<  "NO" << endl ;
    }
}
