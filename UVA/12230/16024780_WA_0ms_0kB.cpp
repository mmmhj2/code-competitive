#include <iostream>
#include <iomanip>
using namespace std;

int main()
{
	int N, D, kase;

	while(cin >> N >> D && D)
	{
		double ans = 0.00, p, L, v;
		for(int i = 1; i <= N; i++)
		{
			cin >> p >> L >> v ;
			ans += 2.0 * L / v, D -= L;
		}

		cout << "Case " << ++kase << ": " << fixed << setprecision(3) << ans << endl << endl ;
	}

	return 0;
}
