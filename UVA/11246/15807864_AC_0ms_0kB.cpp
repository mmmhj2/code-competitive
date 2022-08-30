#include <algorithm>
#include <iostream>
#include <iomanip>
#include <cstring>
#include <vector>
#include <cmath>
#include <queue>

#define printfDbg(...) fprintf(stderr, __VA_ARGS__), fflush(stderr)

using namespace std;
typedef long long i64;

const int MAXN = 1000000000;

int N, K;


int main()
{
	int kase;
	cin >> kase;
	while(kase--)
	{
		int signum = 1;
		i64 ans = 0;
		cin >> N >> K;

		while(N)
		{
			ans += signum * N;
			N /= K;
			signum *= -1;
		}

		cout << ans << endl;
	}
}

