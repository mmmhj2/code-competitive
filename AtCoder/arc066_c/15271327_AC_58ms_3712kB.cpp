#include <algorithm>
#include <iostream>
#include <iomanip>
#include <cstring>
#include <string>
#include <vector>
#include <queue>
#include <cmath>
using namespace std;

typedef long long i64;
const int MAXN = 100000 + 5 ;
const i64 INF  = 1e9 * 1e5 * 10;

int N;
i64 A[MAXN], dp[MAXN][3];
char op[MAXN][3];

int main()
{
    cin >> N ;
    for(int i = 1; i < N; i++)
        cin >> A[i] >> op[i] ;
    cin >> A[N];

    dp[1][0] = A[1];
    dp[1][1] = dp[1][2] = -INF;

    for(int i = 2; i <= N; i++)
        if(op[i - 1][0] == '-')
        {
            dp[i][0] = -INF;
            dp[i][1] = max(dp[i-1][0], dp[i-1][1]) - A[i];
            dp[i][2] = max(dp[i-1][1], dp[i-1][2]) + A[i];
        }
        else if(op[i - 1][0] == '+')
        {
            dp[i][0] = max(dp[i-1][0], dp[i-1][1]) + A[i];
            dp[i][1] = max(dp[i-1][1], dp[i-1][2]) - A[i];
            dp[i][2] = dp[i-1][2] + A[i];
        }

    cout << max({dp[N][0], dp[N][1], dp[N][2]}) << endl ;
    return 0;
}
