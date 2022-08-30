#include <iostream>
#include <utility>
#include <cstring>
#include <vector>
using namespace std;
const int MAXN = 1500;
const int dir[4][2] = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};

int match[MAXN+10];
bool vist[MAXN+10];
bool hole[MAXN+10];
vector <int> Adj[MAXN+10];
int n, m, k;
int holecnt;

inline int point2int(int x, int y)
{
    return (x-1)*m+y;
}

void LinkGraph(int x, int y)
{
    if(hole[point2int(x, y)])
        return;
    int nx, ny;
    int curpos = point2int(x, y);
    for(int i = 0; i < 4; i++)
    {
        nx = x + dir[i][0];
        ny = y + dir[i][1];
        if(nx <= 0 || ny <= 0)
            continue;
        if(nx > n || ny > m)
            continue;
        if(hole[point2int(nx, ny)])
            continue;
        int newpos = point2int(nx, ny);
        //Adj[newpos].push_back(curpos);
        Adj[curpos].push_back(newpos);
    }
}


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
    cin >> n >> m >> k;

    for(int i = 1; i <= k; i++)
    {
        int x, y;
        cin >> y >> x;
        hole[point2int(x, y)] = true;
        holecnt++;
    }

    for(int i = 1; i <= n; i++)
        for(int j = 1; j <= m; j++)
            LinkGraph(i, j);

    int ans = 0;
    for(int i = 1; i <= n*m; i++)
    {
        if(!match[i])
        {
            memset(vist, 0x00, sizeof vist);
            if(DFS(i))
                ans++;
        }
    }

    /*for(int i = 1; i <= n*m; i++)
    {
        cerr << "Adjacent" << i << endl;
        for(int j = 0; j < Adj[i].size(); j++)
            cerr << " " << Adj[i][j] ;
        cerr << endl ;
    }*/

    //cerr << ans << endl ;
    if(ans*2 == m*n-holecnt)
        cout << "YES" << endl;
    else
        cout << "NO" << endl ;
    return 0;
}
