#include <algorithm>
#include <iterator>
#include <iostream>
#include <cstring>
#include <cstdio>
#include <vector>
#include <stack>
#define REDIRECT(x) freopen(x".in", "r", stdin), freopen(x".out", "w", stdout)
#define CLOSEALL() fclose(stdin), fclose(stdout)
using namespace std;
typedef long long i64;
const int MAXN = 1e5 + 10;
const int MAXQ = 1e5 + 10;

int N, Q;

int monoTop;
i64 monoStk[MAXN], tmp[MAXN], ans[MAXN];

void solve(i64 query, i64 delta)
{
	int index = lower_bound(monoStk + 1, monoStk + monoTop + 1, query) - monoStk - 1;
	if(index <= 0)
		ans[1] += delta, ans[query + 1] -= delta;
	else
		tmp[index] += delta * (query / monoStk[index]),
		solve(query % monoStk[index], delta);
}

int main()
{
	//REDIRECT("seq");

	scanf("%d%d", &N, &Q);
	monoStk[++monoTop] = N;
	for(int i = 1; i <= Q; i++)
	{
		i64 t;
		scanf("%lld", &t);

		while(monoTop && t < monoStk[monoTop])
			monoTop--;
		monoStk[++monoTop] = t;
	}

	tmp[monoTop] = 1;
	for(int i = monoTop; i > 0; i--)
		solve(monoStk[i], tmp[i]);
	for(int i = 1; i <= N; i++)
		ans[i] += ans[i-1], printf("%lld\n", ans[i]);

	CLOSEALL();
	return 0;
}
