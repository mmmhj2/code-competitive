// BZOJ5001 搞事情
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 400 + 10;
const int DIR[4][2] =
{
{ 0, 1 },
{ 0, -1 },
{ 1, 0 },
{ -1, 0 } };
int N, M;

namespace Gauss
{
int equ;
bitset<MAXN> a[MAXN];

void printMatrix()
{
	for(int i = 1; i <= equ; i++)
		for(int j = 1; j <= equ + 1; j++)
			printf("%d%c", (bool)a[i][j], " \n"[j == equ + 1]);
}

void gauss()
{
	for (int i = 1; i <= equ; i++)
	{
		//printMatrix();
		int swp = i;
		while (swp <= equ && !a[swp][i])
			swp++;
		if (swp > equ)
			continue;
		if (i != swp)
			swap(a[i], a[swp]);

		for (int k = i + 1; k <= equ; k++)
			if (a[k][i])
				a[k] = a[k] ^ a[i];
	}
}
}

bool isFeasible()
{
	using namespace Gauss;
	for (int i = 1; i <= equ; i++)
	{
		if (!a[i][equ + 1])
			continue;
		bool flag = true;
		for (int k = 1; k <= equ; k++)
			if (a[i][k])
			{
				flag = false;
				break;
			}

		if (flag)
			return false;
	}
	return true;
}

inline int getId(int x, int y)
{
	return (x - 1) * N + y;
}

inline bool inside(int x, int y)
{
	return (x <= N && y <= M && x > 0 && y > 0);
}

int ansLen = 0x7F7F7F7F;
int ans[MAXN], tans[MAXN];

void DFS(int cur, int cnt)
{
	using namespace Gauss;
	if (ansLen < cnt)
		return;
	if (cur == 0)
	{
		if (cnt < ansLen)
			return ansLen = cnt, memcpy(ans, tans, sizeof tans), (void) 0;
		bool isSmaller = false;
		for(int i = 1; i <= Gauss::equ; i++)
			if(tans[i] < ans[i])
			{
				isSmaller = true;
				break;
			}
			else if(tans[i] > ans[i])
				break;

		if(isSmaller)
			memcpy(ans, tans, sizeof tans);
		return;
	}

	if(a[cur][cur])
	{
		int tmp = a[cur][equ + 1];
		for(int i = cur + 1; i <= equ; i++)
			tmp ^= tans[i] * a[cur][i];
		tans[cur] = tmp;
		DFS(cur - 1, cnt + tmp);
	}
	else
	{
		tans[cur] = 0;
		DFS(cur - 1, cnt);
		tans[cur] = 1;
		DFS(cur - 1, cnt + 1);
	}

}

int main()
{
	using namespace Gauss;
	scanf("%d%d", &N, &M);
	equ = N * M;
	for (int i = 1; i <= N; i++)
		for (int j = 1; j <= M; j++)
		{
			int t;
			scanf("%d", &t);
			a[getId(i, j)][equ + 1] = t;
			a[getId(i, j)][getId(i, j)] = true;
		}
	for (int i = 1; i <= N; i++)
		for (int j = 1; j <= M; j++)
			for (int k = 0; k < 4; k++)
			{
				int nx = i + DIR[k][0], ny = j + DIR[k][1];
				//printf("(%d,%d)->(%d,%d)\n", i, j, nx, ny);
				if (!inside(nx, ny))
					continue;
				//puts("Successful");
				a[getId(i, j)][getId(nx, ny)] = true;
			}

	gauss();

	if (!isFeasible())
		return puts("IMPOSSlBLE"), 0;

	DFS(equ, 0);
	for (int i = 1; i <= equ; i++)
		printf("%d%c", ans[i], " \n"[i % M == 0]);

	return 0;
}
