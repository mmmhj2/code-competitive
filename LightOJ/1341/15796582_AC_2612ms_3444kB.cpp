#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

#define DEBUGTRIGGER (cerr << "Triggered at [" << __PRETTY_FUNCTION__ << "]:(" << __LINE__ << ")" << endl)

const int MAXN = 1000000 + 10;		// Square root of (10^12)

typedef long long i64;
typedef unsigned long long u64;

bool notPrime[MAXN];
vector <int> primeList;

void LinearSieve()
{
	for (int i = 2; i < MAXN; i++)
	{
		if (!notPrime[i])
			primeList.push_back(i);
		for (vector<int>::iterator itr = primeList.begin();
				itr != primeList.end(); ++itr)
		{
			const int & j = *itr;
			if (i * j >= MAXN)
				break;

			notPrime[i * j] = true;

			if (i % j == 0)
				break;
		}
	}
}

i64 CalcSigma(i64 x)		// Calculate σ0(N) using FTA
{
	if (x == 0)
		return 0LL;

	i64 sigma = 1;
	for (vector<int>::iterator itr = primeList.begin();
			itr != primeList.end() && *itr <= x; ++itr)
	{
		//DEBUGTRIGGER;
		//cerr << *itr << " " << x << endl ;
		const int & j = *itr;
		if(x % j)
			continue;

		i64 tsum = 0;
		while(x % j == 0)
			x /= j, tsum++;

		sigma *= (tsum + 1);
	}

	if(x > 1)
		sigma *= 2;
	//cerr << sigma << endl ;
	return sigma;
}

int main()
{
	LinearSieve();

	i64 a, b;
	int K;

	cin >> K ;
	for(int CaseCnt = 1; CaseCnt <= K; CaseCnt++)
	{
		i64 ans = 0;
		cin >> a >> b ;

		if(b < sqrt(a))
		{
			for(int i = 1; i < b; i++)
				if(a % i == 0)
					ans--;

			ans += CalcSigma(a) / 2;
		}

		cout << "Case " << CaseCnt << ": " << ans << endl ;
	}
}
