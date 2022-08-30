#include <algorithm>
#include <cstring>
#include <cstdio>

#define REDIRECT(x) freopen(x".in", "r", stdin), freopen(x".out", "w", stdout)
#define CLOSEALL() fclose(stdin), fclose(stdout)

using namespace std;
typedef long long i64;

i64 N, K;

i64 simulate(i64 x, i64 y)
{
	if(y == 0)
		return (-x);
	return simulate(y, x % y) + 2 * (x / y) * y;
}

int main()
{
	//REDIRECT("light");

	scanf("%lld%lld", &N, &K);
	printf("%lld\n", simulate(max(K, N - K), min(K, N - K)) + N);

	CLOSEALL();
	return 0;
}
