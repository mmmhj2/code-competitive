#include <bits/stdc++.h>
using namespace std;

typedef long long i64;

namespace millerRabin
{
const int primelist[15] =
{ 1, 2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43 };

i64 modularMul(i64 a, i64 b, i64 mod)
{
	i64 ret = 0;
	a %= mod, b %= mod;

	while (b)
	{
		if (b & 1)
			ret = (ret + a) % mod;
		a = (a + a) % mod;
		b = b >> 1;
	}
	return ret;
}

i64 modularExp(i64 base, i64 exp, i64 mod)
{
	i64 ret = 1;
	base %= mod;
//	cerr << "Modular exp : " << base << " " << exp << " " << mod << endl ;
	while (exp)
	{
		if (exp & 1)
			ret = modularMul(ret, base, mod);
		base = modularMul(base, base, mod);
		exp = exp >> 1;
	}
	return ret;
}

bool miller_rabin_round(i64 d, i64 n, i64 a)
{
	i64 x = modularExp(a, d, n);
//	cerr << d << " " << n << " " << a << " " << x << endl ;
	if (x == 1 || x == n - 1)
		return true;
	while (d != n - 1)
	{
		x = modularMul(x, x, n), d *= 2;
		if (x == 1)
			return false;
		if (x == n - 1)
			return true;
	}
	return false;
}

bool isPrime(i64 n)
{
	if (n <= 1 || (n != 2 && ((n & 1) == 0)))
		return false;
	if (n <= 3)
		return true;
	i64 d = n - 1;
	while ((d & 1) == 0)
		d = d >> 1;
	for (int i = 1; i < 15; i++)
		if (primelist[i] >= n)
			break;
		else if (!miller_rabin_round(d, n, primelist[i]))
			return false;
	return true;
}

}

namespace pollardRho
{
using namespace millerRabin;

i64 rng(i64 x, i64 offset, i64 n)
{
	return (modularMul(x, x, n) + offset + n) % n;
}

i64 pollard_Rho(i64 n)
{
	if (n == 1)
		return 1;
	if ((n & 1) == 0)
		return 2;
	i64 x, y, c, d;
	x = y = (1LL * rand() * rand() % (n - 2)) + 2;
	c = (1LL * rand() * rand() % (n - 1)) + 1;
	d = 1;

	while (d == 1)
	{
		//cerr << "Pollard : " << x << " " << y << " " << c << " " << d << endl ;
		x = rng(x, c, n);
		y = rng(rng(y, c, n), c, n);
		d = __gcd(abs(x - y), n);
		if (d == n)
			return n;
	}
	return d;
}

void enumFactors(i64 n, vector<i64> & fac)
{
//	cerr << "enumFactor : " << n << endl ;
	if (isPrime(n))
		return fac.push_back(n), (void) 0;
	i64 p = n;
	while (p >= n)
		p = pollard_Rho(n);
	enumFactors(p, fac);
	enumFactors(n / p, fac);
}

}

int main()
{
	int T;
	i64 N;
	cin >> T;
	while (T--)
	{
		cin >> N;
		if (millerRabin::isPrime(N))
			cout << "Prime" << endl;
		else
		{
			vector <i64> fac;
//			cerr << "Enumerating factors" << endl ;
			pollardRho::enumFactors(N, fac);
			N = 0x7F7F7F7F;
			for(vector<i64>::iterator itr = fac.begin(); itr != fac.end(); ++itr)
				if(N > *itr)
					N = *itr;
			cout << N << endl ;
		}
	}
	return 0;
}
