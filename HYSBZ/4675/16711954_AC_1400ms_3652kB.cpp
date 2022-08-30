#include <bits/stdc++.h>
using namespace std;

const int MAXN = 50000 + 10;

int N, M;
int luck[20];
int ans;

namespace Graph
{
	struct edge
	{
		static int eCnt;
		int to;
		edge * nxt;
	} E[MAXN * 2];
	typedef edge *pEdge;

	pEdge head[MAXN];

	inline void addEdge(int u, int v)
	{
		pEdge p;
		p = &E[++edge::eCnt];
		p->nxt = head[u], head[u] = p;
		p->to = v;

		p = &E[++edge::eCnt];
		p->nxt = head[v], head[v] = p;
		p->to = u;
	}
}

int Graph::edge::eCnt = 0;

namespace Division
{
	using namespace Graph;
	int centroid, centSz;
	int subtreeSz;
	int siz[MAXN];
	bool vis[MAXN];

	int dis[MAXN];
	int f[MAXN], g[MAXN];

	void _getCentroid(int x, int fa)
	{
		siz[x] = 1;
		int mxSz = 0;
		for (pEdge p = head[x]; p; p = p->nxt)
			if (!vis[p->to] && p->to != fa)
				_getCentroid(p->to, x), siz[x] += siz[p->to], mxSz = max(mxSz,
						siz[p->to]);
		mxSz = max(mxSz, subtreeSz - mxSz);
		if (mxSz < centSz)
			centroid = x, centSz = mxSz;
	}
	void getCentroid(int x, int fa, int sz)
	{
		subtreeSz = sz, centroid = 0, centSz = 0x7F7F7F7F;
		_getCentroid(x, fa);
	}

	void getDist(int x, int fa)
	{
		siz[x] = 1, dis[x] = 0;
		for (pEdge p = head[x]; p; p = p->nxt)
			if (p->to != fa && !vis[p->to])
				getDist(p->to, x), siz[x] += siz[p->to], dis[x] = max(dis[x],
						dis[p->to] + 1);
	}

	void getDep(int x, int fa, int dep)
	{
		g[dep]++;
		for (int i = 1; i <= M; i++)
			if (dep <= luck[i])
				ans += f[luck[i] - dep];
		for (pEdge p = head[x]; p; p = p->nxt)
			if (p->to != fa && !vis[p->to])
				getDep(p->to, x, dep + 1);
	}

	void DFS(int x)
	{
		vis[x] = true, f[0] = 1;
		getDist(x, 0);

		for (pEdge p = head[x]; p; p = p->nxt)
			if (!vis[p->to])
			{
				getDep(p->to, x, 1);
				for (int j = 0; j <= dis[p->to] + 1; j++)
					f[j] += g[j], g[j] = 0;
			}

		memset(f, 0x00, (sizeof(int)) * (dis[x] + 2));

		for (pEdge p = head[x]; p; p = p->nxt)
			if (!vis[p->to])
				getCentroid(p->to, x, siz[x]), DFS(centroid);
	}
}

int main()
{
	int u, v;
	scanf("%d%d", &N, &M);
	for (int i = 1; i <= M; i++)
		scanf("%d", &luck[i]);
	for (int i = 1; i < N; i++)
		scanf("%d%d", &u, &v), Graph::addEdge(u, v);

	Division::getCentroid(1, 0, N);
	Division::DFS(1);

	u = (N + 2) / 3;
	printf("%.2lf\n", 1.0 * u * (u - 1) * ans / (1.0 * N * (N - 1)));
	u = (N + 1) / 3;
	printf("%.2lf\n", 1.0 * u * (u - 1) * ans / (1.0 * N * (N - 1)));
	u = N / 3;
	printf("%.2lf\n", 1.0 * u * (u - 1) * ans / (1.0 * N * (N - 1)));

	return 0;
}
