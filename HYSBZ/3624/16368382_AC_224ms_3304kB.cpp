#include <algorithm>
#include <cstdio>
#include <vector>
using namespace std;

const int MAXN = 20000 + 10;

namespace disjointSet
{
int fa[MAXN];

void init(int N)
{
	for (int i = 1; i <= N; i++)
		fa[i] = i;
}

int find(int x)
{
	if (fa[x] == x)
		return x;
	return fa[x] = find(fa[x]);
}

void merge(int x, int y)
{
	//x = find(x), y = find(y);
	fa[x] = y;
}
}
;

struct edge
{
	int u, v, k;
};

bool selected[MAXN * 5];
int cnt1, cnt0;
int N, M, K;
vector<edge> E;

bool Kruskal_Altered()
{
	int x, y;
	for (int i = 1; i <= M; i++)
		if (E[i].k == 1)
		{
			x = disjointSet::find(E[i].u), y = disjointSet::find(E[i].v);
			if (x != y)
				disjointSet::merge(x, y), cnt1++;
		}

	for (int i = 1; i <= M; i++)
		if (E[i].k == 0)
		{
			x = disjointSet::find(E[i].u), y = disjointSet::find(E[i].v);
			if (x != y)
				disjointSet::merge(x, y), selected[i] = true, cnt0++;
		}
	if (cnt1 + cnt0 != N - 1 || cnt0 > K)
		return false;
	return true;
}

int main()
{
	int u, v, k;
	scanf("%d%d%d", &N, &M, &K);
	E.push_back((edge{0, 0, 0}));
	for (int i = 1; i <= M; i++)
		scanf("%d%d%d", &u, &v, &k), E.push_back((edge
				)
				{ u, v, k });
	disjointSet::init(N);
	if (!Kruskal_Altered())
		return printf("no solution\n"), 0;
	disjointSet::init(N);
	cnt0 = cnt1 = 0;

	int x, y;
	for (int i = 1; i <= M; i++)
		if (selected[i])
		{
			x = disjointSet::find(E[i].u), y = disjointSet::find(E[i].v);
			if (x != y)
				disjointSet::merge(x, y), cnt0++;
		}
	for (int i = 1; i <= M; i++)
		if (E[i].k == 0 && cnt0 < K)
		{
			x = disjointSet::find(E[i].u), y = disjointSet::find(E[i].v);
			if (x != y)
				disjointSet::merge(x, y), cnt0++, selected[i] = true;
		}
	if (cnt0 != K)
		return printf("no solution\n"), 0;
	for (int i = 1; i <= M; i++)
		if (E[i].k == 1)
		{
			x = disjointSet::find(E[i].u), y = disjointSet::find(E[i].v);
			if (x != y)
				disjointSet::merge(x, y), cnt1++, selected[i] = true;
		}

	for (int i = 1; i <= M; i++)
		if (selected[i])
			printf("%d %d %d\n", E[i].u, E[i].v, E[i].k);

	return 0;
}
