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
const int PRIMETABLE[] =
{ 2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47};

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

}

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(NULL);

	int k, ans = 0;
	while (cin >> k)
	{
		ans = 0;
		while (k--)
		{
			int totest;
			cin >> totest;
			if (numberTheory::MillerRabinTest(totest, 12))
				ans++;
		}
		cout << ans << endl;
	}
}

