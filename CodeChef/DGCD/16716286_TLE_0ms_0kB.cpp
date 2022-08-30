// CodeChef DGCD Dynamic GCD

#include <bits/stdc++.h>
using namespace std;

const int MAXN = 50000 + 10;

int N, M;
int val[MAXN];

int gcd(int x, int y)
{
	if (!y)
		return abs(x);
	return gcd(y, x % y);
}

namespace OptmizedReading
{
	static const int BUF_LEN = 5000000 + 10;
	int errflag;
	char pBuffer[BUF_LEN];
	char * pRead;
	void resetFlow()
	{
		int len = fread(pBuffer, 1, BUF_LEN - 1, stdin);
		pBuffer[len] = '\0';        // Append null character
		if (len != BUF_LEN - 1)
			errflag = EOF;

		pRead = pBuffer;
	}
	void setEofRead()
	{
		errflag = EOF;
		if (pRead == pBuffer + BUF_LEN)
			resetFlow();
	}
	int ReadUnInt()
	{
		int ret = 0;

		while (*pRead < '0' || *pRead > '9')
		{
			if (*pRead == '\0')
			{
				setEofRead();
				return 0;
			}

			*pRead = '\0';
			pRead++;
			if (*pRead == '\0')
				resetFlow();
		}

		while (*pRead >= '0' && *pRead <= '9')
		{
			ret = ret * 10 + (*pRead - '0'), *pRead = '\0', pRead++;
			if (*pRead == '\0')
				resetFlow();
		}
		return ret;
	}
	int readChar()
	{
		char ch = *pRead;
		if (ch == '\0')
		{
			setEofRead();
			return EOF;
		}
		pRead++;
		if (*pRead == '\0')
			resetFlow();
		return ch;
	}
}
;

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
		p->to = v;
		p->nxt = head[u], head[u] = p;

		p = &E[++edge::eCnt];
		p->to = u;
		p->nxt = head[v], head[v] = p;
	}
}
int Graph::edge::eCnt = 0;

namespace HeavyLink
{
	using namespace Graph;
	int tmStp;
	int dep[MAXN], son[MAXN];
	int pos[MAXN], idx[MAXN];
	int siz[MAXN], fa[MAXN];

	int top[MAXN];

	void getSize(int x, int fa)
	{
		dep[x] = dep[fa] + 1, siz[x] = 1;
		for (pEdge p = head[x]; p; p = p->nxt)
			if (p->to != fa)
				HeavyLink::fa[p->to] = x, getSize(p->to, x), siz[x] +=
						siz[p->to];
	}

	void decomp(int x, int lnk)
	{
		tmStp++;
		pos[x] = tmStp, idx[tmStp] = x;
		top[x] = lnk;

		int hvySon = -1, hvyVal = -1;
		for (pEdge p = head[x]; p; p = p->nxt)
			if (p->to != fa[x] && siz[p->to] > hvyVal)
				hvyVal = siz[p->to], hvySon = p->to;
		if (hvySon < 0)
			return;

		son[x] = hvySon;
		decomp(hvySon, lnk);

		for (pEdge p = head[x]; p; p = p->nxt)
			if (p->to != fa[x] && p->to != hvySon)
				decomp(p->to, p->to);
	}

	void runDecomposite()
	{
		getSize(1, 0);
		tmStp = 1;
		top[1] = 1, idx[1] = 1, pos[1] = 1;
		decomp(1, 1);
	}
}

namespace SegmentTree
{
#define LC ((x << 1))
#define RC ((x << 1) | 1)
	using namespace HeavyLink;
	struct node
	{
		int lazy;
		int val;
		int delta;
	} Tree[MAXN << 2];

	void push_up(int x)
	{
		Tree[x].delta = gcd(Tree[LC].delta, Tree[RC].delta);
	}

	void push_down(int x, int L, int R)
	{
		//fprintf(stderr, "Pushed down : %d %d %d, current lazy tag : %d\n", x, L, R, Tree[x].lazy);
		if (L == R)
			Tree[x].val += Tree[x].lazy;
		else
			Tree[LC].lazy += Tree[x].lazy, Tree[RC].lazy += Tree[x].lazy;
		Tree[x].lazy = 0;
	}

	void build(int x, int L, int R)
	{
		if (L == R)
			return Tree[x].val = val[idx[L]], Tree[x].delta = val[idx[L]]
					- val[idx[L - 1]], (void) 0;
		int mid = (L + R) >> 1;
		build(LC, L, mid);
		build(RC, mid + 1, R);
		push_up(x);
	}

