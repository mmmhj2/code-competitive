#include <iostream>
#include <utility>
#include <cstring>
#include <vector>
using namespace std;
const int MAXN = 525;
const int OFFSET = 500;

vector <int> Adj[MAXN*2];
int match[MAXN*2];
bool vist[MAXN*2];

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
    int N, K, x, y;
    cin >> N >> K;
    for(int i = 1; i <= K; i++)
    {
        cin >> x >> y;
        Adj[x].push_back(y+OFFSET);
        Adj[y+OFFSET].push_back(x);
    }

    int ans = 0;
    for(int i = 1; i <= N; i++)
    {
        if(!match[i])
        {
            memset(vist, 0x00, sizeof vist);
            if(DFS(i))
                ans++;
        }
    }
    cout << ans << endl;

    return 0;
}

