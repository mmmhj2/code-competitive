#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

typedef long long i64;
typedef unsigned long long u64;

i64 ArithmeticSum(int a, int d, int n)
{
	return 1LL * (2 * a - d * n) * (n + 1) / 2;
}

int N,K;
int main()
{
	ios::sync_with_stdio(false);

	while(cin >> N >> K)
	{
		int cnt, p, q;
		i64 ans = 0;
		for(int i = 1; i <= N; i += cnt + 1)
		{
			p = K / i, q = K % i, cnt = N - i;

			if(p > 0)
				cnt = min(cnt, q / p);
			ans += ArithmeticSum(q, p, cnt);
		}

		cout << ans << endl ;
	}
}
