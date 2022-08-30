#include <algorithm>
#include <cstdio>
#define REDIRECT(x) freopen(x".in", "r", stdin), freopen(x".out", "w", stdout)
#define CLOSEALL() fclose(stdin), fclose(stdout)
using namespace std;

const int MOD = 924844033;
const int MAXN = 2000 + 5;

int N, K;
int fact[MAXN];

int cnt;
bool vis[MAXN][2], visCnt[MAXN * 2];

int DP[MAXN * 2][MAXN][2];

void prepare()
{
	fact[0] = 1;
	for (int i = 1; i < MAXN; i++)
		fact[i] = 1LL * fact[i - 1] * i % MOD;
}

int main()
{
	//REDIRECT("captain");

	scanf("%d%d", &N, &K);
	prepare();

	for (int i = 1; i <= N; i++)
		for (int j = 0; j < 2; j++)
		{
			if (vis[i][j])
				continue;

			int a = i, b = j;
			while (a <= N)
				cnt++, vis[a][b] = true, a += K, b = b ^ 1;

			visCnt[cnt] = true;
		}

	DP[1][0][0] = 1;
	for (int i = 1; i <= cnt; i++)
		for (int j = 0; j <= N; j++)
		{
			DP[i + 1][j][0] = (DP[i][j][0] + DP[i][j][1]) % MOD;
			if (!visCnt[i])
				DP[i + 1][j + 1][1] = DP[i][j][0];
		}

	int signum = 1, answer = 0;
	for (int i = 0; i <= N; i++)
	{
		answer = (answer
				+ ((((1LL * signum * (DP[cnt][i][0] + DP[cnt][i][1]) % MOD)
						+ MOD) % MOD) * fact[N - i] % MOD)) % MOD;
		signum = -signum;
	}

	printf("%d\n", answer);

	CLOSEALL();
	return 0;
}
