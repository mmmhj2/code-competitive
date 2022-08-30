// Codeforces893D Credit Card
#include <bits/stdc++.h>
using namespace std;

typedef long long i64;
const int MAXN = 1e5 + 10;

int ans;
i64 N, D;
i64 a[MAXN];
i64 suffix[MAXN], sufMin[MAXN];

int main()
{
	i64 cur = 0, sum = 0;
	cin >> N >> D;
	for (int i = 1; i <= N; i++)
		cin >> a[i];
	suffix[N + 1] = sufMin[N + 1] = 0;
	for (int i = N; i >= 1; i--)
		suffix[i] = suffix[i + 1] + a[i], sufMin[i] = min(sufMin[i + 1],
				suffix[i]);
	int j, k;
	for (int i = 0; i <= N; i = j)
	{
		for (j = i + 1; j <= N; j++)
			if (!a[j])
				break;
		for (sum = cur, k = i + 1; k < j; k++)
		{
			sum += a[k];
			if (sum > D)
				return puts("-1"), 0;
		}

		if (sum < 0)
		{
			cur = max(0LL, min(D - suffix[j + 1] + sufMin[j + 1], D));
			if (j != N + 1)
				ans++;
		}
		else
			cur = sum;
	}

	cout << ans << endl;

	return 0;
}
