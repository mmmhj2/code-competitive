#include <bits/stdc++.h>
using namespace std;
typedef long long i64;

int n, ans;
i64 a[100010], b[100010];

map<i64, int> mp;

i64 square(i64 x)
{
	return x * x;
}

i64 clearCubicFactor(i64 x)
{
	for (i64 i = 2; i * i * i <= x; i++)
		while (x % (i * i * i) == 0)
			x /= (i * i * i);
	return x;
}

int main()
{
	scanf("%d", &n);
	for (int i = 1; i <= n; i++)
	{
		i64 x, y = 1;
		scanf("%lld", &x);

		x = clearCubicFactor(x);
		mp[x]++;
		a[i] = x;

		for (i64 j = 2; j * j * j <= x; j++)
			if (x % j == 0)
			{
				y *= (x % (j * j) == 0) ? j : j * j;
				while (x % j == 0)
					x /= j;
			}

		if (square((i64) sqrt(x)) == x)
			y *= (i64) sqrt(x);
		else
			y *= x * x;
		b[i] = y;
	}
	if (mp[1])
		ans++, mp[1] = 0;
	for (int i = 1; i <= n; i++)
		ans += max(mp[a[i]], mp[b[i]]), mp[a[i]] = mp[b[i]] = 0;
	printf("%d", ans);
	return 0;
}
