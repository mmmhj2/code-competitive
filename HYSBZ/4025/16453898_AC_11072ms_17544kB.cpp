// BZOJ4025 二分图
#include <bits/stdc++.h>
using namespace std;

struct edge
{
	int u, v;
	int s, t;
	edge(int _u = 0, int _v = 0, int _s = 0, int _t = 0)
	{
		u = _u, v = _v, s = _s, t = _t;
	}
};
const int MAXN = 100000 + 100;
int N, M, T;

namespace disjointSet
{
stack<int> stk;
int fa[MAXN], rnk[MAXN], a[MAXN];

void init()
{
	for (int i = 1; i <= N; i++)
		fa[i] = i;
}

int find(int x)
{
	while (fa[x] != x && fa[x] != 0)
		x = fa[x];
	return x;
}

int dist(int x)
{
	int ret = 0;

	while (fa[x] != x && fa[x] != 0)
		ret ^= a[x], x = fa[x];
	return ret;
}

bool joint(int x, int y, int z)
{
	x = find(x), y = find(y);
	if (x == y)
		return false;
	if (rnk[x] > rnk[y])
		swap(x, y);
	if (rnk[x] == rnk[y])
		rnk[y]++, stk.push(-y);
	fa[x] = y, a[x] = z;
	stk.push(x);
	return true;
}

void restore(unsigned bot)
{
	while (stk.size() > bot)
	{
		if (stk.top() < 0)
			rnk[-stk.top()]--;
		else
			fa[stk.top()] = stk.top(), a[stk.top()] = 0;
		stk.pop();
	}
}
}

void DC(int x, int y, vector<edge>&e)
{
	using namespace disjointSet;
	vector<edge> L, R;
	unsigned bot = stk.size();

	int mid = (x + y) >> 1;
	for (vector<edge>::iterator itr = e.begin(); itr != e.end(); ++itr)
	{
		if (itr->s == x && itr->t == y)
		{
			//int tx = find(itr->u), ty = find(itr->v), tz = dist(itr->u);
			int dst = dist(itr->u) ^ dist(itr->v) ^ 1;
			if (!joint(itr->u, itr->v, dst))
				if (dst & 1)
				{
					for (int i = x; i <= y; i++)
						puts("No");
					restore(bot);
					return;
				}
		}
		else if (itr->t <= mid)
			L.push_back(*itr);
		else if (itr->s > mid)
			R.push_back(*itr);
		else
			L.push_back(edge
			{ itr->u, itr->v, itr->s, mid }), R.push_back(edge
			{ itr->u, itr->v, mid + 1, itr->t });
	}

	if (x == y)
		puts("Yes");
	else
		DC(x, mid, L), DC(mid + 1, y, R);
	restore(bot);
}

vector<edge> t;
int main()
{
	edge e;

	cin >> N >> M >> T;
	disjointSet::init();

	for (int i = 1; i <= M; i++)
	{
		cin >> e.u >> e.v >> e.s >> e.t;
		e.s += 1;
		if (e.s > e.t)
			continue;
		t.push_back(e);
	}
	DC(1, T, t);
	return 0;
}
