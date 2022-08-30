// BZOJ4031 小Z的房间
#include <bits/stdc++.h>
using namespace std;
typedef long long i64;
const int MAXN = 15;
const int MOD = 1e9;
const int DIR[4][2] =
{
{ 0, 1 },
{ 0, -1 },
{ 1, 0 },
{ -1, 0 } };

int N, M;

char room[MAXN][MAXN];
int id[MAXN][MAXN], idCnt;

namespace Gauss
{
int a[MAXN * MAXN][MAXN * MAXN];
i64 solveDet()
{
	i64 ret = 1;

	int ed = idCnt - 1;
	for(int i = 1; i <= ed; i++)
		for(int j = 1; j <= ed; j++)
			a[i][j] = (a[i][j] + MOD) % MOD;
	for(int j = 1; j <= ed; j++)
	{
		for(int i = j + 1; i <= ed; i++)
			while(a[i][j])
			{
				i64 tmp = a[j][j] / a[i][j];
				for(int k = j; k <= ed; k++)
					a[j][k] = (a[j][k] - tmp * a[i][k] % MOD + MOD) % MOD,
					swap(a[i][k], a[j][k]);
				ret *= -1;
			}
		ret = ret * a[j][j] % MOD;
	}

	while(ret < 0)
		ret += MOD;
	return ret;
}
}

int main()
{
	using namespace Gauss;
	scanf("%d%d", &N, &M);
	for (int i = 1; i <= N; i++)
		scanf("%s", &room[i][1]);
	/*
	for (int i = 0; i <= N + 1; i++)
		room[i][0] = room[i][M + 1] = '*';
	for (int i = 0; i <= M + 1; i++)
		room[0][i] = room[N + 1][i] = '*';
	*/
	for(int i = 0; i <= N + 1; i++)
		for(int j = 0; j <= M + 1; j++)
			if(i == 0 || j == 0 || i == N + 1 || j == M + 1)
				room[i][j] = '*';

	for (int i = 1; i <= N; i++)
		for (int j = 1; j <= M; j++)
			if (room[i][j] == '.')
			{
				id[i][j] = ++idCnt;
				if(room[i-1][j] == '.')
//					printf("(%d,%d)[%d]->(%d,%d)[%d]\n", i, j, id[i][j], i-1, j, id[i-1][j]),
					a[id[i][j]][id[i-1][j]] = true,
					a[id[i-1][j]][id[i][j]] = true;
				if(room[i][j-1] == '.')
//					printf("(%d,%d)[%d]->(%d,%d)[%d]\n", i, j, id[i][j], i, j-1, id[i][j-1]),
					a[id[i][j]][id[i][j-1]] = true,
					a[id[i][j-1]][id[i][j]] = true;
			}

	for(int i = 1; i <= idCnt; i++)
		for(int j = 1; j <= idCnt; j++)
			if(a[i][j] && i != j)
				a[i][i]++;
	printf("%lld\n", solveDet());
	return 0;
}

