#include <algorithm>
#include <cstdlib>
#include <cstdio>
#include <map>

using std::map;
using std::pair;
using std::make_pair;

typedef long long i64;
const int MAXN = 20 + 5;

i64 F[MAXN][MAXN][MAXN];

void prepare()
{
	F[1][1][1] = 1;

	for(int i = 2; i < MAXN; i++)
		for(int j = 1; j < MAXN; j++)
			for(int k = 1; k < MAXN; k++)
				F[i][j][k] = F[i-1][j-1][k] + F[i-1][j][k-1] + F[i-1][j][k] * (i - 2);
}

int main()
{
	prepare();
	int kase;
	scanf("%d", &kase);

	while(kase--)
	{
		int N, L, R;
		scanf("%d%d%d", &N, &L, &R);
		printf("%lld\n", F[N][L][R]);
	}


    return 0;
}