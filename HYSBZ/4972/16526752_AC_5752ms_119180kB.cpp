// BZOJ4972 小Q的方格纸
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 3e3 + 10;
const int MAXQ = 3000000 + 10;

int N, M, Q;

unsigned ans;
unsigned a[MAXN][MAXN], b[MAXN][MAXN], c[MAXN][MAXN];
unsigned pow_233[MAXQ];

namespace RNG
{
unsigned A, B, C;

unsigned RNG61()
{
	A ^= A << 16;
	A ^= A >> 5;
	A ^= A << 1;
	unsigned int t = A;
	A = B;
	B = C;
	C ^= t ^ A;
	return C;
}

}

int main()
{
	using RNG::RNG61;
	pow_233[0] = 1;
	for (int i = 1; i < MAXQ; i++)
		pow_233[i] = pow_233[i - 1] * 233;

	cin >> N >> M >> Q >> RNG::A >> RNG::B >> RNG::C;

	for(int i = 1; i <= N; i++)
	{
		for(int j = 1; j <= M; j++)
			a[i][j] = RNG61(), b[i][j] = b[i][j-1] + a[i][j], c[i][j] = b[i][j] + c[i-1][j+1], a[i][j] = b[i][j] + a[i-1][j];
		c[i][0] = c[i-1][1];
	}

	for(int i = 1; i <= Q; i++)
	{
		unsigned x, y, k, t1, t2, t3, t4;
		x = RNG61() % N + 1;
		y = RNG61() % M + 1;
		k = RNG61() % min(x, y) + 1;
		int dx = max(0, (signed)(x - k)), dy = max(0, (signed)(y - k));
		t1 = c[x][dy] - c[dx][y];
		t2 = a[x][dy] - a[dx][dy];
		t3 = t1 - t2;
		t4 = a[x][y] - a[dx][y] - a[x][dy] + a[dx][dy];

		ans += pow_233[Q - i] * (t4 - t3);
	}
	cout << ans << endl ;
	return 0;
}
