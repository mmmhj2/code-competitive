#include <cstdio>
#include <cstring>

double p[25], ans[25];
int N, R, vis[25];

void dfs(int k, int dep)
{
	if (dep == R)
	{
		double tmp = 1;
		for (int i = 1; i <= N; i++)
		{
			if (vis[i])
				tmp *= p[i];
			else
				tmp *= (1 - p[i]);
		}
		ans[0] += tmp;
		for (int i = 1; i <= N; i++)
			if (vis[i])
				ans[i] += tmp;
	}
	else
		for (int i = k + 1; i <= N; i++)
			vis[i] = 1, dfs(i, dep + 1), vis[i] = 0;
}

int main()
{
	int t = 0;
	while (scanf("%d%d", &N, &R))
	{
		if (!N && !R)
			break;

		memset(ans, 0x00, sizeof ans);
		memset(vis, 0x00, sizeof vis);

		for (int i = 1; i <= N; i++)
			scanf("%lf", &p[i]);
		dfs(0, 0);

		printf("Case %d:\n", ++t);
		for (int i = 1; i <= N; i++)
			printf("%.6lf\n", ans[i] / ans[0]);
	}

	return 0;
}
