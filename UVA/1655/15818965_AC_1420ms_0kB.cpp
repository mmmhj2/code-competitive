#include <algorithm>
#include <iostream>
#include <iomanip>
#include <cstring>
#include <vector>
#include <cmath>
#include <queue>

#define printfDbg(...) fprintf(stderr, __VA_ARGS__), fflush(stderr)

using namespace std;
typedef long long i64;

namespace numberTheory
{
// Prime table
const int CONST_DELTA = 47;
const int PRNG_MODULAR = 1048576;
const int PRIMETABLE[] =
{ 2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47};

// Calculate the absolute value
template<class T>
T abs(T x)
{
	if(x > 0)
		return (x);
	return (-x);
}

// Calculate base ^ exp % mod
template<class T>
T modularExponention(T base, T exp, T mod)
{
	T ans = 1;
	while (exp)
	{
		if (exp & 1)
			ans = ans * base % mod;
		base = base * base % mod;
		exp = exp >> 1;
	}
	return (ans);
}

// Calculate the greatest common divisor
template <class T>
T GCD(T a, T b)
{
	if(!b)
		return (a);
	return (GCD(b, a % b));
}

// Solve ax + by = GCD(a, b)
template<class T>
T exGCD(T a, T b, T & x, T & y)
{
	if (b == 0)
	{
		x = 1, y = 0;
		return (a);
	}
	int q = exGCD(b, a % b, y, x);
	y -= a / b * x;
	return (q);
}

// Solve ax = b (modular n)
template<class T>
void modularLinearEquation(T a, T b, T n, vector<T> & sol)
{
	int x, y, d;
	d = exGCD(a, b, x, y);

	if (b % d)
		return;

	int x0 = x * (b / d) % n;
	for (int i = 0; i < d; i++)
		sol.push_back((x0 + i * (n / d)) % n);
}

// Miller-Rabin witness function
template<class T>
bool witness(T d, T n, unsigned k)
{
	//T a = 2 + rand() % (n - 4);
	T a = PRIMETABLE[k];
	// Calculate a^d % n
	T x = modularExponention(a, d, n);

	if (x == 1 || x == n - 1)
		return (true);
	while (d != n - 1)
	{
		x = (x * x) % n;
		d = d * 2;
		if (x == 1)
			return (false);
		if (x == n - 1)
			return (true);
	}
	return (false);
}

// Miller-Rabin prime test
/// @param s the possibility of this test to go wrong is 2^(-s)
template<class T>
bool MillerRabinTest(T n, unsigned s)
{
	if (n <= 1 || n == 4)
		return (false);
	if (n == 2 || n == 3)
		return (true);
	T d = n - 1;
	while (d % 2 == 0)
		d /= 2;
	for (unsigned i = 0; i < s; i++)
	{
		if (!witness(d, n, i))
			return (false);
	}

	return (true);
}

//Pseudo-random function used by PollarRho
template <class T>
T PRNG(T x, T delta, T modular)
{
	return ((x * x % modular + delta) % modular);
}

// Pollard-Rho algorithm to find a factor of N
template <class T>
T PollarRho(T n)
{
	int d = (rand() * rand()) % n;
	int a, b;
	a = rand(), b = a;

	do
	{
		a = PRNG(a, d, n);
		b = PRNG(PRNG(b, d, n), d, n);
		int p = GCD(abs(a-b), n);
		if(p > 1)
			return (p);
	}while(b != a);
	return (0);
}

}

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(NULL);

	i64 N;
	int kase = 0;

	while(cin >> N)
	{
		i64 ans = 0;
		// Three congruent numbers
		for(i64 i = 1; i * i * i <= N; i++)
			ans ++;

		// Two Congruent numbers
		for(i64 i = 1; i * i <= N; i++)
		{
			i64 x = N / (i * i);
			if(x >= i)
				ans += (x - 1) * 3;
			else
				ans += x * 3;
		}

		// Three different numbers
		for(i64 i = 1; i * i * i <= N; i++)
			for(i64 j = i + 1; j <= N; j++)
			{
				i64 x = N / (i * j);
				if(x > j)
					ans += (x - j) * 6;
				else
					break;
			}

		cout << "Case " << ++kase << ": " << ans << endl ;
	}
}

