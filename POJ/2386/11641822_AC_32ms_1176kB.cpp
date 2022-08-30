#include <iostream>
#include <algorithm>
using namespace std;

char field[105][105];

int dir[8][2] = {{0, 1},{0, -1},{1, 0},{-1, 0},{1, 1},{-1, -1},{1, -1},{-1, 1}};

int n, m, ans = 0;

int DFS(int, int);

int main()
{
    cin >> n >> m;
    for(int i = 1; i <= n; i++)
    {
        for(int j = 1; j <= m; j++)
        {
            cin >> field[i][j];
        }
    }

    for(int i = 1; i <= n; i++)
    {
        for(int j = 1; j <= m; j++)
        {
            if(field[i][j] == 'W'){
                DFS(i, j);
                ans ++;
            }

        }
    }
    cout << ans << endl;
}

int DFS(int i, int j)
{
    if(field[i][j] == 'W')
    {
        field[i][j] = '.';
        for(int d = 0; d < 8; d++)
        {
            int tx = i+dir[d][0], ty = j+dir[d][1];
            if(tx > 0 && ty > 0 && tx <= n && ty <= m)
                DFS(tx, ty);
        }
    }
    return 0;
}
