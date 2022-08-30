#include <bits/stdc++.h>
using namespace std;

const int MAXN = 100000 + 10;

int N, M;
int A[MAXN];

namespace graph
{
int cnt;
int head[MAXN];
int to[MAXN << 1], nxt[MAXN << 1];

void addEdge(int u, int v)
{
	to[++cnt] = v;
	nxt[cnt] = head[u], head[u] = cnt;
}

int fa[MAXN], sz[MAXN], dep[MAXN];

void findSize(int x)
{
	//printf("%d\n", x);
	//fflush(stdout);
	sz[x] = 1;
	for (int p = head[x]; p; p = nxt[p])
		if (to[p] != fa[x])
			fa[to[p]] = x, dep[to[p]] = dep[x] + 1, findSize(to[p]), sz[x] +=
					sz[to[p]];
}

}

namespace DynamicSegTree
{
int root[MAXN << 2];
map<int, int> rootMap;
int rootCnt;

int ls[MAXN << 7], rs[MAXN << 7], sum[MAXN << 7];
int cnt;

void modify(int toMod, int val, int L, int R, int & x)
{
	if (!x)
		x = ++cnt;
	sum[x] += val;
	if (L == R)
		return;

	int mid = (L + R) >> 1;
	if (toMod <= mid)
		modify(toMod, val, L, mid, ls[x]);
	else
		modify(toMod, val, mid + 1, R, rs[x]);
}

int query(int qL, int qR, int L, int R, int x)
{
	if (!x)
		return 0;
	if (qL <= L && R <= qR)
		return sum[x];

	int ret = 0, mid = (L + R) >> 1;

	if (qL <= mid)
		ret += query(qL, qR, L, mid, ls[x]);
	if (qR > mid)
		ret += query(qL, qR, mid + 1, R, rs[x]);
	return ret;
}

}

namespace heavyLink
{

int posCnt;
int lnk[MAXN], pos[MAXN];

using namespace graph;

void decomp(int x, int pre)
{
	int heavySon = 0;
	lnk[x] = pre, pos[x] = ++posCnt;
	for (int p = head[x]; p; p = nxt[p])
		if (to[p] != fa[x])
			if (sz[to[p]] > sz[heavySon])
				heavySon = to[p];

	if (!heavySon)
		return;
	decomp(heavySon, pre);
	for (int p = head[x]; p; p = nxt[p])
		if (to[p] != fa[x] && to[p] != heavySon)
			decomp(to[p], to[p]);
}

int query(int x, int y, int val)
{
	int ret = 0;
	while(lnk[x] != lnk[y])
	{
		if(dep[lnk[x]] < dep[lnk[y]])
			swap(x, y);
		ret += DynamicSegTree::query(pos[lnk[x]], pos[x], 1, N, DynamicSegTree::root[val]);
		x = fa[lnk[x]];
	}

	if(dep[x] > dep[y])
		swap(x, y);
	ret += DynamicSegTree::query(pos[x], pos[y], 1, N, DynamicSegTree::root[val]);
	return ret;
}

}

int main()
{
	using DynamicSegTree::root;
	using DynamicSegTree::rootMap;
	using DynamicSegTree::rootCnt;

	char op[5];
	int x, y;

	scanf("%d%d", &N, &M);
	for (int i = 1; i <= N; i++)
		scanf("%d", &A[i]);
	for (int i = 1; i < N; i++)
		scanf("%d%d", &x, &y), graph::addEdge(x, y), graph::addEdge(y, x);

	graph::findSize(1);
	heavyLink::decomp(1, 1);

	for (int i = 1; i <= N; i++)
	{
		if (!rootMap[A[i]])
			rootMap[A[i]] = ++rootCnt;
		DynamicSegTree::modify(heavyLink::pos[i], 1, 1, N, root[rootMap[A[i]]]);
	}

	while (M--)
	{
		scanf("%s%d%d", op, &x, &y);
		if(op[0] == 'C')
		{
			assert(root[rootMap[A[x]]]);
			DynamicSegTree::modify(heavyLink::pos[x], -1, 1, N, root[rootMap[A[x]]]);
			A[x] = y;
			if(!rootMap[A[x]])
				rootMap[A[x]] = ++rootCnt;
			DynamicSegTree::modify(heavyLink::pos[x], 1, 1, N, root[rootMap[A[x]]]);

		}
		else
		{
			int z;
			scanf("%d", &z);
			if(rootMap[z] == 0)
				puts("0");
			else
				printf("%d\n", heavyLink::query(x, y, rootMap[z]));
		}
	}

	return 0;
}
