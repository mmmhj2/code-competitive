#include <algorithm>
#include <iostream>
#include <iomanip>
#include <vector>
#include <cmath>
using namespace std;

#define DEBUGTRIGGER (cerr << "Triggered at [" << __PRETTY_FUNCTION__ << "]:(" << __LINE__ << ")" << endl)

typedef long long i64;
typedef unsigned long long u64;

const int MAXN = 1500000;

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

int main()
{
	linearSieve();

	ios::sync_with_stdio(false);
	cin.tie(NULL);

	int t;
	while (cin >> t && t)
	{
		if (!notPrime[t])
			cout << 0 << endl;
		else
			cout
					<< (*upper_bound(primeList.begin(), primeList.end(), t)
							- (*(lower_bound(primeList.begin(), primeList.end(),
									t) - 1))) << endl;
	}

	return 0;
}
