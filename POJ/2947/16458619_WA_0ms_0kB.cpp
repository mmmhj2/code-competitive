// POJ2947 Widget Factory
#include <algorithm>
#include <cstring>
#include <cstdio>
using namespace std;

int N, M;

inline int LCM(int a, int b)
{
	return a * b / __gcd(a, b);
}

int toDay(char s[])
{
	switch(s[0])
	{
	case 'M':
		return 1;
	case 'T':
		if(s[1] == 'U')
			return 2;
		return 4;
	case 'W':
		return 3;
	case 'F':
		return 5;
	case 'S':
		if(s[1] == 'A')
			return 6;
		return 7;
	}
	return -1;
}

namespace Gauss
{
const int MAXN = 300 + 10;
int var, equ;
int a[MAXN][MAXN];
int x[MAXN];

int gauss()
{
	int col(0);
	int k;
	for(k = 0; k < equ && col < var; k++, col++)
	{
		int mxr = k;
		for(int i = k + 1; i < equ; i++)
			if(abs(a[i][col]) > abs(a[mxr][col]))
				mxr = i;
		if(mxr != k)
			for(int j = k; j <= var; j++)
				swap(a[k][j], a[mxr][j]);
		if(a[k][col] == 0)
		{
			k--;
			continue;
		}

		for(int i = k + 1; i < equ; i++)
			if(a[i][col] != 0)
			{
				int lcm = LCM(abs(a[i][col]), abs(a[k][col]));
				int ta = lcm / abs(a[i][col]);
				int tb = lcm / abs(a[k][col]);

				if(a[i][col] * a[k][col] < 0)
					tb = -tb;
				for(int j = col; j <= var; j++)
					a[i][j] = ((a[i][j] * ta - a[k][j] * tb) % 7 + 7) % 7;
			}
	}

	for(int i = k; i < equ; i++)
		if(a[i][col] != 0)
			return -1;
	if(k < var)
		return var - k;

	for(int i = var - 1; i >= 0; i--)
	{
		int tmp = a[i][var];
		for(int j = i + 1; j < var; j++)
		{
			if(a[i][j])
				tmp -= a[i][j] * x[j];
			tmp = (tmp % 7 + 7) % 7;
		}
		while(tmp % a[i][i])
			tmp += 7;
		x[i] = (tmp / a[i][i]) % 7;
	}
	return 0;
}

}

int main()
{
	using namespace Gauss;

	char s[5], t[5];
	int T, n;

	while(scanf("%d%d", &N, &M) != EOF)
	{
		if(N == 0 && M == 0)
			break;
		var = N, equ = M;

		for(int i = 1; i <= M; i++)
		{
			scanf("%d%s%s", &T, s, t);
			a[i][N] = ((toDay(t) - toDay(s) + 1) % 7 + 7) % 7;

			for(int j = 1; j <= T; j++)
				scanf("%d", &n),
				a[i][n-1] = (a[i][n-1] + 1) % 7;
		}

		int free = gauss();
		if(free == 0)
			for(int i = 0; i < N; i++)
				printf("%d%c", x[i] + (x[i] < 3 ? 7 : 0), " \n"[i == N - 1]);
		else if(free > 0)
			puts("Inconsistent data.");
		else
			puts("Multiple solutions.");
	}

	return 0;
}
