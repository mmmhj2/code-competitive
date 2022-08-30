#include <bits/stdc++.h>
using namespace std;

typedef long long i64;

const int MAXN = 2000 + 5;
const int MOD = 1e9 + 7;

int N, K;
i64 fact[MAXN * MAXN], inverse[MAXN * MAXN];
i64 DP[MAXN][MAXN];

i64 modularExp(i64 base, i64 exp)
{
	i64 ret = 1;
	while (exp)
	{
		if (exp & 1)
			ret = ret * base % MOD;
		base = base * base % MOD;
		exp = exp >> 1;
	}
	return ret;
}

void prepare()
{
	fact[0] = 1;
	for (int i = 1; i < MAXN * MAXN; i++)
		fact[i] = fact[i - 1] * i % MOD;

	inverse[MAXN * MAXN - 1] = modularExp(fact[MAXN * MAXN - 1], MOD - 2) % MOD;
	for (int i = MAXN * MAXN - 2; i >= 0; i--)
		inverse[i] = inverse[i + 1] * (i + 1) % MOD;

	assert(inverse[1] == 1);
}

i64 getC(int n, int m)
{
	return fact[n] * inverse[m] % MOD * inverse[n - m] % MOD;
}

int main()
{
	prepare();
	cin >> N >> K;

	if(K == 1)
		cout << 1 << endl, exit(0);

	DP[0][0] = 1;
	for (int i = 0; i <= N; i++)
		for (int j = i; j <= N; j++)
		{
			DP[i][j + 1] = (DP[i][j + 1] + DP[i][j]) % MOD;
			DP[i + 1][j] = (DP[i][j] * getC(K * (N - i) - (j - i) - 1, K - 2)
					+ DP[i + 1][j]) % MOD;
		}
	cout << DP[N][N] * fact[N] % MOD << endl ;
	return 0;
}
