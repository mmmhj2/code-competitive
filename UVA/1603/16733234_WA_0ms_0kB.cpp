#include <bits/stdc++.h>
using namespace std;

typedef long long i64;

i64 power_2[64];

int maxDep;
int N, tot;

i64 base[10][10];

int cnt;
i64 square[100];

inline int getIdUD(int x, int y)
{
	//fprintf(stderr, "getIdUD(%d,%d) : %d\n", x, y, (2 * N + 1) * (x - 1) + y);
	return (2 * N + 1) * (x - 1) + y - 1;
}

inline int getIdLR(int x, int y)
{
	//fprintf(stderr, "getIdLR(%d,%d) : %d\n", x, y, (2 * N + 1) * (x - 1) + y + N);
	return (2 * N + 1) * (x - 1) + y + N - 1;
}

void buildGraph()
{
	cnt = 0;
	memset(base, 0x00, sizeof base);
	memset(square, 0x00, sizeof square);
	for (int i = 1; i <= N; i++)
		for (int j = 1; j <= N; j++)
			square[++cnt] = (base[i][j] |= (power_2[getIdLR(i, j)]
					| power_2[getIdLR(i, j + 1)] | power_2[getIdUD(i, j)]
					| power_2[getIdUD(i + 1, j)]));

	for(int sz = 2; sz <= N; sz++)
		for(int i = 1; i + sz - 1 <= N; i++)
			for(int j = 1; j + sz - 1 <= N; j++)
			{
				cnt++;
				for(int offsetX = 0; offsetX < sz; offsetX++)
					for(int offsetY = 0; offsetY < sz; offsetY++)
						square[cnt] ^= base[i + offsetX][j + offsetY];
			}
}

bool DFS(int dep, i64 st)
{
	if(dep == maxDep)
	{
		for(int i = 1; i <= cnt; i++)
			if((square[i] & st) == square[i])
				return false;
		return true;
	}

	i64 nxtSt = st;
	int leastNeed = 0, delMatch = 0;
	for(int i = 1; i <= cnt; i++)
		if((square[i] & nxtSt) == square[i])
		{
			leastNeed++;
			nxtSt ^= square[i];
			if(delMatch <= 0)
				delMatch = square[i];
		}
	if(dep + leastNeed > maxDep)
		return false;

	for(int i = 1; i <= tot; i++)
		if((delMatch & power_2[i-1]) == power_2[i-1])
			if(DFS(dep + 1, st ^ power_2[i-1]))
				return true;
	return false;
}

int main()
{

	power_2[0] = 1;
	for (int i = 1; i < 64; i++)
		power_2[i] = power_2[i - 1] << 1;

	int T, k, t;
	scanf("%d", &T);
	i64 initState;
	while (T--)
	{
		scanf("%d", &N);
		tot = 2 * N * (N + 1);
		initState = power_2[tot] - 1;

		scanf("%d", &t);
		for (int i = 1; i <= t; i++)
			scanf("%d", &k), initState ^= power_2[k - 1];

		buildGraph();
		maxDep = 0;
		while (!DFS(0, initState))
			maxDep++;
		printf("%d\n", maxDep);
		fflush(stdout);
	}

	return 0;
}
