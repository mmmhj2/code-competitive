#include <algorithm>
#include <iostream>
#include <cstring>
#include <cstdio>
using namespace std;
const int MAXN = 1000;
const int MAXK = 10000;

struct instruction
{
    char dir;
    int space;
} ins[MAXK+10];

char ans[100010];
char maze[MAXN+10][MAXN+10];
int emptyspacex[MAXN+5][MAXN+5];
int emptyspacey[MAXN+5][MAXN+5];
int anscnt = 0;
int main()
{
    int n, m;
    int k;
    scanf("%d%d", &n, &m);
    for(int i = 0; i < n; i++)
        scanf("%s", maze[i]);

    for(int i = 0; i < n; i++)
        for(int j = 0; j < m; j++)
        {
            emptyspacex[i][j] = emptyspacex[i][j-1];
            emptyspacex[i][j] += (maze[i][j] != '#');
        }

    for(int i = 0; i < m; i++)
        for(int j = 0; j < n; j++)
        {
            emptyspacey[j][i] = emptyspacey[j-1][i];
            emptyspacey[j][i] += (maze[j][i] != '#');
        }

    scanf("%d", &k);
    getchar();
    for(int i = 0; i < k; i++)
    {
        scanf("%c%d", &ins[i].dir, &ins[i].space);
        getchar();
    }

    for(int i = 0; i < n; i++)
    {
        for(int j = 0; j < m; j++)
        {
            if('A' <= maze[i][j] && maze[i][j] <= 'Z')
            {
                bool accessible = true;
                int x = i, y = j;

                for(int cur = 0; cur < k; cur++)
                {
                    int tx = x, ty = y;
                    if(ins[cur].dir == 'N')
                    {
                        x -= ins[cur].space;
                        if(x < 0 || emptyspacey[tx][ty] - emptyspacey[x-1][y] != ins[cur].space+1)
                        {
                            accessible = false;
                            break;
                        }
                    }
                    if(ins[cur].dir == 'S')
                    {
                        x += ins[cur].space;
                        if(x >= n || emptyspacey[x][y] - emptyspacey[tx-1][ty] != ins[cur].space+1)
                        {
                            accessible = false;
                            break;
                        }
                    }
                    if(ins[cur].dir == 'W')
                    {
                        y -= ins[cur].space;
                        if(y < 0 || emptyspacex[tx][ty] - emptyspacex[x][y-1] != ins[cur].space+1)
                        {
                            accessible = false;
                            break;
                        }
                    }
                    if(ins[cur].dir == 'E')
                    {
                        y += ins[cur].space;
                        if(y >= m || emptyspacex[x][y] - emptyspacex[tx][ty-1] != ins[cur].space+1)
                        {
                            accessible = false;
                            break;
                        }
                    }
                }
                if(accessible)
                    //ans.push(maze[i][j]);
                    ans[anscnt++] = maze[i][j];
            }
        }
    }
    sort(ans, ans+anscnt);
    for(int i = 0; i < anscnt; i++)
        printf("%c", ans[i]);
    if(anscnt == 0)
        printf("no solution");
    puts("");
    return 0;
}
