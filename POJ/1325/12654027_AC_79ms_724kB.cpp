#include <iostream>
#include <cstring>
#include <vector>
using namespace std;
const int MAXN = 200;

int match[MAXN*2+10];
bool vist[MAXN*2+10];
vector <int> Adj[MAXN*2+10];

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
    int N, M, K;
    while(cin >> N)
    {
        if(N == 0)
            break;
        cin >> M >> K;

        for(int i = 1; i <= K; i++)
        {
            int a, ma, mb;
            cin >> a >> ma >> mb;
            if(ma == 0 || mb == 0)
                continue;

            Adj[ma].push_back(mb+1+N);
            Adj[mb+1+N].push_back(ma);
        }

        int ans = 0;

        for(int i = 1; i <= N; i++)
        {
            if(match[i] == 0)
            {
                memset(vist, 0x00, sizeof vist);
                if(DFS(i))
                    ans++;
            }
        }

        cout << ans << endl;

        for(int i = 1; i <= M+N+5; i++)
            Adj[i].clear();

        memset(match, 0x00 ,sizeof match);
    }
    return 0;
}
