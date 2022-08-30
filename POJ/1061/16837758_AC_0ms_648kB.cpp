#include <iostream>
using namespace std;
typedef long long i64;

void extendedEuclidean(i64 a, i64 b, i64 & x, i64 & y, i64 & d)
{

	if (!b)
		return x = 1, y = 0, d = a, (void) 0;
	i64 _x = 0, _y = 0;
	extendedEuclidean(b, a % b, _x, _y, d);
	x = _y;
	y = _x - a / b * _y;
}
int main()
{
	i64 x, y, m, n, l;
	i64 k1, k2, d;

	cin >> x >> y >> m >> n >> l;

	k1 = 0, k2 = 0, d = 0;
	extendedEuclidean(m - n, -l, k1, k2, d);
	//cerr << k1 << " " << k2 << " " << d << endl;
	if ((y - x) % d != 0)
		cout << "Impossible" << endl;
	else
	{

		k1 *= (y - x) / d;
		l /= d;
		if (l < 0)
			l = -l;
		k1 %= l;
		if (k1 < 0)
			k1 += l;
		cout << k1 << endl;
	}

	return 0;
}
