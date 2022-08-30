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

const int INF = 200000000;
const int MAXN = 15000 + 10;

bool notPrime[MAXN];
vector<int> primeList;

void linearSieve()
{
	for(int i = 2; i < MAXN; i++)
	{
		if(!notPrime[i])
			primeList.push_back(i);

		for(vector<int>::iterator itr = primeList.begin(); itr != primeList.end(); ++itr)
		{
			const int & prime = *itr;
			if(1LL * prime * i >= MAXN)
				break;

			notPrime[i * prime] = true;

			if(i % prime == 0)
				break;
		}
	}
}

bool vist[MAXN];
int answer;
vector <int> selectedPrime;

bool judge(int x)
{
	// Check if the remainder is not a prime
	for(int prime : primeList)
	{
		if(prime * prime > x)
			break;
		if(x % prime == 0)
			return false;
	}

	// Check if the remainder is already selected
	for(unsigned i = 0; i < selectedPrime.size(); i++)
		if(selectedPrime[i] == x && vist[i])
			return false;

	return true;
}

void defactorize(int x)
{
	for(int prime : primeList)
	{
		if((prime-1) * (prime-1) > x)
			break;
		if(x % (prime - 1) == 0)
			selectedPrime.push_back(prime);
	}
}

void DFS(unsigned pos, int remainder, int n)
{
	if(pos >= selectedPrime.size())
	{
		if(remainder == 1)					// All primes are selected
			answer = min(answer, n);
		else if(judge(remainder + 1))		// Only one component remains
			answer = min(answer, n * (remainder + 1));
		return;
	}

	DFS(pos + 1, remainder, n);				// Do nothing
	if(remainder % (selectedPrime[pos] - 1))
		return;

	// Choose this prime
	vist[pos] = true;

	remainder /= (selectedPrime[pos] - 1);
	n *= selectedPrime[pos];
	DFS(pos + 1, remainder, n);

	while(remainder % selectedPrime[pos] == 0)
	{
		remainder /= selectedPrime[pos];
		n *= selectedPrime[pos];
		DFS(pos + 1, remainder, n);
	}

	vist[pos] = false;
}

int main()
{
	linearSieve();

	int N, kase = 0;
	while(scanf("%d", &N) != EOF && N)
	{
		answer = INF;
		selectedPrime.clear();

		defactorize(N);
		DFS(0, N, 1);

		printf("Case %d: %d %d\n", ++kase, N, answer);
		fflush(stdout);
	}

	return 0;
}
