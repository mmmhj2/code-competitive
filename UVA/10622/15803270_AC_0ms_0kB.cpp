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

const int MAXN = 67000;	// 65535

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

int GCD(int x, int y)
{
	if (!y)
		return (x);
	return (GCD(y, x % y));
}

int main()
{
	linearSieve();

	ios::sync_with_stdio(false);
	cin.tie(NULL);

	int input;

	while (cin >> input && input)
	{
		int ans = 0;
		bool isNegative = false;
		if (input < 0)
			isNegative = true, input *= -1;

		//cerr << input << " " ;

		for (vector<int>::iterator itr = primeList.begin();
				itr != primeList.end() && input > 1; ++itr)
		{
			if(input % (*itr) == 0)
			{
				int cnt = 0;
				while(input % (*itr) == 0)
					cnt++, input /= (*itr);
				ans = GCD(ans, cnt);
			}
		}

		if(input > 1)
			ans = GCD(ans, 1);
		//cerr << ans << " " ;
		if(isNegative)
			while(ans % 2 == 0)
				ans >>= 1;

		cout << ans << endl ;
	}

	return 0;
}
