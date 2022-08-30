#include <algorithm>
#include <iostream>
#include <iomanip>
#include <vector>
#include <cmath>
using namespace std;

#define DEBUGTRIGGER (cerr << "Triggered at [" << __PRETTY_FUNCTION__ << "]:(" << __LINE__ << ")" << endl)

typedef long long i64;
typedef unsigned long long u64;

const int MAXN = 1000000 + 10;

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

	int kase;
	cin >> kase;

	while(kase--)
	{
		i64 L, R, ans = 0;
		cin >> L >> R ;

		for(int prime : primeList)
		{
			for(i64 i = 1LL * prime * prime; i <= R; i *= prime)
				if(i >= L)
					ans++;
		}

		cout << ans << endl ;
	}

	return 0;
}
