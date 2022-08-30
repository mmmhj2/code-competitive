// BZOJ 2467 生成树
#include <iostream>
using namespace std;

template <typename T = long long>
T modularExp(T base, T exp, const T & MOD)
{
	T ans = 1;
	while(exp > 0)
	{
		if(exp % 2)
			ans = ans * base % MOD ;
		base = base * base % MOD ;
		exp = exp >> 1;
	}
	return ans;
}

int main()
{
	int T;
	scanf("%d", &T);

	while(T--)
	{
		int N;
		scanf("%d", &N);
		printf("%lld\n", (((modularExp<>(5LL, 1LL * (N - 1), 2007LL) * 4) % 2007) * N) % 2007);
	}

	return 0;
}
