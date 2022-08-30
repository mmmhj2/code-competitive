#include <iostream>
#include <string>
using namespace std;
typedef long long i64;
const int MAXN = 400 + 5;
const int MOD = 1e9 + 7;

int n, c;
i64 powSum[MAXN][MAXN];
i64 A[MAXN], B[MAXN];
i64 DP[MAXN][MAXN];

i64 fastPow(i64 base, i64 exp)
{
    i64 ans = 1;
    while(exp)
    {
        if(exp & 1)
            ans = (ans * base) % MOD;
        base = (base * base) % MOD;
        exp >>= 1;
    }
    return ans;
}

void Init()
{
    for(int i = 1; i <= 400; i++)
        for(int j = 0; j <= 400; j++)
            powSum[i][j] = fastPow(i, j);
    for(int j = 0; j <= 400; j++)
        for(int i = 0; i <= 400; i++)
            powSum[i][j] = (powSum[i][j] + powSum[i-1][j]) % MOD;
}

int main()
{
    Init();

    cin >> n >> c;
    for(int i = 1; i <= n; i++)
        cin >> A[i];
    for(int i = 1; i <= n; i++)
        cin >> B[i];

    DP[0][0] = 1;
    for(int i = 1; i <= n; i++)
        for(int j = 0; j <= c; j++)
            for(int k = 0; k <= j; k++)
            {
                DP[i][j] += (DP[i-1][j-k] * (powSum[B[i]][k] - powSum[A[i]-1][k])) % MOD;
                DP[i][j] %= MOD;
            }

    cout << (DP[n][c] + MOD) % MOD << endl ;
    return 0;
}
