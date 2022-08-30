#include <iostream>
#include <vector>
using namespace std;

const int MAXN = 200;

int SG[MAXN + 10][MAXN + 10];

int getSG(int n, int m)
{
    if(SG[n][m] >= 0)
        return SG[n][m];

    bool mex[MAXN + 10] = {false};

    for(int i = 2; i <= n / 2; i++)
        mex[getSG(i, m) ^ getSG(n-i, m)] = true;
    for(int j = 2; j <= m / 2; j++)
        mex[getSG(n, j) ^ getSG(n, m-j)] = true;

    for(int i = 0; i <= MAXN+1; i++)
        if(!mex[i])
            return SG[n][m] = i ;
    return -1;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    memset(SG, 0xFF, sizeof SG);
    int n, m;
    while(cin >> n >> m)
    {
        if(!getSG(n, m))
            cout << "LOSE" << endl ;
        else
            cout << "WIN" << endl ;
    }
    return 0;
}
