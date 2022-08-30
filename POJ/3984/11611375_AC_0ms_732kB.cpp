#include <iostream>
#include <cstring>
using namespace std;
const int MAXN = 6;
const int MAXQ = MAXN*MAXN;
const int dir[4][2] = {{1, 0},{-1, 0},{0, 1},{0, -1}};

struct node
{
    int x, y;
    int fa;
    node(){};
    node(int _x, int _y, int _f) //: x(_x), y(_y), fa(_f)
    {
        x = _x, y = _y, fa = _f;
    }
};

node Q[MAXQ+5];
int h, t;
int maze[MAXN][MAXN];
bool vis[MAXN][MAXN];
int n = 5;

void read();
int BFS();
void printAns(int);

int main()
{
    read();
    BFS();
    return 0;
}

void printAns(int i)
{
    if(i == 0)
        return ;
    printAns(Q[i].fa);
    cout << "(" << Q[i].x-1 << ", " << Q[i].y-1 << ")" << endl;
}

void read()
{
    for(int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++)
        {
            int t;
            cin >> t;
            maze[i][j] = !t;
        }
}

int BFS()
{
    h = 0, t = 1;
    Q[t] = node(1, 1, 0);
    vis[1][1] = true;
    while(h < t)
    {
        node cur = Q[++h], nxt;
        if(cur.x == n && cur.y == n)
        {
            printAns(h);
            return 0;
        }

        for(int i = 0; i < 4; i++)
        {
            nxt.x = cur.x+dir[i][0];
            nxt.y = cur.y+dir[i][1];
            if(vis[nxt.x][nxt.y] == true || maze[nxt.x][nxt.y] == 0)
                continue;
            vis[nxt.x][nxt.y] = true;
            nxt.fa = h;
            Q[++t] = nxt;
        }
    }
    return -1;
}
