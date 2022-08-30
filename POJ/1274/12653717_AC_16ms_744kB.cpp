#include <iostream>
#include <cstring>
#include <vector>
using namespace std;
const int MAXN = 205;

int match[MAXN*2+10];
bool vist[MAXN*2+10];
vector <int> Adj[MAXN*2+10];
int N, M;

int ans;

int DFS(int cur)
{

    for(int i = 0; i < Adj[cur].size(); i++)
    {
        int & to = Adj[cur][i];
        if(vist[to])
            continue;
        vist[to] = true;
        if(match[to] == 0 || DFS(match[to]))
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
    while(cin >> N >> M)
    {
        ans = 0;
        for(int i = 1; i <= N; i++)
        {
            int K, t;
            cin >> K;
            for(int k = 1; k <= K; k++)
            {
                cin >> t;
                Adj[t+N].push_back(i);
                Adj[i].push_back(t+N);
            }
        }

        for(int i = 1; i <= N; i++)
        {
            if(!match[i])
            {
                memset(vist, 0x00, sizeof vist);
                //vist[i] = true;
                if(DFS(i))ans++;
            }
        }
        cout << ans << endl;

        for(int i = 1; i <= N+M+1; i++)
            Adj[i].clear();
        memset(match, 0x00, sizeof match);
    }
}
