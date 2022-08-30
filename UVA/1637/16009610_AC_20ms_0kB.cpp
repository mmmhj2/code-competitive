#include <iostream>
#include <cstring>
#include <cstdio>
#define ARRAYACCESS [x1][x2][x3][x4][x5][x6][x7][x8][x9]
#define COMMAACCESS x1, x2, x3, x4, x5, x6, x7, x8, x9
using namespace std;

char str[4][5];
int deck[10][5];

bool vis[5][5][5][5][5][5][5][5][5];
double dp[5][5][5][5][5][5][5][5][5];

double DFS(int x1, int x2, int x3, int x4, int x5, int x6, int x7, int x8,
		int x9)
{
	if (vis ARRAYACCESS)
		return (dp ARRAYACCESS);
	(vis ARRAYACCESS) = true;

	int nextState[10] =
	{ 0, COMMAACCESS };
	bool flag = true;

	for (int i = 1; i <= 9; i++)
		if (nextState[i] != 0)
		{
			flag = false;
			break;
		}

	if (flag)
		return (dp ARRAYACCESS = 1);

	int tot = 0;
	double cnt = 0;
	for (int i = 1; i <= 9; i++)
		for (int j = i + 1; j <= 9; j++)
		{
			if (nextState[i] <= 0 || nextState[j] <= 0
					|| deck[i][nextState[i]] != deck[j][nextState[j]])
				continue;

			nextState[i]--, nextState[j]--;
			tot++;

			cnt += DFS(nextState[1], nextState[2], nextState[3], nextState[4],
					nextState[5], nextState[6], nextState[7], nextState[8],
					nextState[9]);
			nextState[i]++, nextState[j]++;
		}
	if(tot > 0)
		dp ARRAYACCESS = (1.0 * cnt) / (1.0 * tot);

	return dp ARRAYACCESS;
}

int main()
{
	while (scanf("%s%s%s%s", str[0], str[1], str[2], str[3]) != EOF)
	{
		for (int i = 1; i <= 4; i++)
			deck[1][i] = str[i-1][0];
		for (int k = 2; k <= 9; k++)
		{
			scanf("%s%s%s%s", str[0], str[1], str[2], str[3]);
			for (int i = 1; i <= 4; i++)
				deck[k][i] = str[i-1][0];
		}

		memset(dp, 0x00, sizeof dp);
		memset(vis, 0x00, sizeof vis);

		DFS(4, 4, 4, 4, 4, 4, 4, 4, 4);

		printf("%.6lf\n", dp[4][4][4][4][4][4][4][4][4]);
		fflush(stdout);
	}
}
