#include <bits/stdc++.h>

#if RAND_MAX <= 0x7FFF
#define getRand() rand() * rand() * rand() * rand()
#else
#define getRand() rand() * rand()
#endif

using namespace std;
typedef long long i64;

template<class T>
T templateAbs(T x)
{
	if (x < 0)
		return -x;
	return x;
}

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
	while (exp)
	{
		if (exp & 1)
			ret = modularMul(ret, base, mod);
		base = modularMul(base, base, mod);
		exp = exp >> 1;
	}
	return ret;
}

namespace MR_PrimeTest
{
	vector<int> primeList = { 1, 2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41,
			43 };

	bool miller_rabin(i64 d, i64 n, i64 a)
	{
		i64 x = modularExp(a, d, n);
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
		return true;
	}

	bool isPrime(i64 n)
	{
		if (n == 2 || n == 3)
			return true;
		if (((n & 1) == 0) || n <= 1)
			return false;

		i64 d = n - 1;
		while ((d & 1) == 0)
			d = d >> 1;
		for (vector<int>::iterator itr = primeList.begin();
				itr != primeList.end(); ++itr)
			if (*itr >= n)
				break;
			else if (!miller_rabin(d, n, *itr))
				return false;
		return true;
	}

}

namespace pollar_rho
{
	using namespace MR_PrimeTest;

	i64 rng(i64 x, i64 offset, i64 mod)
	{
		return (modularMul(x, x, mod) + offset + mod) % mod;
	}

	i64 pollard_rho(i64 n)
	{
		if(n == 1)
			return 1;
		if((n & 1) == 0)
			return 2;

		i64 x, y, offset, d;
		x = y = (1LL * getRand() % (n - 2)) + 2;
		offset = (1LL * getRand() % (n - 1)) + 1;
		d = 1;

		while(d == 1)
		{
			x = rng(x, offset, n);
			y = rng(rng(y, offset, n), offset, n);
			d = __gcd(templateAbs(x - y), n);
			if(d == n)
				return n;
		}
		return d;
	}
}

void getAllFactors(i64 n, vector<i64> & fac)
{
	if(MR_PrimeTest::isPrime(n))
		return fac.push_back(n), (void) NULL;
	i64 p = n;
	while(p >= n)
		p = pollar_rho::pollard_rho(n);
	getAllFactors(p, fac);
	getAllFactors(n / p, fac);
}

int main()
{
	int T;
	scanf("%d", &T);

	while (T--)
	{
		i64 N;
		scanf("%lld", &N);
		if (MR_PrimeTest::isPrime(N))
			printf("Prime\n");
		else
		{
			vector<i64> fac;
			fprintf(stderr, "Not a prime\n");
			getAllFactors(N, fac);
			printf("%lld\n", *min_element(fac.begin(), fac.end()));
		}
	}

	return 0;
}
