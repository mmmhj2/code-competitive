// Codeforces792E Colored Balls
#include <bits/stdc++.h>
using namespace std;

typedef long long i64;
const int MAXN = 500 + 10;

i64 ans = 0x7F7F7F7F7F7F7F7F;
int N, a[MAXN];

bool check(int cur, i64 & cnt)
{
	if (cur <= 0)
		return false;
	cnt = 0;

	for (int i = 1; i <= N; i++)
		if (a[i] % cur <= a[i] / cur)
			cnt += 1LL * ceil(a[i] * 1.0 / (cur + 1));
		else
			return false;
	return true;
}

int main()
{
	ios::sync_with_stdio(false), cin.tie(nullptr);

	cin >> N;
	for (int i = 1; i <= N; i++)
		cin >> a[i];

	sort(a + 1, a + N + 1);
	i64 cnt = 0;
	int sq = (int) sqrt(a[1]) + 1;

	for (int i = 1; i <= sq; i++)
	{
		int cur = a[1] / i;
		if (check(cur, cnt))
			ans = min(ans, cnt);
		if (a[1] % i == 0)
			if (check(cur - 1, cnt))
				ans = min(ans, cnt);

		if (ans < 0x7F7F7F7F7F7F7F7F)
			break;
	}

	for (int i = sq + 1; i; i--)
	{
		if (check(i, cnt))
			ans = min(ans, cnt);
		if (ans < 0x7F7F7F7F7F7F7F7F)
			break;
	}

	cout << ans << endl;

	return 0;
}
