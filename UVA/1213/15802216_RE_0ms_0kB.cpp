#include <algorithm>
#include <iostream>
#include <iomanip>
#include <vector>
#include <cmath>
using namespace std;

#define DEBUGTRIGGER (cerr << "Triggered at [" << __PRETTY_FUNCTION__ << "]:(" << __LINE__ << ")" << endl)

typedef long long i64;
typedef unsigned long long u64;

const int MAXN = 1200;

int N;
i64 dp[MAXN][MAXN];

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

void calcAns()
{
	dp[0][0] = 1;

	for(int prime : primeList)
		for(int n = MAXN; n >= prime; n--)
			for(int k = 1; k <= 14; k++)
				dp[n][k] += dp[n - prime][k - 1];
}

int main()
{
	linearSieve();
	calcAns();

	ios::sync_with_stdio(false);
	cin.tie(NULL);

	int t, k;
	while (cin >> t >> k && t && k)
	{
		cout << dp[t][k] << endl ;
	}

	return 0;
}
