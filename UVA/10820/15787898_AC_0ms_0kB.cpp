#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

typedef long long i64;
typedef unsigned long long u64;

const int MAXN = 50000 + 5;

int phi[MAXN];
int ans[MAXN];

vector <int> primeList;
bool notPrime[MAXN];

void linearSieve()
{
	for(int i = 2; i < MAXN; i++)
	{
		if(!notPrime[i])
			phi[i] = i - 1,
			primeList.push_back(i);

		for(vector<int>::iterator itr = primeList.begin(); itr != primeList.end(); ++itr)
		{
			const int & j = *itr;
			if(i * j >= MAXN)
				break;
			notPrime[i * j] = true;

			if(i % j == 0)
			{
				phi[i * j] = phi[i] * j;
				break;
			}

			phi[i * j] = phi[i] * (j - 1);
		}
	}

	for(int i = 1; i < MAXN; i++)
		ans[i] = ans[i - 1] + phi[i];
}

int main()
{
	ios::sync_with_stdio(false);
	linearSieve();

	int N;
	while(cin >> N)
	{
		if(!N)
			break;

		cout << 2 * ans[N] + 1 << endl ;
	}
}
