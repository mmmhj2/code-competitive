#include <iostream>
#include <iomanip>
#include <cmath>
using namespace std;

const int MAXN = 2e5 + 10;

typedef long double ldouble;

ldouble FactLog[MAXN * 2];

void prepare()
{
	FactLog[0] = 0;
	for (int i = 1; i < MAXN * 2; i++)
		FactLog[i] = FactLog[i - 1] + log(i);
}

ldouble logC(int n, int m)
{
	return FactLog[n] - FactLog[n - m] - FactLog[m];
}

int main()
{
	prepare();
	//cerr << FactLog[1] << FactLog[2] << FactLog[3] << endl ;

	int N, kase;
	ldouble p;

	while (cin >> N >> p)
	{
		//cerr << p << endl ;
		ldouble answer = 0.0;

		for (int i = 1; i <= N; i++)
		{
			ldouble C = logC(2 * N - i, N), v1 = C + (N + 1) * log(p)
					+ (N - i) * log(1 - p), v2 = C
					+ (N + 1) * log(1 - p) + (N - i) * log(p);
			//cerr << v1 << " " << v2 << " " << i * (exp(v1) + exp(v2)) << endl ;
			answer += i * (exp(v1) + exp(v2));
		}

		cout << "Case " << ++kase << ": " << fixed << setprecision(6) << answer << endl ;

	}

	return 0;
}
