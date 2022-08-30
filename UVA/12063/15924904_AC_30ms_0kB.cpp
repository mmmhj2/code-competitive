#include <cstring>
#include <cstdio>

typedef long long i64;

i64 memo[35][35][105];

int N, K, tot;

i64 DFS(int zero, int one, int remainder)
{
    i64 & dp = memo[zero][one][remainder];
    if(dp != -1)
        return dp;

    if(tot == one && tot == zero)
        return dp = (remainder == 0);
    if(one == tot)
        return dp = DFS(zero + 1, one, (remainder << 1) % K);
    if(zero == tot)
        return dp = DFS(zero, one + 1, ((remainder << 1) | 1) % K);
    return dp = DFS(zero + 1, one, (remainder << 1) % K) + DFS(zero, one + 1, ((remainder << 1) | 1) % K);
}

int main()
{
    int T;
    scanf("%d", &T);

    for(int kase = 1; kase <= T; kase++)
    {
        memset(memo, 0xFF, sizeof memo);

        scanf("%d%d", &N, &K);
        tot = N >> 1;

        i64 res = (((N & 1) == 0) && K) ? DFS(0, 1, 1) : 0;
        printf("Case %d: %lld\n", kase, res);
    }

    return 0;
}
