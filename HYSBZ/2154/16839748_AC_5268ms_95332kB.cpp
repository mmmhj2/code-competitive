#include <bits/stdc++.h>
using namespace std;
typedef long long i64;
const int MAXN = 1e7 + 10;
const int MOD = 20101009;

bool notPrime[MAXN];

int N, M;
int mu[MAXN], prefix[MAXN];

typedef vector<int>::iterator lstItr;
vector<int> prime;

void linearSieve(int lim)
{
	notPrime[1] = true;
	mu[1] = prefix[1] = 1;
	for (int i = 2; i <= lim; i++)
	{
		if (!notPrime[i])
			prime.push_back(i), mu[i] = -1;
		for (lstItr itr = prime.begin(); itr != prime.end(); ++itr)
		{
			int j = *itr;
			if (i * j > lim)
				break;
			notPrime[i * j] = true;

			if (i % j == 0)
			{
				mu[i * j] = 0;
				break;
			}

			mu[i * j] = mu[i] * mu[j];
		}
		prefix[i] = (prefix[i - 1] + 1LL * i * i * mu[i] % MOD) % MOD;
	}
}

inline i64 _getSum(int x, int y)
{
	return (1ll * x * (x + 1) / 2 % MOD * (1ll * y * (y + 1) / 2 % MOD) % MOD);
}

inline i64 getSum(int x, int y)
{
	int lim = min(x, y);
	i64 ret = 0;
	for (int i = 1, last = 0; i <= lim; i = last + 1)
		last = min(x / (x / i), y / (y / i)), ret = (ret
				+ (((prefix[last] - prefix[i - 1]) % MOD)
						* _getSum(x / i, y / i)) % MOD + MOD) % MOD;
	return ret;
}

int main()
{
	scanf("%d%d", &N, &M);
	int lim = min(N, M);
	linearSieve(lim);

	i64 ans = 0;

	for (int i = 1, last = 0; i <= lim; i = last + 1)
	{
		last = min(N / (N / i), M / (M / i)), ans = (ans
				+ (1LL * (i + last) * (last - i + 1) / 2) % MOD
						* getSum(N / i, M / i) % MOD) % MOD;
	}

	printf("%lld\n", ans);

	return 0;
}
