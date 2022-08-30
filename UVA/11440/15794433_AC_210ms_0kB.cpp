#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

const int MOD = 100000007;
const int MAX_PRIME = 10000010;

typedef long long i64;
typedef unsigned long long u64;

int phiFact[MAX_PRIME];
bool notPrime[MAX_PRIME];
vector <int> prime;

void LinearSieve()
{
	for(int i = 2; i < MAX_PRIME; i++)
	{
		if(!notPrime[i])
			prime.push_back(i);
		for(vector<int>::iterator itr = prime.begin(); itr != prime.end(); ++itr)
		{
			const int & j = *itr;
			if(i * j >= MAX_PRIME)
				break;
			notPrime[i * j] = true;
			if(i % j == 0)
				break;

		}
	}

	// Calculate phiFact
	phiFact[1] = phiFact[2] = 1;
	for(int i = 3; i < MAX_PRIME; i++)
		phiFact[i] = 1LL * phiFact[i-1] * (!notPrime[i] ? i-1 : i) % MOD;
}

int N, M;
int main()
{
	LinearSieve();
	while(cin >> N >> M)
	{
		if(!N)
			break;
		int answer = phiFact[M];
		// Multiply (N-M)!
		for(int i = M + 1; i <= N; i++)
			answer = 1LL * answer * i % MOD;

		cout << (answer - phiFact[1] + MOD) % MOD << endl ;
	}
}
