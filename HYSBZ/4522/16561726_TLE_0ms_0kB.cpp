#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <vector>

using namespace std;

typedef long long i64;

namespace millerRabin
{

template<class T>
T templateAbs(const T & x)
{
	if (x > 0)
		return x;
	return -x;
}

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
		d = __gcd(templateAbs(x - y), n);
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

namespace extendedEuc
{
void exGCD(i64 a, i64 b, i64 mod, i64 & x, i64 & y)
{
	if (!b)
		return x = 1, y = 0, (void) 0;
	exGCD(b, a % b, mod, y, x);
	y = (y - millerRabin::modularMul(a / b, x, mod) + mod) % mod;
}
}

int main()
{
	i64 e, N, c, p, r;
	i64 d, y, n;
	//cin >> e >> N >> c ;
	scanf("%lld %lld %lld", &e, &N, &c);
	p = pollardRho::pollard_Rho(N);
	r = (p - 1) * (N / p - 1);
	extendedEuc::exGCD(e, r, r, d, y);
	n = millerRabin::modularExp(c, d, N);
	//cout << d << " " << n << endl ;
	printf("%lld %lld\n", d, n);
	return 0;
}