	// Query
	int query_point(int k, int x = 1, int L = 1, int R = N)
	{
		push_down(x, L, R);
		if (L == R)
			return Tree[x].val;
		int mid = (L + R) >> 1;
		if (k <= mid)
			return query_point(k, LC, L, mid);
		else
			return query_point(k, RC, mid + 1, R);
	}

	int query_segment(int QL, int QR, int x = 1, int L = 1, int R = N)
	{
		if (QL > QR || R < QL || QR < L)
			return 0;
		if (QL <= L && R <= QR)
			return Tree[x].delta;
		int mid = (L + R) >> 1;
		return gcd(query_segment(QL, QR, LC, L, mid),
				query_segment(QL, QR, RC, mid + 1, R));
	}

	// Modify
	void modify_point(int k, int val, int x = 1, int L = 1, int R = N)
	{
		//assert(1 <= k && k <= N);
		if (L == R)
			return Tree[x].delta += val, (void) 0;
		int mid = (L + R) >> 1;
		if (k <= mid)
			modify_point(k, val, LC, L, mid);
		else
			modify_point(k, val, RC, mid + 1, R);
		push_up(x);
	}

	void modify_segment(int val, int QL, int QR, int x = 1, int L = 1,
			int R = N)
	{
		if (QR < L || R < QL)
			return;
		push_down(x, L, R);
		if (QL <= L && R <= QR)
			return Tree[x].lazy += val, (void) 0;

		int mid = (L + R) >> 1;
		modify_segment(val, QL, QR, LC, L, mid);
		modify_segment(val, QL, QR, RC, mid + 1, R);
	}

	namespace OnTree
	{
		int query_path(int u, int v)
		{
			if (top[u] != top[v])
			{
				if (dep[top[u]] < dep[top[v]])
					swap(u, v);
				if (top[u] != u)
					return gcd(query_path(fa[top[u]], v),
							gcd(query_segment(pos[son[top[u]]], pos[u]),
									query_point(pos[top[u]])));
				return gcd(query_path(fa[top[u]], v), query_point(pos[top[u]]));
			}

			if (dep[u] > dep[v])
				swap(u, v);

			if (u != v)
			{
				int x = query_point(pos[u]);
				int y = query_segment(pos[son[u]], pos[v]);
				return gcd(x, y);
			}
			return query_point(pos[u]);
		}

		void modify_path(int u, int v, int val)
		{
			if (top[u] != top[v])
			{
				if (dep[top[u]] < dep[top[v]])
					swap(u, v);
				modify_point(pos[top[u]], val);
				if (son[u] != u)
					modify_point(pos[son[u]], -val);
				modify_segment(val, pos[top[u]], pos[u]);
				modify_path(fa[top[u]], v, val);
				return;
			}
			if (dep[u] > dep[v])
				swap(u, v);
			modify_point(pos[u], val);

			if (son[v])
				modify_point(pos[son[v]], -val);
			modify_segment(val, pos[u], pos[v]);
			return;
		}

	}

#undef LC
#undef RC
}

int main()
{
	freopen("DGCD.in", "r", stdin);
	OptmizedReading::resetFlow();
	N = OptmizedReading::ReadUnInt();
	for (int i = 1; i < N; i++)
	{
		int u = OptmizedReading::ReadUnInt() + 1;
		int v = OptmizedReading::ReadUnInt() + 1;
		Graph::addEdge(u, v);
	}
	for (int i = 1; i <= N; i++)
		val[i] = OptmizedReading::ReadUnInt();

	HeavyLink::runDecomposite();
	SegmentTree::build(1, 1, N);
/*
	for (int i = 1; i <= N; i++)
		printf("%d ", HeavyLink::pos[i]);
	puts("");
*/

	int Q = OptmizedReading::ReadUnInt();

	while (Q--)
	{
		char op = '\0';
		while (op != 'F' && op != 'C')
			op = OptmizedReading::readChar();
		if (op == 'C')
		{
			int a, b, c;
			a = OptmizedReading::ReadUnInt() + 1;
			b = OptmizedReading::ReadUnInt() + 1;
			c = OptmizedReading::ReadUnInt();
			SegmentTree::OnTree::modify_path(a, b, c);
		}
		else
		{
			int a, b;
			a = OptmizedReading::ReadUnInt() + 1;
			b = OptmizedReading::ReadUnInt() + 1;
			printf("%d\n", SegmentTree::OnTree::query_path(a, b));
		}
	}

	return 0;
}

