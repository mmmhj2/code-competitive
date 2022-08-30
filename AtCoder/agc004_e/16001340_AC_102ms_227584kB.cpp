#include <algorithm>
#include <cstdio>
#include <vector>
#include <queue>
using namespace std;

typedef short int i16;
typedef unsigned short int u16;

const int MAXN = 100 + 5;

int answer;
int N, M;
i16 ex, ey;
i16 row[MAXN][MAXN], col[MAXN][MAXN];
i16 dp[MAXN][MAXN][MAXN][MAXN];

char mp[MAXN][MAXN];

int main()
{
	scanf("%d%d", &N, &M);
	for (int i = 1; i <= N; i++)
		scanf("%s", mp[i] + 1);

	for (i16 i = 1; i <= N; i++)
		for (i16 j = 1; j <= M; j++)
		{
			row[i][j] = row[i][j - 1] + (mp[i][j] == 'o'), col[i][j] =
					col[i - 1][j] + (mp[i][j] == 'o');
			if (mp[i][j] == 'E')
				ex = i, ey = j;
		}

	for (i16 i = ex; i >= 1; i--)
		for (i16 j = ey; j >= 1; j--)
			for (i16 k = ex; k <= N; k++)
				for (i16 l = ey; l <= M; l++)
				{
					i16 bl, bh;

					bl = max((int)j - 1, l - ey), bh = min((int)l, M - ey + j);

					if (i > 1 && k - ex < i - 1)
						dp[i - 1][j][k][l] = max((int)dp[i - 1][j][k][l],
								dp[i][j][k][l] + row[i - 1][bh]
										- row[i - 1][bl]);

					if (k < N && ex + k < N + i)
						dp[i][j][k + 1][l] = max((int)dp[i][j][k + 1][l],
								dp[i][j][k][l] + row[k + 1][bh]
										- row[k + 1][bl]);


					bl = max((int)i - 1, k - ex), bh = min((int)k, N - ex + i);

					if (j > 1 && l - ey < j - 1)
						dp[i][j - 1][k][l] = max((int)dp[i][j - 1][k][l],
								dp[i][j][k][l] + col[bh][j - 1]
										- col[bl][j - 1]);

					if (l < M && ey + l < M + j)
						dp[i][j][k][l + 1] = max((int)dp[i][j][k][l + 1],
								dp[i][j][k][l] + col[bh][l + 1]
										- col[bl][l + 1]);
					answer = max(answer, (int) max(
					{ dp[i - 1][j][k][l], dp[i][j - 1][k][l],
							dp[i][j][k + 1][l], dp[i][j][k][l + 1] }));
				}
	printf("%d\n", answer);
	return 0;
}
