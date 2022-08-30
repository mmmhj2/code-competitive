#include <bits/stdc++.h>
using namespace std;

const int MAXN = 10000 + 10;

int N, M;
int sum;
int ans[MAXN], Q[MAXN];

namespace Graph
{
	struct edge
	{
		static int eCnt;
		int to, cst;
		edge * nxt;
	} E[MAXN * 2];
	typedef edge * pEdge;

	pEdge head[MAXN];
	inline void addEdge(int u, int v, int w)
	{
		pEdge p = &E[++edge::eCnt];
		p->nxt = head[u], head[u] = p;
		p->to = v, p->cst = w;
	}
}

int Graph::edge::eCnt = 0;

namespace division
{
	using namespace Graph;
	int centroid = 0;
	int siz[MAXN], maxSz[MAXN];
	bool vis[MAXN];

	int deep[MAXN], cst[MAXN];

	namespace binarySearch
	{
		int lower_bound(int l, int r, int k)
		{
			int ans = 0;
			while (l <= r)
			{
				int mid = (l + r) >> 1;
				if (deep[mid] == k)
					ans = mid, r = mid - 1;
				else if (deep[mid] < k)
					l = mid + 1;
				else
					r = mid - 1;
			}
			return ans;
		}
		int upper_bound(int l, int r, int k)
		{
			int ans = -1;
			while (l <= r)
			{
				int mid = (l + r) >> 1;
				if (deep[mid] == k)
					ans = mid, l = mid + 1;
				else if (deep[mid] < k)
					l = mid + 1;
				else
					r = mid - 1;
			}
			return ans;
		}
	}

	void getCentroid(int x, int fa)
	{
		siz[x] = 1, maxSz[x] = 0;
		for (pEdge p = head[x]; p; p = p->nxt)
			if (p->to != fa && !vis[p->to])
				getCentroid(p->to, x), siz[x] += siz[p->to], maxSz[x] = max(
						maxSz[x], siz[p->to]);
		maxSz[x] = max(maxSz[x], sum - siz[x]);
		if (maxSz[x] < maxSz[centroid])
			centroid = x;
	}

	void getDeep(int x, int fa)
	{
		deep[++deep[0]] = cst[x];
		for (pEdge p = head[x]; p; p = p->nxt)
			if (p->to != fa && !vis[p->to])
				cst[p->to] = cst[x] + p->cst, getDeep(p->to, x);
	}

	int calcAns(int x, int now, int k)
	{
		cst[x] = now, deep[0] = 0;
		getDeep(x, 0);
		sort(&deep[1], &deep[deep[0] + 1]);
		int ret = 0;

		for (int i = 1; i <= deep[0]; i++)
		{
			if (deep[i] * 2 > k)
				break;
			ret += binarySearch::upper_bound(i, deep[0], k - deep[i])
					- binarySearch::lower_bound(i, deep[0], k - deep[i]) + 1;
		}
		return ret;
	}

	void DFS(int x)
	{
		for (int i = 1; i <= M; i++)
			ans[i] += calcAns(x, 0, Q[i]);
		vis[x] = true;
		for (pEdge p = head[x]; p; p = p->nxt)
			if (!vis[p->to])
			{
				for (int j = 1; j <= M; j++)
					ans[j] -= calcAns(p->to, p->cst, Q[j]);
				sum = siz[p->to], centroid = 0;
				getCentroid(p->to, 0);
				DFS(centroid);
			}
	}

}

int main()
{
	using namespace division;
	maxSz[0] = 0x7F7F7F7F;
	int u, v, w;

	scanf("%d%d", &N, &M);
	for (int i = 1; i < N; i++)
		scanf("%d%d%d", &u, &v, &w), addEdge(u, v, w), addEdge(v, u, w);
	for (int i = 1; i <= M; i++)
		scanf("%d", &Q[i]);

	sum = N, centroid = 0;
	getCentroid(1, 0);
	DFS(centroid);

	for (int i = 1; i <= M; i++)
		if (ans[i])
			puts("Yes");
		else
			puts("No");

	return 0;
}
