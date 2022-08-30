#include <algorithm>
#include <iostream>
#include <iomanip>
#include <cassert>
#include <vector>
#include <cmath>
using namespace std;

#define DEBUGTRIGGER (cerr << "Triggered at [" << __PRETTY_FUNCTION__ << "]:(" << __LINE__ << ")" << endl)

typedef long long i64;
typedef unsigned long long u64;

const int MAXN = 36000;		// SQRT(1e9)

bool notPrime[MAXN];
vector<int> primeList;

void linearSieve()
{
	for (int i = 2; i < MAXN; i++)
	{
		if (!notPrime[i])
			primeList.push_back(i);

		for (auto j : primeList)
		{
			if (i * j >= MAXN)
				break;
			notPrime[i * j] = true;

			if (i % j == 0)
				break;
		}
	}
}

int defactorize(int x)
{
	int ret = 1;

	for(vector<int>::iterator itr = primeList.begin(); itr != primeList.end() && *itr <= x; ++itr)
	{
		const int & prime = *itr;
		if(x % prime)
			continue;
		int sum = 0;
		while(x % prime == 0)
			x /= prime, sum++;
		ret *= (1 + sum);
	}

	if(x > 1)
		ret *= 2;

	return (ret);
}

int main()
{
	linearSieve();
	int kase;
	int L, U, P, D;

	scanf("%d", &kase);

	for(int caseCnt = 1; caseCnt <= kase; caseCnt++)
	{
		P = 0;
		D = 0;
		scanf("%d%d", &L, &U);

		int res;
		for(int i = L; i <= U; i++)
		{
			res = defactorize(i);
			if(res > D)
				P = i, D = res;
		}

		printf("Between %d and %d, %d has a maximum of %d divisors.\n", L, U, P, D);

	}

	return 0;
}
