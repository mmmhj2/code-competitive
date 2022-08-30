// Codeforces626F Group Projects
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 200 + 10;
const int MAXK = 1000 + 10;
const int MOD = 1e9 + 7;

int N, K;
int A[MAXN];
struct dpVal
{
	int dp[MAXN][MAXK];
	int * operator [](int x)
	{
		return dp[x];
	}
} dp1, dp2;
dpVal *dpNew, *dpOld;

int main()
{
	ios::sync_with_stdio(false), cin.tie(nullptr);
	dpNew = &dp1, dpOld = &dp2;
	cin >> N >> K;
	for (int i = 1; i <= N; i++)
		cin >> A[i];
	sort(&A[1], &A[N + 1]);
	A[0] = A[1];

	(*dpNew)[0][0] = 1;

	for (int i = 1; i <= N; i++)
	{
		swap(dpNew, dpOld);
		memset(dpNew, 0x00, (sizeof (dpVal)));
		for (int j = 0; j <= N; j++)
		{
			int delta = A[i] - A[i - 1];
			//cerr << delta << endl ;
			for (int k = 0; k <= K; k++)
				if ((*dpOld)[j][k])
				{
					const int cur = k + j * delta;
					if (cur > K)
						break;
					(*dpNew)[j][cur] = ((*dpNew)[j][cur]
							+ (1LL * (*dpOld)[j][k] * (j + 1)) % MOD) % MOD;

					(*dpNew)[j + 1][cur] = ((*dpNew)[j + 1][cur]
							+ (*dpOld)[j][k]) % MOD;

					if (j)
						(*dpNew)[j - 1][cur] = ((*dpNew)[j - 1][cur]
								+ (1LL * (*dpOld)[j][k] * j) % MOD) % MOD;
				}
		}
	}

	int answer = 0;
	for (int i = 0; i <= K; i++)
		answer = (answer + (*dpNew)[0][i]) % MOD;
	cout << answer << endl;

	return 0;
}

