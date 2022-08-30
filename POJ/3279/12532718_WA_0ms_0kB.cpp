#include <iostream>
#include <cstring>
using namespace std;

const int MAXN = 20;
const int dir[5][2] = {{1,0},{0,1},{-1,0},{0,-1}, {0,0}};

int m, n;
int opt[MAXN][MAXN], stp, til[MAXN][MAXN];
int flip[MAXN][MAXN];

int solve(void);
int printAns(int[MAXN][MAXN]);
int cmpAns();

inline int getTile(int x, int y)
{
    int sum = til[x][y], tx, ty;
    for(int d = 0; d < 5; d++)
    {
        tx = x + dir[d][0], ty = y + dir[d][1];
        if(tx > 0 && tx <= m && ty > 0 && ty <= n)
            sum += flip[tx][ty];
    }
    return sum & 1;
}

int main()
{
    memset(opt, 0x7f, sizeof opt);
    stp = int(0x7fffffff);
    cin >> m >> n;
    for(int i = 1; i <= m; i++)
        for(int j = 1; j <= n; j++)
            cin >> til[i][j];

    for(int i = 0; i < (1 << n); i++)
    {
        memset(flip, 0x00, sizeof flip);
        for(int s = 0; s < n; s++)
            flip[1][n-s] = (i>>(s))&1;      // Enumerate Subset
        int res = solve();
        if((res < stp && res >= 0 )|| (res == stp && cmpAns()))
        {

            memcpy(opt, flip, sizeof flip);
            stp = res;
        }
    }
    //cerr << stp << endl ;
    printAns(opt);

    return 0;
}

int solve()
{
    int res = 0;

    for(int i = 2; i <= m; i++)
        for(int j = 1; j <= n; j++)
            if(getTile(i-1, j))
                flip[i][j]++;

    for(int i = 1; i <= n; i++)
        if(getTile(m, i))
        {
            //cout << "Return unsolved :" << endl;
            //printAns(flip);
            return -1;
        }


    for(int i = 1; i <= m; i++)
        for(int j = 1; j <= n; j++)
            res += flip[i][j];
    //cout << "Return Solved :" << endl;
    //printAns(flip);
    return res;
}

int printAns(int opt[MAXN][MAXN])
{
    for(int i = 1; i <= m; i++)
    {
        for(int j = 1; j <= n; j++)
        {
            cout << opt[i][j];
            if(j != n)
                cout << " ";
        }
        cout << endl ;
    }
    return 1;
}

int cmpAns()
{
    for(int i = 1; i <= m; i++)
        if(opt[1][m] > flip[1][m])
            return true;
    return false;
}
