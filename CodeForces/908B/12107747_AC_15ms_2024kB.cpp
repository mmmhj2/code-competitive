#include <map>
#include <iostream>
#include <algorithm>
using namespace std;
const int DIRAR[4][2] = {{1, 0},{0, 1},{-1, 0},{0, -1}};
const int MAXN = 50;
string nav;

int n, m;
char maze[MAXN+2][MAXN+2];
int dirmap[5];
int sx, sy, ex, ey;
int cnt = 0;
int mapping[] = {0, 1, 2, 3};


bool navigate()
{
    int curx = sx, cury = sy;
    for(int i = 0; i < nav.length(); i++)
    {
        int dir = dirmap[nav[i]-'0'];
        curx += DIRAR[dir][0], cury += DIRAR[dir][1];
        if(curx < 0 || curx >= n)
            return false;
        if(cury < 0 || cury >= m)
            return false;
        if(maze[curx][cury] == '#')
            return false;
        if(maze[curx][cury] == 'E')
            return true;
    }
    return false;
}

int main()
{
    cin >> n >> m;
    for(int i = 0; i < n; i++)
    {
        cin >> maze[i];
        for(int j = 0; j < m; j++)
        {
            if(maze[i][j] == 'S')
                sx = i, sy = j;
            if(maze[i][j] == 'E')
                ex = i, ey = j;
        }
    }
    cin >> nav;

    do
    {
        for(int i = 0; i < 4; i++)
            dirmap[i] = mapping[i];
        if(navigate())
            cnt++;
    }while(next_permutation(mapping, mapping+4));

    cout << cnt << endl;
    return 0;
}
