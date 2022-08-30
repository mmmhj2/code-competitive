// BZOJ1218
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 5000 + 10;

int N, R;
int ans;
int sum[MAXN][MAXN];

int main()
{
	cin >> N >> R;
	for (int i = 1; i <= N; i++)
	{
		int x, y, w;
		cin >> x >> y >> w;
		sum[x + 1][y + 1] += w;
	}

	for (int i = 1; i < MAXN; i++)
		for (int j = 1; j < MAXN; j++)
			sum[i][j] += sum[i - 1][j];
	for (int i = 1; i < MAXN; i++)
		for (int j = 1; j < MAXN; j++)
			sum[i][j] += sum[i][j - 1];

	for (int i = R; i < MAXN; i++)
		for (int j = R; j < MAXN; j++)
			ans = max(ans,
					sum[i][j] - sum[i - R][j] - sum[i][j - R]
							+ sum[i - R][j - R]);
	cout << ans << endl ;
	return 0;
}
