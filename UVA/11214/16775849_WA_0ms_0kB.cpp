#include <bits/stdc++.h>
using namespace std;
int N, M;
int maxDeep;
bool vis[4][30];
char board[20][20];

inline bool checkSquare(int x, int y)
{
	if (board[x][y] != 'X')
		return true;
	if (!vis[0][x] && !vis[1][y] && !vis[2][x + y] && !vis[3][x - y + 11])
		return false;
	return true;
}

bool IDDFS(int dep, int row)
{
	if (dep == maxDeep)
	{
		for (int i = 1; i <= N; i++)
			for (int j = 1; j <= M; j++)
				if (!checkSquare(i, j))
					return false;
		return true;
	}

	for (int i = row; i <= N; i++)
		for (int j = 1; j <= M; j++)
			if (!vis[0][i] || !vis[1][j] || !vis[2][i + j]
					|| !vis[3][i - j + 11])
			{
				int v0, v1, v2, v3;
				v0 = vis[0][i], v1 = vis[1][j], v2 = vis[2][i + j], v3 =
						vis[3][i - j + 11];
				vis[0][i] = vis[1][j] = vis[2][i + j] = vis[3][i - j + 11] =
						true;
				if (IDDFS(dep + 1, i + 1))
					return true;
				vis[0][i] = v0, vis[1][j] = v1, vis[2][i + j] = v2, vis[3][i - j
						+ 11] = v3;
			}
	return false;
}

int main()
{
	int kase = 0;
	while (~scanf("%d", &N) && N)
	{
		scanf("%d", &M);
		for (int i = 1; i <= N; i++)
			scanf("%s", board[i] + 1);

		for (maxDeep = 1; maxDeep <= 5; maxDeep++)
		{
			if (IDDFS(0, 0))
				break;
		}
		printf("Case %d: %d\n", ++kase, maxDeep);
	}
	return 0;
}