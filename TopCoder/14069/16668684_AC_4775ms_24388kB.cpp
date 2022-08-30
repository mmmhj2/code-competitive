#include <bits/stdc++.h>
using namespace std;

class BearDestroys
{
	static const int MAXN = 20000 + 10;
	int W, H, MOD;

	int dp1[80][MAXN], dp2[80][MAXN];

	void DFS(int r, int sum, int mask, int nmask, int ft, int wt);
public:
	int sumUp(int _W, int _H, int _MOD);
};

inline void BearDestroys::DFS(int r, int sum, int mask, int nmask, int ft,
		int wt)
{
	if (r == H)
		return dp1[sum + 1][nmask] = (dp1[sum + 1][nmask] + ft) % MOD, dp2[sum
				+ 1][nmask] = (dp2[sum + 1][nmask] + wt) % MOD, (void) 0;

	int c = sum - r;
	if (0 <= c && c < W)
	{
		if (mask & (1 << r))
			DFS(r + 1, sum, mask, nmask, 2LL * ft % MOD, 2LL * wt % MOD);
		else
		{
			if (c == W - 1 || (nmask & (1 << r)))
			{
				if (r == H - 1)
					DFS(r + 1, sum, mask, nmask, 2LL * ft % MOD,
							2LL * wt % MOD);
				else
					DFS(r + 1, sum, mask, nmask + (1 << (r + 1)),
							(2LL * ft % MOD + 2LL * wt % MOD) % MOD,
							2LL * wt % MOD);

			}
			else
			{
				if (r == H - 1)
					DFS(r + 1, sum, mask, nmask + (1 << r),
							(2LL * ft % MOD + 2LL * wt % MOD) % MOD,
							2LL * wt % MOD);
				else
					DFS(r + 1, sum, mask, nmask + (1 << r), (ft + wt) % MOD,
							wt), DFS(r + 1, sum, mask, nmask + (1 << (r + 1)),
							(ft + wt) % MOD, wt);
			}
		}
	}
	else
		DFS(r + 1, sum, mask, nmask, ft, wt);
}

inline int BearDestroys::sumUp(int _W, int _H, int _MOD)
{
	W = _W, H = _H, MOD = _MOD;
	int sMax = W + H - 2;

	for (int i = 0; i <= sMax + 1; i++)
		for (int t = 0; t < (1 << H); t++)
			dp1[i][t] = dp2[i][t] = 0;
	dp1[0][0] = 0, dp2[0][0] = 1;

	for (int i = 0; i <= sMax; i++)
		for (int t = 0; t < (1 << H); t++)
			if (dp1[i][t] || dp2[i][t])
				DFS(0, i, t, 0, dp1[i][t], dp2[i][t]);
	return dp1[sMax + 1][0];
}
