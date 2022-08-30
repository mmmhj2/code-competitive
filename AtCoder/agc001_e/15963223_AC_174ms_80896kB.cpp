#include <cassert>
#include <cstdio>
#include <cmath>

typedef long long i64;

const i64 MOD = 1e9 + 7;
const i64 ZERO = 2000 + 5;
const i64 MAXM = 4500;
const i64 MAXFACT = 8000 + 10;
const i64 MAXN = 200000 + 5;

int N;
int factorial[MAXFACT], inverse[MAXFACT];
int a[MAXN], b[MAXN];
int dp[MAXM][MAXM];

i64 modularExp(i64 base, i64 exp)
{
	i64 ret = 1;
	while(exp)
	{
		if(exp & 1)
			ret = ret * base % MOD;
		base = base * base % MOD;
		exp = exp >> 1;
	}
	return ret;
}

void preprocess()
{
	factorial[0] = 1;
	for(int i = 1; i < MAXFACT; i++)
		factorial[i] = 1LL * factorial[i-1] * i % MOD ;

	inverse[MAXFACT - 1] = modularExp(factorial[MAXFACT - 1], MOD - 2);
	for(int i = MAXFACT - 2; i >= 0; i--)
		inverse[i] = 1LL * inverse[i + 1] * (i + 1) % MOD;
	assert(inverse[1] == 1);
}

inline int getBinomial(int n, int m)
{
	return 1LL * factorial[n] * inverse[m] % MOD * inverse[n - m] % MOD;
}

int main()
{
	i64 ans = 0;
	preprocess();

	scanf("%d", &N);
	for(int i = 1; i <= N; i++)
		scanf("%d%d", &a[i], &b[i]),
		dp[ZERO - a[i]][ZERO - b[i]] += 1;

	for(int i = 1; i < MAXM; i++)
		for(int j = 1; j < MAXM; j++)
			dp[i][j] = (dp[i][j] + dp[i-1][j] + dp[i][j-1]) % MOD;

	for(int i = 1; i <= N; i++)
		ans = (ans + dp[ZERO + a[i]][ZERO + b[i]]) % MOD;
	for(int i = 1; i <= N; i++)
		ans = ((ans - getBinomial((a[i] + b[i]) * 2, b[i] * 2)) % MOD + MOD) % MOD;

	printf("%lld\n", (500000004ll*ans)%MOD);
}
