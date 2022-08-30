#include <algorithm>
#include <iostream>
#include <iomanip>
#include <vector>
#include <cmath>
using namespace std;

int a, b, ans;
bool check(int mid)
{
	int x = (mid + 1) / 2;
	int y = mid + 1 - x;
	/*
	 return (2 * a * (mid + 3) + b * (x * y + mid + 2)
	 <= 3 * a * (x * y + mid + 2));
	 */
	return (2 * a * (mid + 3) <= (3 * a - b) * (x * y + mid + 2));
}

int main()
{
	int kase, nkase = 0;
	cin >> kase;

	while (kase--)
	{
		ans = 0;
		cin >> a >> b;
		if (a >= b)
			ans = 1;
		else if (a * 3 <= b)
			ans = -1;
		else
		{
			int L = 0, R = 10001;

			while (L + 1 < R)
			{
				int mid = (L + R) >> 1;
				//cerr << "Checking " << mid << endl;
				if (check(mid))
					R = mid;
				else
					L = mid;
			}

			ans = L;

			if (ans < 0 || ans > 10000)
				ans = -1;
			else
				ans++;
		}

		cout << "Case " << ++nkase << ": " << ans << endl;
	}
}

