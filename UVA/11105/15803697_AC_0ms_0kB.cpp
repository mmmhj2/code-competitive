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

const int MAXN = 250000 + 10;

int prefixSum[MAXN * 4 + 1];
bool notPrime[MAXN];
vector<int> primeList;

void linearSieve()
{
	for (int i = 1; i < MAXN; i++)
	{
		if (!notPrime[i])
			primeList.push_back(i);

		for (auto prime : primeList)
		{
			i64 current = 4LL * prime * i + prime + i;
			if (current >= MAXN)
				break;
			notPrime[current] = true;

			if ((i - prime) % (4 * prime + 1) == 0)
				break;
		}
	}

	for (auto prime1 : primeList)
		for (auto prime2 : primeList)
		{
			i64 current = 4LL * prime1 * prime2 + prime1 + prime2;
			if(current >= MAXN)
				break;

			prefixSum[current * 4 + 1] = 1;
		}

	for(int i = 1; i < MAXN * 4 + 1; i++)
		prefixSum[i] += prefixSum[i-1];
}

int main()
{
	linearSieve();

	int H;
	while (cin >> H && H)
	{
		cout << H << " " << prefixSum[H] << endl ;
	}

	return 0;
}
