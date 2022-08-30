#include <algorithm>
#include <cstdio>

#define REDIRECT(x) freopen(x".in", "r", stdin), freopen(x".out", "w", stdout)
#define CLOSEALL() fclose(stdin), fclose(stdout)

const int MAXN = 1e5 + 10;

typedef long long i64;

i64 tmp = 0x7F7F7F7F7F7F7F7F;
i64 N, M, T;
i64 a[MAXN];
i64 dp[MAXN];

int main()
{
	//REDIRECT("computer");

	i64 t = 0;
	scanf("%lld%lld%lld", &N, &M, &T);
	for (int i = 1; i <= N; i++)
		scanf("%lld", &a[i]);

	for (int i = 1; i <= N; i++)
	{
		while (T <= (a[i] - a[t + 1]) * 2)
			tmp = std::min(tmp, dp[t] - 2 * a[t + 1]), t++;
		dp[i] = std::min(dp[t] + T, tmp + 2 * a[i]);
	}

	printf("%lld\n", dp[N] + M);

	CLOSEALL();
	return 0;
}
