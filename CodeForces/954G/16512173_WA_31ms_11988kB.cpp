// Codeforces954G Castle Defense
#include <bits/stdc++.h>
using namespace std;

typedef long long i64;
const int MAXN = 500000 + 10;

i64 N, R, K;
i64 a[MAXN], b[MAXN];
i64 prefix[MAXN];

bool check(i64 mid)
{
	int lft = K, delta = 0;
	memset(b, 0x00, sizeof b);

	for(int i = 1; i <= N; i++)
	{
		delta += b[i];
		i64 t1 = prefix[min(i + R, N)] - prefix[max(i - R - 1, 0LL)] + delta;
		if(t1 < mid)
		{
			i64 dlt = mid - t1;
			if(dlt > lft)
				return false;
			lft -= dlt, delta += dlt;
			b[i + 2 * R + 1] -= dlt;
		}
	}
	return true;
}

int main()
{
	ios::sync_with_stdio(false), cin.tie(nullptr);

	i64 LL = 0, RR = 0x7F7F7F7F7F7F7F7F;

	cin >> N >> R >> K;
	for (int i = 1; i <= N; i++)
		cin >> a[i], prefix[i] = prefix[i-1] + a[i];

	while (LL < RR)
	{
		i64 mid = (LL + RR) >> 1;
		if (check(mid))
			LL = mid + 1;
		else
			RR = mid;
	}

	cout << max(0LL, LL - 1) << endl;

	return 0;
}
