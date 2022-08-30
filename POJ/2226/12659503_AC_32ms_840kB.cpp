#include <iostream>
#include <utility>
#include <cstring>
#include <vector>
using namespace std;
const int MAXN = 60;

vector <int> Adj[MAXN*MAXN*2];
int match[MAXN*MAXN];
bool vist[MAXN*MAXN];
int R, C;

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

void Addedge(int u, int v)
{
    Adj[u].push_back(v);
    Adj[v].push_back(u);
}

int getPos(int x, int y, bool isXaxis)
{
    if(isXaxis)
        return (x)*C+y;
    return (x)*C+y+R*C;
}

int main()
{
    string row[MAXN];
    cin >> R >> C;

    for(int i = 0; i < R; i++)
        cin >> row[i];

    // 处理联通块

    for(int i = 0; i < R; i++)
    {
        for(int j = 0; j < C; j++)
        {
            if(row[i][j] == '*')
            {
                int x = i, y = j;
                while(x > 0 && row[x-1][j] == '*')  x--;
                while(y > 0 && row[i][y-1] == '*')  y--;
                Addedge(getPos(x, j, 1), getPos(i, y, 0));
            }
        }
    }

    int ans = 0;

    for(int i = 0; i <= R*C; i++)
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

