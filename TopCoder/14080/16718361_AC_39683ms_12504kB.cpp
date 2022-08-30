#include <bits/stdc++.h>
using namespace std;

class BearPermutations
{
	const static int MAXN = 200 ;

	int dp[MAXN][MAXN][3];
	int C[MAXN][MAXN];

public:
	int countPermutations(int N, int S, int MOD);
};

inline int BearPermutations::countPermutations(int N, int S, int MOD)
{
	for(int i = 0; i <= N; i++)
		for(int j = 0; j <= N; j++)
			C[i][j] = (j == 0 ? 1 : (i == 0 ? 0 : C[i-1][j-1] + C[i-1][j])) % MOD;

	for(int n = 1; n <= N; n++)
		for(int s = 0; s <= S; s++)
			for(int k = 0; k <= 2; k++)
			{
				int ft = 0, delta;
				for(int pos = 0; pos < n; pos++)
				{
					delta = 0;
					if(k == 1)
						delta = pos + 1;
					if(k == 2)
						delta = n - pos;
					if(delta > s)
						continue;

					for(int sL = 0; sL <= s - delta; sL++)
					{
						int sR = s - delta - sL;
						if(pos == 0 && sL > 0)
							continue;
						if(pos == n - 1 && sR > 0)
							continue;
						int cur = C[n - 1][pos];
						if(pos > 0)
							cur = 1LL * cur * dp[pos][sL][(pos == n - 1) ? 0 : 2] % MOD;
						if(pos < n - 1)
							cur = 1LL * cur * dp[n - pos - 1][sR][(pos == 0) ? 0 : 1] % MOD;
						ft = (1LL * ft + cur) % MOD;
					}
				}
				dp[n][s][k] = ft;
			}
	int ans = 0;
	for(int s = 0; s <= S; s++)
		ans = (ans + dp[N][s][0]) % MOD;
	return ans;
}
