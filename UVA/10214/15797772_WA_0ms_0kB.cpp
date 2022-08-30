#include <iostream>
#include <iomanip>
#include <vector>
#include <cmath>
using namespace std;

#define DEBUGTRIGGER (cerr << "Triggered at [" << __PRETTY_FUNCTION__ << "]:(" << __LINE__ << ")" << endl)

typedef long long i64;
typedef unsigned long long u64;

int getPhi(int x)
{
	int phi = x;
	for(int i = 2; i * i <= x; i++)
	{
		if(x % i == 0)
		{
			while(x % i == 0)
				x /= i;
			phi = phi / i * (i - 1);
		}
	}

	if(x > 1)
		phi = phi / x * (x - 1);
	return phi;
}

int GCD(int x, int y)
{
	if(!y)
		return x;
	return GCD(y, x % y);
}

int a, b;

i64 getAnswer()
{
	i64 ret = 0;

	for(int i = 1; i <= a; i++)
	{
		int t = b / i;
		ret += 1LL * getPhi(i) * t;

		for(int j = t * i + 1; j <= b; j++)
			if(GCD(i, j) == 1)
				ret++;
	}
	return ret * 4 + 4;
}

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(NULL);

	while(cin >> a >> b)
	{
		if(a == 0 && b == 0)
			break;

		i64 allsum = (2 * a + 1) * (2 * b + 1) - 1 ;
		cout << fixed << setprecision(7) << 1.0 * getAnswer() / allsum << endl ;
	}

	return 0;
}
