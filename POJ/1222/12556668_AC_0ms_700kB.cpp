#include <cstdio>
#include <climits>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;
const int DIR[5][2] = {{0, 0}, {1, 0}, {0, 1}, {-1, 0}, {0, -1}};
const int MAXN = 6;
const int MAXM = 5;
const int MAXA = 10;
int n;
int opt[MAXA][MAXA];
int tile[MAXA][MAXA];
int flip[MAXA][MAXA];

int getAns();
int getClr(int, int);
int solve();
int printAns(int);

int main()
{
    cin >> n;
    for(int cnt = 1; cnt <= n; cnt++)
    {

        for(int i = 1; i <= MAXM; i++)
            for(int j = 1; j <= MAXN; j++)
                cin >> tile[i][j];
        cout << "PUZZLE #" << cnt << endl ;
        getAns();
    }
}

int getClr(int x, int y)
{
    int clr = tile[x][y];
    for(int i = 0; i < 5; i++)
        clr += flip[x+DIR[i][0]][y+DIR[i][1]];
    return clr & 1;
}

int getAns()
{
    int res = INT_MAX;
    for(int i = 0; i < (1 << 6); i++)
    {
        memset(flip, 0x00, sizeof flip);
        for(int j = 1; j <= 6; j++)
            flip[1][7-j] = ((i >> (j-1)) & 1);
        int num = solve();
        //res = min(num, res);
        if(res > num)
        {
            res = num;
            memcpy(opt, flip, sizeof flip);
        }
    }
    printAns(res);
    return res;
}

int solve()
{
    int sum = 0;
    for(int i = 2; i <= MAXM; i++)
        for(int j = 1; j <= MAXN; j++)
            if(getClr(i-1, j))
                flip[i][j] = 1;//, sum ++;

    for(int i = 1; i <= MAXN; i++)
        if(getClr(MAXM, i))
            return INT_MAX;

    for(int i = 1; i <= MAXM; i++)
        for(int j = 1; j <= MAXN; j++)
            sum += flip[i][j];

    return sum;
}

int printAns(int res)
{
    if(res >= INT_MAX)
        cout << "NO SOLUTION" << endl;
    else
    {
        for(int i = 1; i <= MAXM; i++)
        {
            for(int j = 1; j <= MAXN; j++)
            {
                if(j != 1)
                    cout << " " ;
                cout << opt[i][j];
            }
            cout << endl;
        }
    }
    return res;
}
