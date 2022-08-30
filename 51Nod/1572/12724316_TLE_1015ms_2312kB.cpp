#include <algorithm>
#include <iostream>
#include <cstring>
#include <string>
#include <cctype>
#include <cstdio>
#include <queue>
#include <list>
#include <map>
using namespace std;
const int MAXN = 1000;
const int MAXK = 10000;

struct instruction
{
    enum _dir
    {
        dir_N = 0,
        dir_S,
        dir_W,
        dir_E
    };
    //_dir dir;
    char dir;
    int space;
} ins[MAXK+10];

priority_queue <char, vector<char>, greater<char> > ans;
char maze[MAXN+10][MAXN+10];
int emptyspacex[MAXN+5][MAXN+5];
int emptyspacey[MAXN+5][MAXN+5];

int main()
{
    ios::sync_with_stdio(false);

    int n, m;
    int k;
    //cin >> n >> m ;
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

    //cin >> k;
    scanf("%d", &k);
    getchar();
    for(int i = 0; i < k; i++)
    {
        scanf("%c%d", &ins[i].dir, &ins[i].space);
        getchar();
        //cin.sync();
        //cin >> ins[i].dir >> ins[i].space;
        //cerr << ins[i].dir << ins[i].space << endl ;
    }

    for(int i = 0; i < n; i++)
    {
        for(int j = 0; j < m; j++)
        {
            if(isupper(maze[i][j]))
            {
                bool accessible = true;
                int x = i, y = j;
                for(int cur = 0; cur < k; cur++)
                {
                    int tx = x, ty = y;
                    switch(ins[cur].dir)
                    {
                    case 'N':
                        x -= ins[cur].space;
                        if(x < 0 || emptyspacey[tx][ty] - emptyspacey[x-1][y] != ins[cur].space+1)
                        {
                            accessible = false;
                            goto judge;
                        }
                        break;
                    case 'S':
                        x += ins[cur].space;
                        if(x >= n || emptyspacey[x][y] - emptyspacey[tx-1][ty] != ins[cur].space+1)
                        {
                            accessible = false;
                            goto judge;
                        }
                        break;
                    case 'W':
                        y -= ins[cur].space;
                        if(y < 0 || emptyspacex[tx][ty] - emptyspacex[x][y-1] != ins[cur].space+1)
                        {
                            accessible = false;
                            goto judge;
                        }
                        break;
                    case 'E':
                        y += ins[cur].space;
                        if(y >= m || emptyspacex[x][y] - emptyspacex[tx][ty-1] != ins[cur].space+1)
                        {
                            accessible = false;
                            goto judge;
                        }
                        break;
                    }
                }
judge:
                if(accessible)
                    ans.push(maze[i][j]);
            }


            {

            }
        }
    }
    if(ans.empty())
        //cout << "no solution";
        printf("no solution");
    else
        while(!ans.empty())
        {
            //cout << ans.top();
            printf("%c",ans.top());
            ans.pop();
        }
    printf("\n");
}
