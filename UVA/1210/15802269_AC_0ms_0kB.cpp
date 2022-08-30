#include <algorithm>
#include <iostream>
#include <iomanip>
#include <vector>
#include <cmath>
using namespace std;

#define DEBUGTRIGGER (cerr << "Triggered at [" << __PRETTY_FUNCTION__ << "]:(" << __LINE__ << ")" << endl)

typedef long long i64;
typedef unsigned long long u64;

const int MAXN = 10000 + 50;

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

int calcAns(int target)
{
	int ans = 0;
	unsigned l = 0, r = 0;
	int tmp = 0;
	while (true)
	{
		while (tmp < target && r < primeList.size())
		{
			tmp += primeList[r++];
		}
		if (tmp < target)
			break;
		if (tmp == target)
			ans++;
		tmp -= primeList[l++];
	}
	return ans;
}

int main()
{
	linearSieve();

	ios::sync_with_stdio(false);
	cin.tie(NULL);

	int t;
	while (cin >> t&& t)
	{
		cout << calcAns(t) << endl ;
	}

	return 0;
}
