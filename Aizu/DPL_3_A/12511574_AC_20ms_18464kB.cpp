#include <iostream>
#include <algorithm>
using namespace std;

const int MAXN = 1400;

int dp[MAXN+5][MAXN+5];
int G[MAXN+5][MAXN+5];
int n, m;

int main()
{
    int ans = 0;
    cin >> n >> m ;
    int t;
    for(int i = 1; i <= n; i++)
        for(int j = 1; j <= m; j++)
        {
            cin >> G[i][j];
            dp[i][j] = !G[i][j];
        }


    for(int i = 1; i <= n; i++)
        for(int j = 1; j <= m; j++)
        {
            if(G[i][j] == 1)
            {
                dp[i][j] = 0;
            }
            else
            {
                dp[i][j] = min(dp[i-1][j], min(dp[i][j-1], dp[i-1][j-1]))+1;
                ans = max(ans, dp[i][j]);
            }
        }

    cout << ans*ans << endl;

    return 0;
}
