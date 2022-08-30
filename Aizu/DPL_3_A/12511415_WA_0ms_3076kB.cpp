#include <iostream>
#include <algorithm>
using namespace std;

const int MAXN = 1400;

int dp[MAXN+5][MAXN+5];
int n, m;

int main()
{
    cin >> n >> m ;
    int t;
    for(int i = 1; i <= n; i++)
        for(int j = 1; j <= m; j++)
        {
            cin >> t;
            dp[i][j] = !t;
        }

    for(int i = 1; i <= n; i++)
        for(int j = 1; j <= m; j++)
            dp[i][j] = min(dp[i][j-1], min(dp[i-1][j], dp[i-1][j-1])) + 1;

    cout << dp[n][m] << endl;

    return 0;
}
