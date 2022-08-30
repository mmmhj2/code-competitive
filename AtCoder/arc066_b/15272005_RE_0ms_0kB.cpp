#include <algorithm>
#include <iostream>
#include <iomanip>
#include <cstring>
#include <string>
#include <vector>
#include <queue>
#include <cmath>
#include <map>
using namespace std;

typedef long long i64;
typedef pair <i64, i64> pi64;
const int MOD = 1e9 + 7;

i64 N;
map <i64, i64> dp;

i64 getDP(int x)
{
    if(dp[x])
        return dp[x];
    dp[x] = (getDP(x / 2) + getDP((x - 1) / 2) + getDP((x - 2) / 2)) % MOD ;
    return dp[x];
}

int main()
{
    dp[0] = 1;
    dp[1] = 2;
    //cin >> N ;
    //cout << getDP(N) << endl ;
    scanf("%lld", &N);
    printf("%lld\n", getDP(N));
    return 0;
}
