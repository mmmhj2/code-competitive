#include <algorithm>
#include <cstdlib>
#include <cstring>
#include <cstdio>

#define REDIRECT(x) freopen(x".in", "r", stdin), freopen(x".out", "w", stdout)
#define CLOSEALL() fclose(stdin), fclose(stdout)

typedef long long i64;
const int MAXN = 2000 + 10;

i64 answer;
i64 N, x;
i64 a[MAXN];
i64 min[MAXN], pos[MAXN];

int main()
{
	//REDIRECT("slime");

	scanf("%lld%lld", &N, &x);
	for(int i = 1; i <= N; i++)
		scanf("%lld", &a[i]), min[i] = a[i], pos[i] = i, answer += a[i];

	for(int i = 1; i <= N; i++)
	{
		i64 tans(0);
		for(int j = 1; j <= N; j++)
		{
			pos[j] --;
			if(pos[j] <= 0)
				pos[j] = N;

			min[j] = std::min(min[j], a[pos[j]]);
			tans += min[j];
		}
		answer = std::min(answer, tans + x * i);
	}


	printf("%lld\n", answer);

	CLOSEALL();
	return 0;
}
