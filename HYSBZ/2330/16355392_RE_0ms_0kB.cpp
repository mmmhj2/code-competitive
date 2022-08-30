// BZOJ 2330 糖果
#include <cstring>
#include <cstdio>
#include <vector>
#include <queue>
using namespace std;

class DiffereceConstrainSolver
{
protected:
	static const int MAXN = 100000 + 10;
	static const int MAXM = 100000 * 10 + 10;

	struct edge
	{
		int to, w;
		edge * nxt;
	};
	typedef edge * pEdge;
	edge E[MAXM];
	pEdge head[MAXN];

	int allocCnt;

	pEdge addEdge(int u, int v, int w)
	{
		fprintf(stderr, "Edge added : %d %d %d\n", u, v, w);
		pEdge p = &E[allocCnt++];
		p->nxt = head[u], head[u] = p;
		p->to = v, p->w = w;
		return p;
	}

	int dist[MAXN];
	int inCnt[MAXN];
	bool inQueue[MAXN];

	int SPFA(int s, int N)
	{
//		memset(dist, 0x7F, sizeof dist);
//		memset(inCnt, 0x00, sizeof inCnt);
//		memset(inQueue, 0x00, sizeof inQueue);
		for (int i = 0; i <= N; i++)
			dist[i] = 0x80808080, inCnt[i] = 0, inQueue[i] = false;

		deque<int> Q;
		Q.push_back(s);
		dist[s] = 0, inCnt[s] = 1, inQueue[s] = 1;

		while (!Q.empty())
		{
			s = Q.front(), Q.pop_front();
			inQueue[s] = false;
			if (inCnt[s] > N)
				return -1;

			for (pEdge p = head[s]; p; p = p->nxt)
				if (dist[p->to] < dist[s] + p->w)
				{
					dist[p->to] = dist[s] + p->w;
					if (!inQueue[p->to])
					{
						inQueue[p->to] = true;
						inCnt[p->to]++;
						if (Q.empty())
							Q.push_back(p->to);
						else
						{
							if (dist[p->to] > dist[Q.front()])
								Q.push_back(p->to);
							else
								Q.push_front(p->to);
						}
					}
				}

		}
		return 0;
	}

public:

	void clearConstrains()
	{
		allocCnt = 0;
		memset(head, 0x00, sizeof head);
	}

	bool addConstrainEqual(int u, int v)
	{
		addEdge(u, v, 0);
		addEdge(v, u, 0);
		return true;
	}

	bool addConstrainLess(int u, int v)
	{
		if (u == v)
			return false;
		addEdge(u, v, 1);
		return true;
	}

	bool addConstrainLessEqual(int u, int v)
	{
		addEdge(u, v, 0);
		return true;
	}

	void addEdgeAll(int u, int S, int T, int w)
	{
		for (int i = S; i <= T; i++)
			addEdge(u, i, w);
	}

	bool solve(int s, int N)
	{
		return SPFA(s, N) != -1;
	}

	int query(int x)
	{
		return dist[x];
	}
};

DiffereceConstrainSolver DCS;

int main()
{
	int N, K;
	scanf("%d%d", &N, &K);

	while (K--)
	{
		int X, A, B;
		scanf("%d%d%d", &X, &A, &B);

		switch (X)
		{
		case 1:
			DCS.addConstrainEqual(A, B);
			break;
		case 2:
			if (!DCS.addConstrainLess(A, B))
			{
				puts("-1");
				return 0;
			}
			break;
		case 3:
			DCS.addConstrainLessEqual(B, A);
			break;
		case 4:
			if (!DCS.addConstrainLess(B, A))
			{
				puts("-1");
				return 0;
			}
			break;
		case 5:
			DCS.addConstrainLessEqual(A, B);
		}

	}
	DCS.addEdgeAll(0, 1, N, 1);

	if(!DCS.solve(0, N))
		puts("-1");
	else
	{
		long long answer = 0;
		for(int i = 1; i <= N; i++)
			answer += DCS.query(i);
		printf("%lld\n", answer);
	}

	return 0;
}
