#include <bits/stdc++.h>
using namespace std;

class VampireTreeDiv2
{
	typedef long long i64;
	static const int MAXN = 1000 + 10;
	static const int MOD = 1e9 + 7;

	struct _G
	{
		struct edge
		{
			int to;
			edge * nxt;
		} E[MAXN << 1];

		typedef edge *pEdge;

		int eCnt;
		pEdge head[MAXN];

		void addEdge(int u, int v)
		{
			pEdge p = &E[++eCnt];
			p->to = v;
			p->nxt = head[u];
			head[u] = p;
		}

		_G()
		{
			eCnt = 0;
		}
	} G;

	int dep[MAXN], fa[MAXN];
	int flag[MAXN];
	int f[MAXN][2];
	i64 g[MAXN][2];

	int N;
	vector<int> ch;

	void DFS(int x)
	{
		for (_G::pEdge p = G.head[x]; p; p = p->nxt)
			if (dep[p->to] < dep[x] + 1)
				dep[p->to] = dep[x] + 1, DFS(p->to);
	}

	void DP(int u);

public:
	int countMinSamples(vector<int> A, vector<int> B);
};

int VampireTreeDiv2::countMinSamples(vector<int> A, vector<int> B)
{
	N = A.size();

	for (int i = 0; i < N; i++)
		if (B[i] == -1)
			G.addEdge(A[i], i + 1);
		else
			ch.push_back(i), G.addEdge(A[i], i + 1), G.addEdge(B[i], i + 1);

	DFS(0);

	int lim = 1 << (ch.size()), mn = 0x7F7F7F7F;
	i64 res = 0;

	for (auto c : ch)
		fa[c + 1] = dep[A[c]] > dep[B[c]] ? A[c] : B[c];

	for (int s = 0; s < lim; s++)
	{
		memset(f, 0xFF, sizeof f);
		memset(g, 0xFF, sizeof g);

		for (unsigned i = 0; i < ch.size(); i++)
			flag[ch[i] + 1] = (s >> i & 1) + 1;
		DP(0);

		if (f[0][0] < mn)
			res = g[0][0];
		else if (f[0][0] == mn)
			res = (res + g[0][0]) % MOD;
		mn = min(mn, f[0][0]);

		if (f[0][1] < mn)
			res = g[0][1];
		else if (f[0][1] == mn)
			res = (res + g[0][1]) % MOD;
		mn = min(mn, f[0][1]);
	}
	return res;
}

void VampireTreeDiv2::DP(int u)
{
	if (f[u][0] != -1)
		return;
	f[u][0] = 0;
	g[u][0] = g[u][1] = f[u][1] = 1;
	bool flag0 = false, flag1 = false;
	int delta = 0;

	for (_G::pEdge p = G.head[u]; p; p = p->nxt)
	{
		const int v = p->to;
		DP(v);

		if (!flag[v] || (flag[v] && u == fa[v]))
		{
			if (f[v][1] >= 0x7F7F7F7F || flag0)
				flag0 = true, f[u][0] = 0x7F7F7F7F, g[u][0] = 0;
			else
				f[u][0] += f[v][1], g[u][0] = g[u][0] * g[v][1] % MOD;

			delta = min(f[v][0], f[v][1]);

			if (delta >= 0x7F7F7F7F || flag1)
				flag1 = true, f[u][1] = 0x7F7F7F7F, g[u][1] = 0;
			else
				f[u][1] += delta;

			g[u][1] *=
					f[v][0] < f[v][1] ?
							g[v][0] :
							(f[v][0] == f[v][1] ?
									(g[v][0] + g[v][1]) % MOD : g[v][1]);
			g[u][1] %= MOD;
		}
		else if (f[v][1] >= 0x7F7F7F7F)
			flag0 = true, f[u][0] = 0x7F7F7F7F, g[u][0] = 0;
	}

	if (flag[u] == 2)
		f[u][0] = 0x7F7F7F7F, g[u][0] = 0;
	if (flag[u] == 1)
		f[u][1] = 0x7F7F7F7F, g[u][1] = 0;
}
