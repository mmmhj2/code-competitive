#include <bits/stdc++.h>
using namespace std;
typedef long long i64;
const int MAXN = 2000000 + 10;
const int MOD = 1e9 + 7;

template<class T>
T modularExp(T base, T exp)
{
	T ret = 1;
	while (exp)
	{
		if (exp & 1)
			ret = ret * base % MOD;
		base = base * base % MOD;
		exp >>= 1;
	}
	return ret;
}
int fact[MAXN + 1], inv[MAXN + 1];

void prepare()
{
	fact[0] = 1;
	for (int i = 1; i <= MAXN; i++)
		fact[i] = 1LL * fact[i - 1] * i % MOD;
	inv[MAXN] = modularExp<i64>(fact[MAXN], MOD - 2) % MOD;
	for (int i = MAXN - 1; i >= 0; i--)
		inv[i] = 1LL * inv[i + 1] * (i + 1) % MOD;
	assert(inv[1] == 1);
}

i64 getBino(int n, int m)
{
	return 1LL * fact[n] * inv[m] % MOD * inv[n - m] % MOD;
}

i64 calcRect(int n, int m, int a, int b)
{
	return ((getBino(n + m + a + b, n + a) - getBino(m + a + b, a)
			- getBino(n + a + b, n + a) + getBino(a + b, a)) % MOD + MOD) % MOD;
}

int main()
{
	int x1, x2, x3, x4, x5, x6;
	int y1, y2, y3, y4, y5, y6;
	prepare();

	cin >> x1 >> x2 >> x3 >> x4 >> x5 >> x6 ;
	cin >> y1 >> y2 >> y3 >> y4 >> y5 >> y6 ;

	int n1 = x2 - x1 + 1, n2 = x6 - x5 + 1;
	int m1 = y2 - y1 + 1, m2 = y6 - y5 + 1;
	int answer = 0;

	for(int x = x3; x <= x4; x++)
		answer = (answer + calcRect(n1, m1, x-x2, y3-y2-1) * calcRect(n2, m2, x5-x, y5-y3) % MOD * (MOD - x - y3)) % MOD ,
		answer = (answer + calcRect(n1, m1, x-x2, y4-y2) * calcRect(n2, m2, x5-x, y5-y4-1) % MOD * (x + y4 + 1)) % MOD;
	for(int y = y3; y <= y4; y++)
		answer = (answer + calcRect(n1, m1, x3-x2-1, y-y2) * calcRect(n2, m2, x5-x3, y5-y) % MOD * (MOD - y - x3)) % MOD,
		answer = (answer + calcRect(n1, m1, x4-x2, y-y2) * calcRect(n2, m2, x5-x4-1, y5-y) % MOD * (y + x4 + 1)) % MOD;
	cout << answer << endl ;

}
