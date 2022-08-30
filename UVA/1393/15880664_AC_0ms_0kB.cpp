#include <algorithm>
#include <iostream>
#include <fstream>
#include <cstring>
#include <vector>
#include <cmath>
using namespace std;

const int MAXN = 300 + 10;

int tmp[MAXN][MAXN];
int ans[MAXN][MAXN];

template<class T>
inline T GCD(const T & a, const T & b)
{
	if (b == 0)
		return (a);
	return (GCD(b, a % b));
}

int main()
{
	int N, M;

	for (int i = 1; i <= 300; i++)
		for (int j = 1; j <= 300; j++)
			tmp[i][j] = tmp[i - 1][j] + tmp[i][j - 1] - tmp[i - 1][j - 1]
					+ (GCD(i, j) == 1);
	for (int i = 1; i <= 300; i++)
		for (int j = 1; j <= 300; j++)
			ans[i][j] = ans[i - 1][j] + ans[i][j - 1] - ans[i - 1][j - 1]
					+ tmp[i][j] - tmp[i / 2][j / 2];

	while (cin >> N >> M)
	{
		if (N == 0 && M == 0)
			break;
		cout << ans[N - 1][M - 1] * 2 << endl;
	}
}

