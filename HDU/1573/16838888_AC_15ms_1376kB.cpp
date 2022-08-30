#include <bits/stdc++.h>
using namespace std;
typedef long long i64;

const int MAXM = 10 + 5;

i64 N, M;
i64 a[MAXM], b[MAXM];

template<class T>
void extendedEuclidean(T a, T b, T & x, T & y, T & d)
{

	if (!b)
		return x = 1, y = 0, d = a, (void) 0;
	i64 _x = 0, _y = 0;
	extendedEuclidean(b, a % b, _x, _y, d);
	x = _y;
	y = _x - a / b * _y;
}

template<class T>
T getInversion(T x, T mod)
{
	T _x = 0, _y = 0, d = 0;
	extendedEuclidean(x, mod, _x, _y, d);
	_x = (_x % mod + mod) % mod;
	if (_x == 0)
		_x += mod;

	return _x;
}

int main()
{
	int T;

	scanf("%d", &T);
	while (T--)
	{
		bool flag = true;
		scanf("%lld%lld", &N, &M);
		for (int i = 1; i <= M; i++)
			scanf("%lld", &a[i]);
		for (int i = 1; i <= M; i++)
			scanf("%lld", &b[i]), b[i] %= a[i];

		for (int k = 2; k <= M; k++)
		{
			i64 a1, a2, b1, b2, gcd;
			b1 = b[k - 1], b2 = b[k], a1 = a[k - 1], a2 = a[k];
			gcd = __gcd(a1, a2);

			if ((b1 - b2) % gcd)
			{
				flag = false;
				continue;
			}

			a[k] = a1 * a2 / gcd;
			b[k] = ((getInversion(a1 / gcd, a2 / gcd) * ((b2 - b1) / gcd) % (a2 / gcd)
					* a1 + b1) % a[k] + a[k]) % a[k];
			//cerr << a[k] << " " << b[k] << endl ;
		}

		if (!flag)
			puts("0");
		else
		{
			i64 ans;
			if (N < b[M])
				ans = 0;
			else
			{
				ans = (N - b[M]) / a[M] + 1;
				if (b[M] == 0)
					ans--;
			}
			printf("%lld\n", ans);
		}

	}
	return 0;
}
