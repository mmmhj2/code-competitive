// UVa 225 Golygons
#include <bits/stdc++.h>
using namespace std;

const int ORIGIN = 100;

const char dir[2][2] = { { 'e', 'w' }, { 'n', 's' } };
const int dirOffset[2][2][2] = { { { 1, 0 }, { -1, 0 } },
		{ { 0, 1 }, { 0, -1 } } };

string ans;
int ansCnt;
bool ob[200 + 10][200 + 10];
bool vis[200 + 10][200 + 10];

int N, K;

bool check(int x, int y, int len, int d1, int d2)
{
	for (int i = 1; i <= len; i++)
	{
		x += dirOffset[d1][d2][0], y += dirOffset[d1][d2][1];
		if (ob[x][y])
			return false;
	}
	return true;
}

void DFS(int len, int x, int y, int lastDir)
{
	if (len == N + 1)
	{
		if (x != ORIGIN || y != ORIGIN)
			return;
		printf("%s\n", ans.c_str());
		ansCnt++;
		return;
	}

	if (abs(x - ORIGIN) + abs(y - ORIGIN) > (N - len + 1) * (N + len) / 2)
		return;
	for (int i = 0; i < 2; i++)
	{
		int nx, ny;
		nx = x + len * dirOffset[lastDir][i][0], ny = y
				+ len * dirOffset[lastDir][i][1];
		if (len != N && nx == ORIGIN && ny == ORIGIN)
			continue;
		if (nx < 0 || ny < 0)
			continue;
		if (nx > ORIGIN * 2 || ny > ORIGIN * 2)
			continue;
		if (vis[nx][ny])
			continue;
		if (!check(x, y, len, lastDir, i))
			continue;

		ans.push_back(dir[lastDir][i]);
		vis[nx][ny] = true;
		DFS(len + 1, nx, ny, lastDir ^ 1);
		vis[nx][ny] = false;
		ans.pop_back();
	}
}

int main()
{

	int T;
	scanf("%d", &T);

	while (T--)
	{
		ansCnt = 0;
		memset(ob, 0x00, sizeof ob);
		scanf("%d%d", &N, &K);

		for (int i = 1; i <= K; i++)
		{
			int x, y;
			scanf("%d%d", &x, &y);
			if (abs(x) > ORIGIN || abs(y) > ORIGIN)
				continue;
			ob[ORIGIN + x][ORIGIN + y] = true;
		}

		if (!ob[ORIGIN + 1][ORIGIN])
			ans.push_back('e'), vis[ORIGIN + 1][ORIGIN] = true, DFS(2,
					ORIGIN + 1, ORIGIN, 1), vis[ORIGIN + 1][ORIGIN] = false, ans.pop_back();
		if (!ob[ORIGIN][ORIGIN + 1])
			ans.push_back('n'), vis[ORIGIN][ORIGIN + 1] = true, DFS(2, ORIGIN,
					ORIGIN + 1, 0), vis[ORIGIN][ORIGIN + 1] = false, ans.pop_back();
		if (!ob[ORIGIN][ORIGIN - 1])
			ans.push_back('s'), vis[ORIGIN][ORIGIN - 1] = true, DFS(2, ORIGIN,
					ORIGIN - 1, 0), vis[ORIGIN][ORIGIN - 1] = false, ans.pop_back();
		if (!ob[ORIGIN - 1][ORIGIN])
			ans.push_back('w'), vis[ORIGIN - 1][ORIGIN] = true, DFS(2,
					ORIGIN - 1, ORIGIN, 1), vis[ORIGIN - 1][ORIGIN] = false, ans.pop_back();
		printf("Found %d golygon(s).\n\n", ansCnt);
	}

	return 0;
}
