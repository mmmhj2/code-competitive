#include <bits/stdc++.h>
using namespace std;

class DeerInZooDivOne
{
	const static int MAXN = 51 + 5;

	int N;
	int S, T;
	int memo[MAXN][MAXN][MAXN][MAXN];
	int col[MAXN];

	vector<int> orgG[MAXN];

	class Graph
	{
		static const int MAXE = 5000 + 500;
		int eCnt;

		struct edge
		{
			int to, cost, cap;
			edge * nxt;
			edge * inv;
		} E[MAXE];
	public:
		typedef edge *pEdge;
		pEdge head[MAXN];

		void clear()
		{
			memset(head, 0x00, sizeof head);
			eCnt = 0;
		}
		void addEdge(int u, int v, int cap, int cst)
		{
			pEdge p, q;
			p = &E[++eCnt];
			p->nxt = head[u], head[u] = p;
			p->to = v, p->cap = cap, p->cost = cst;

			q = &E[++eCnt];
			q->nxt = head[v], head[v] = q;
			q->to = u, q->cap = 0, q->cost = -cst;

			p->inv = q, q->inv = p;
		}
	} G;

	void Coloring(int cur, int fa, int c)
	{
		col[cur] = c;
		for (auto to : orgG[cur])
			if (to != fa)
				Coloring(to, cur, c);
	}


	int dist[MAXN];
	bool inQueue[MAXN];
	Graph::pEdge pre[MAXN];
	bool SPFA(int & ret);
	int DFS(int a, int fa, int b, int fb);

public:
	int getmax(vector<int> a, vector<int> b);
};

bool DeerInZooDivOne::SPFA(int& ret)
{
	memset(dist, 0x3F, sizeof dist);
	memset(inQueue, 0x00, sizeof inQueue);

	queue<int> Q;
	Q.push(S), dist[S] = 0, inQueue[S] = true;

	while (!Q.empty())
	{
		int x;
		x = Q.front(), Q.pop(), inQueue[x] = false;

		for (Graph::pEdge p = G.head[x]; p; p = p->nxt)
			if(p->cap != 0 && dist[p->to] > dist[x] + p->cost)
			{
				dist[p->to] = dist[x] + p->cost;
				pre[p->to] = p;
				if(!inQueue[p->to])
					Q.push(p->to), inQueue[p->to] = true;
			}
	}

	if(dist[T] == 0x3F3F3F3F)
		return false;

	for(int p = T; p != S; p = pre[p]->inv->to)
		(pre[p]->cap)--, (pre[p]->inv->cap)++;
	ret -= dist[T];

	return true;
}

int DeerInZooDivOne::DFS(int a, int fa, int b, int fb)
{
	if(memo[a][fa][b][fb] != -1)
		return memo[a][fa][b][fb];

	for(vector<int>::iterator itr = orgG[a].begin(); itr != orgG[a].end(); ++itr)
		if(*itr != fa)
			for(vector<int>::iterator jtr = orgG[b].begin(); jtr != orgG[b].end(); ++jtr)
				if(*jtr != fb)
					DFS(*itr, a, *jtr, b);

	int & ret = memo[a][fa][b][fb];
	ret = 1;
	G.clear();

	for(unsigned i = 0; i < orgG[a].size(); i++)
		if(orgG[a][i] != fa)
			for(unsigned j = 0; j < orgG[b].size(); j++)
				if(orgG[b][j] != fb)
					G.addEdge(i, j + orgG[a].size(), 1, -memo[orgG[a][i]][a][orgG[b][j]][b]);
	S = orgG[a].size() + orgG[b].size();
	T = S + 1;

	for(unsigned i = 0; i < orgG[a].size(); i++)
		G.addEdge(S, i, 1, 0);
	for(unsigned i = 0; i < orgG[b].size(); i++)
		G.addEdge(i + orgG[a].size(), T, 1, 0);

	while(SPFA(ret));
	return ret;
}

int DeerInZooDivOne::getmax(vector<int> a, vector<int> b)
{
	N = a.size() + 1;
	int ret = 0;

	for(int k = 0; k < N - 1; k++)
	{
		memset(memo, 0xFF, sizeof memo);
		for(int i = 0; i < N; i++)
			orgG[i].clear();
		for(int i = 0; i < N - 1; i++)
			if(i != k)
				orgG[a[i]].push_back(b[i]),
				orgG[b[i]].push_back(a[i]);

		Coloring(a[k], b[k], 1);
		Coloring(b[k], a[k], 2);
/*
		for(int i = 0; i < N; i++)
			cerr << col[i] << " " ;
		cerr << endl ;
*/
		for(int a = 0; a < N; a++)
			if(col[a] == 1)
				for(int b = 0; b < N; b++)
					if(col[b] == 2)
						ret = max(ret, DFS(a, 0, b, 0));
	}
	return ret;
}
