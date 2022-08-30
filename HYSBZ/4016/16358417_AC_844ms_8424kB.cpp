// BZOJ 4016 最短路径树问题
#include <algorithm>
#include <cstring>
#include <cstdio>
#include <queue>
using namespace std;

const int MAXN = 30000 + 10;

struct edge1
{
	int u, v, w;
	bool operator <(const edge1 & rhs) const
	{
		if (u == rhs.u)
			return v > rhs.v;
		return u < rhs.u;
	}
} E1[MAXN * 4];
struct edge2
{
	int nxt, to, d;
} E2[200000 + 10];

int allocCnt;
int head[MAXN], dist[MAXN];
int pre[MAXN], predist[MAXN];
int sz[MAXN], mxSz[MAXN], mnSz, root;
int w[MAXN], ans, mxDep, K, N, M;
int cnt, ct[MAXN * 10];
bool vist[MAXN];

inline void addEdge(int u, int v, int d)
{
	allocCnt++;
	E2[allocCnt].nxt = head[u];
	head[u] = allocCnt;
	E2[allocCnt].to = v, E2[allocCnt].d = d;
}

void SPFA()
{
	queue<int> Q;
	memset(dist, 0x7F, sizeof dist);
	Q.push(1), dist[1] = 0, vist[1] = true;

	while (!Q.empty())
	{
		int cur = Q.front();
		Q.pop(), vist[cur] = false;

		for (int i = head[cur]; i != 0; i = E2[i].nxt)
		{
			int to = E2[i].to;

			if (dist[to] > dist[cur] + E2[i].d)
			{
				pre[to] = cur;
				predist[to] = E2[i].d;
				dist[to] = dist[cur] + E2[i].d;

				if (!vist[to])
					vist[to] = true, Q.push(to);
			}
		}
	}
}

void getSz(int cur, int fa)
{
	sz[cur] = 1, mxSz[cur] = 0;

	for(int i = head[cur]; i != 0; i = E2[i].nxt)
	{
		int to = E2[i].to;
		if(to == fa || vist[to])
			continue;
		getSz(to, cur);
		sz[cur] += sz[to];
		mxSz[cur] = max(mxSz[cur], sz[to]);
	}
}

void getCentroid(int cur, int fa, int rt)
{
	mxSz[cur] = max(sz[rt] - sz[cur], mxSz[cur]);
	if(mxSz[cur] < mnSz)
		mnSz = mxSz[cur], root = cur;

	for(int i = head[cur]; i != 0; i = E2[i].nxt)
		if(E2[i].to != fa && !vist[E2[i].to])
			getCentroid(E2[i].to, cur, rt);
}

void getAnswer(int cur, int fa, int dis, int dep)
{
	const int index = K - dep - 1;
	if(ct[index] && w[index]+dis == ans)
		cnt += ct[index];
	else if(ct[index] && w[index] + dis > ans)
		ans = w[index] + dis, cnt = ct[index];
	mxDep = max(mxDep, dep);

	for(int i = head[cur]; i != 0; i = E2[i].nxt)
	{
		const int to = E2[i].to;
		if(to == fa || vist[to] || dep == K - 1)
			continue;
		getAnswer(to, cur, dis + E2[i].d, dep + 1);
	}

}

void update(int cur, int fa, int dis, int dep)
{
	if(dis > w[dep])
		w[dep] = dis, ct[dep] = 1;
	else if(dis == w[dep])
		ct[dep] ++;
	mxDep = max(mxDep, dep);

	for(int i = head[cur]; i != 0; i = E2[i].nxt)
	{
		const int to = E2[i].to;
		if(to == fa || vist[to] || dep == K - 1)
			continue;
		update(to, cur, dis + E2[i].d, dep + 1);
	}

}

void solve(int cur)
{
	mnSz = 0x7F7F7F7F;
	getSz(cur, 0), getCentroid(cur, 0, cur);
	vist[root] = true, mxDep = 0, ct[0] = 1;

	for(int i = head[root]; i != 0; i = E2[i].nxt)
	{
		const int to = E2[i].to;
		if(vist[to])
			continue;
		getAnswer(to, root, E2[i].d, 1);
		update(to, root, E2[i].d, 1);
	}

	for(int i = 0; i <= mxDep; i++)
		w[i] = 0, ct[i] = 0;
	for(int i = head[root]; i != 0; i = E2[i].nxt)
		if(!vist[E2[i].to])
			solve(E2[i].to);
}

int main()
{
	int u, v, d;
	scanf("%d%d%d", &N, &M, &K);
	for(int i = 1; i <= M; i++)
		scanf("%d%d%d", &u, &v, &d),
		E1[2 * i - 1].u = u, E1[2 * i - 1].v = v, E1[2 * i - 1].w = d,
		E1[2 * i].u = v, E1[2 * i].v = u, E1[2 * i].w = d;

	sort(E1 + 1, E1 + 1 + 2 * M);
	for(int i = 1; i <= 2 * M; i++)
		addEdge(E1[i].u, E1[i].v, E1[i].w);
	SPFA();
	memset(head, 0x00, sizeof head), allocCnt = 0;

	for(int i = 2; i <= N; i++)
		addEdge(i, pre[i], predist[i]), addEdge(pre[i], i, predist[i]);
	solve(1);

	printf("%d %d\n", ans, cnt);

}
