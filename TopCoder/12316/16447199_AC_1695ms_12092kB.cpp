///////////////////////////////////////////////
#include <bits/stdc++.h>
using namespace std;

class ThreeColorability
{
	static const int MAXN = 50 + 5;

	class
	{
		int fa[ThreeColorability::MAXN];
	public:
		void initialize()
		{
			iota(fa, fa + ThreeColorability::MAXN, 0);
		}

		int find(int x)
		{
			if (fa[x] == x)
				return x;
			return fa[x] = find(fa[x]);
		}

		void merge(int x, int y)
		{
//			cerr << "Merge " << x << " " << y << endl ;
			fa[find(x)] = find(y);
		}

	} disjointSet;

	struct edge;
	typedef struct edge * pEdge;
	struct edge
	{
		int to;
		pEdge nxt;
	} E[MAXN * MAXN * 4];

	int eCnt;
	int N, M;
	int vis[MAXN];
	int a[MAXN][MAXN];

	bool adjMat[MAXN][MAXN];
	pEdge head[MAXN];

	void addEdge(int u, int v)
	{
//		cerr << "Edge added :" << u << " " << v << endl ;
		pEdge p;
		p = &E[eCnt++];
		p->nxt = head[u], head[u] = p;
		p->to = v;

		p = &E[eCnt++];
		p->nxt = head[v], head[v] = p;
		p->to = u;
	}

	bool isBipartite = true;
	void DFS(int x, int col)
	{
		if (vis[x] >= 0)
		{
//			cerr << "Revisited " << x << " " << col << " " << vis[x] << endl ;
			if (vis[x] != col)
				isBipartite = false;
			return;
		}
		vis[x] = col;

		for (pEdge p = head[x]; p; p = p->nxt)
			DFS(p->to, col ^ 1);
	}

public:

	ThreeColorability()
	{
		eCnt = 0;
		N = 0, M = 0;
		memset(vis, 0xFF, sizeof vis);
		memset(head, 0x00, sizeof head);
		memset(adjMat, 0x00, sizeof adjMat);
		disjointSet.initialize();
	}

	vector<string> lexSmallest(vector<string> cells)
	{
		vector<string> answer = cells;
		N = cells.size(), M = cells[0].length();

		for (int i = 0; i < N; i++)
			for (int j = 0; j < M; j++)
				switch (cells[i][j])
				{
				case '?':
					a[i][j] = -1;
					break;
				case 'N':
					a[i][j] = 0;
					break;
				default:
					a[i][j] = 1;
				}

		for (int i = 1; i < N; i++)
			for (int j = 0; j < M; j++)
				for (int k = j + 1; k < M; k++)
					if ((~a[i][j]) && (~a[i][k]))
					{
						if (a[i][j] ^ a[i][k])
							adjMat[j][k] = adjMat[k][j] = 1;
						else
							disjointSet.merge(j, k);
					}

		for (int i = 0; i < M; i++)
			for (int j = i + 1; j < M; j++)
				if (adjMat[i][j])
					addEdge(disjointSet.find(i), disjointSet.find(j));

		for (int i = 0; i < M; i++)
			if (~a[0][i])
				DFS(disjointSet.find(i), a[0][i]);
		for (int i = 0; i < M; i++)
			if (vis[disjointSet.find(i)] < 0)
				DFS(disjointSet.find(i), 0);

		if (!isBipartite)
			return vector<string>
			{ };

		for (int i = 0; i < M; i++)
			a[0][i] = vis[disjointSet.find(i)];
		for (int i = 1; i < N; i++)
		{
			bool vist[2] =
			{ 0 };
			for (int j = 0; j < M; j++)
				if (~a[i][j])
					vist[a[i][j] ^ a[0][j]] = 1;
			if (!vist[0] && !vist[1])
				vist[a[0][0]] = 1;

			if(vist[0])
				for(int j = 0; j < M; j++)
					a[i][j] = a[0][j];
			else
				for(int j = 0; j < M; j++)
					a[i][j] = a[0][j] ^ 1;
		}

		for(int i = 0; i < N; i++)
			for(int j = 0; j < M; j++)
				answer[i][j] = (a[i][j] ? 'Z' : 'N');

		return answer;
	}
};
