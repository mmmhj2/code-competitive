#include <algorithm>
#include <cstdio>

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-result"		// scanf -> unused return value

#define REDIRECT(x) freopen(x".in", "r", stdin), freopen(x".out", "w", stdout)
#define CLOSEALL() fclose(stdin), fclose(stdout)

const int MAXN = 1e5 + 10;
typedef long long i64;

i64 K;
i64 N, M;
i64 answer[MAXN];
i64 a[MAXN], idx[MAXN];

i64 stk[MAXN], top;

bool vis[MAXN];

int main()
{
	//REDIRECT("rabbit");
	
	scanf("%lld", &N);
	for(int i = 1; i <= N; i++)
		scanf("%lld", &a[i]), idx[i] = i;
		
	for(int i = N; i >= 1; i--)
		a[i] -= a[i-1];
		
	scanf("%lld%lld", &M, &K);
	for(int i = 1;i <= M; i++)
	{
		int t;
		scanf("%d", &t);
		std::swap(idx[t], idx[t + 1]);
	}
	
	for(int i = 1; i <= N; i++)
		if(!vis[i])
		{
			int cur = i;
			top = 0;

			while(!vis[cur])
				stk[++top] = cur, vis[cur] = true, cur = idx[cur];

			for(int k = 1; k <= top; k++)
				answer[stk[k]] = a[stk[(K + k - 1) % top + 1]];
		}

	for(int i = 1; i <= N; i++)
		answer[i] += answer[i-1],
		printf("%lld\n", answer[i]);

	CLOSEALL();
	return 0;
}

#pragma GCC diagnostic pop
