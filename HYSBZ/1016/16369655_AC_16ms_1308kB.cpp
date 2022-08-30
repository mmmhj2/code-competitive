#include <algorithm>
#include <iostream>
using namespace std;

const int MOD = 31011;
const int MAXM = 1000 + 10;

struct edge
{
	int u, v, w;

	bool operator < (const edge & rhs) const
	{
		return w < rhs.w;
	}

}E[MAXM];

struct data
{
	int L, R, v;
}Q[MAXM];
int qCnt;

namespace disjointSet
{
int fa[100 + 10];

void init(int N)
{
	for(int i = 1; i <= N; i++)
		fa[i] = i;
}
int find(int x)
{
	if(x == fa[x])
		return x;
	return find(fa[x]);
}
};

int N, M;
int sum, tot, ans(1);
void DFS(int cur, int now, int cnt)
{
	using namespace disjointSet;
	if(now == Q[cur].R + 1)
	{
		sum += (cnt == Q[cur].v);
		return;
	}
	int x = find(E[now].u), y = find(E[now].v);
	if(x != y)
	{
		fa[x] = y;
		DFS(cur, now + 1, cnt+1);
		fa[x] = x, fa[y] = y;
	}
	DFS(cur, now+1, cnt);
}

int main()
{
	using namespace disjointSet;
	ios::sync_with_stdio(false), cin.tie(NULL);

	cin >> N >> M ;
	init(N);
	for(int i = 1; i <= M; i++)
		cin >> E[i].u >> E[i].v >> E[i].w ;
	sort(&E[1], &E[M + 1]);

	for(int i = 1; i <= M; i++)
	{
//		fprintf(stderr, "%d %d %d\n", E[i].u, E[i].v, E[i].w);
		if(E[i].w != E[i-1].w)
			Q[++qCnt].L = i, Q[qCnt-1].R = i-1;
		int x = find(E[i].u), y = find(E[i].v);
		if(x != y)
			fa[x] = y, Q[qCnt].v++, tot++;
	}
	Q[qCnt].R = M;

//	for(int i = 1; i <= qCnt; i++)
//		fprintf(stderr, "%d %d %d\n", Q[i].L, Q[i].R, Q[i].v);

	if(tot != N - 1)
		return cout << 0 << endl, 0;

	init(N);
	for(int i = 1; i <= qCnt; i++)
	{
		sum = 0;
		DFS(i, Q[i].L, 0);
		ans = (1LL * ans * sum) % MOD ;
		for(int k = Q[i].L; k <= Q[i].R; k++)
		{
			int x = find(E[k].u), y = find(E[k].v);
			if(x != y)
				fa[x] = y;
		}
	}

	cout << ans << endl ;
	return 0;
}
