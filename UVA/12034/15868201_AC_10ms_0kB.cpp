#include <algorithm>
#include <iostream>
#include <fstream>
#include <cstring>
#include <vector>
#include <cmath>
using namespace std;


const int MOD = 10056;
const int MAXN = 1000 + 10;

int C[MAXN][MAXN];
int F[MAXN];

void getBinomial()
{
	C[1][0] = 1, C[1][1] = 1;
	for(int i = 2; i < MAXN; i++)
	{
		C[i][0] = 1;
		for(int j = 1; j <= i; j++)
			C[i][j] = (C[i-1][j-1] % MOD + C[i-1][j] % MOD) % MOD ;
	}
}

void preCalculate()
{
	F[0] = 1;
	for(int N = 1; N < MAXN; N++)
		for(int i = 0; i <= N; i++)
			F[N] = (F[N] + (C[N][i] * F[N - i] % MOD)) % MOD;
}

int main()
{
	int kase, N;

	getBinomial();
	preCalculate();

	scanf("%d", &kase);
	for(int i = 1; i <= kase; i++)
	{
		scanf("%d", &N);
		printf("Case %d: %d\n", i, F[N]);
	}
}

