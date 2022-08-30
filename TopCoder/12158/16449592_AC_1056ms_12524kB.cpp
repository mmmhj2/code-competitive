#include <bits/stdc++.h>
#pragma GCC diagnostic ignored "-Wchar-subscripts"
using namespace std;

class SurroundingGame
{
	static const int MAXN = 21 * 21 * 2;
	static const int INF = 0x7F7F7F7F;
	static const int DIR[4][2];

	int chMap[300], N, M;

	inline int getId(int x, int y, bool flag);
///////////////////////////////////////////////////////////////
	class NetworkFlowing
	{
		//int tHead[MAXN], dist[MAXN];
		struct _G
		{
			struct edge;
			typedef edge * pEdge;
			struct edge
			{
				int to, cap;
				pEdge inv, nxt;
			} E[MAXN * 30];

			int eCnt;
			pEdge head[MAXN];

			void addEdge(int u, int v, int w)
			{
				pEdge p = &E[eCnt++], q = &E[eCnt++];

				p->inv = q, q->inv = p;
				p->to = v, q->to = u;
				p->cap = w, q->cap = 0;

				p->nxt = head[u], q->nxt = head[v];
				head[u] = p, head[v] = q;
			}
		} G;

		typedef _G::pEdge pEdge;

		pEdge tHead[MAXN];
		int dist[MAXN];
		void getDistTag();
		int Dinic(int cur, int res);
	public:

		int S, T;
		void addEdge(int u, int v, int cap)
		{
			G.addEdge(u, v, cap);
		}

		int maxFlow();
	} NF;
///////////////////////////////////////////////////////////////
	void prepare();
	int build(vector<string>, vector<string>);
public:
	int maxScore(vector<string> cost, vector<string> benefit);
};

///////////////////////////////////////////////////////////////

const int SurroundingGame::DIR[4][2] =
{
{ 1, 0 },
{ -1, 0 },
{ 0, 1 },
{ 0, -1 } };

///////////////////////////////////////////////////////////////

void SurroundingGame::NetworkFlowing::getDistTag()
{
	queue<int> Q;
	memset(dist, 0x7F, sizeof dist);
	dist[T] = 0, Q.push(T);

	while (!Q.empty())
	{
		int cur = Q.front();
		Q.pop();
		for (pEdge p = G.head[cur]; p; p = p->nxt)
			if (p->inv->cap > 0 && dist[p->to] > dist[cur] + 1)
				dist[p->to] = dist[cur] + 1, Q.push(p->to);
	}
}

int SurroundingGame::NetworkFlowing::Dinic(int cur, int res)
{
	if (cur == T || res == 0)
		return res;
	int flow = 0, delta;

	for (pEdge & p = tHead[cur]; p; p = p->nxt)
		if (dist[p->to] + 1 == dist[cur] && p->cap > 0)
		{
			delta = Dinic(p->to, min(res, p->cap));
			p->cap -= delta, p->inv->cap += delta;

			flow += delta, res -= delta;

			if (res == 0)
				return flow;
		}
	dist[cur] = INF - 1;
	return flow;
}

int SurroundingGame::NetworkFlowing::maxFlow()
{
	int flow = 0;
	while (true)
	{
		getDistTag();
		if (dist[S] >= INF)
			break;
		assert(sizeof tHead == sizeof G.head);
		memcpy(tHead, G.head, sizeof tHead);

		flow += Dinic(S, INF);
	}
	return flow;
}

///////////////////////////////////////////////////////////////

int SurroundingGame::getId(int x, int y, bool flag)
{
	return x * M + y + 1 + ((flag) ? (N * M) : 0);
}

void SurroundingGame::prepare()
{
	for (int i = '0'; i <= '9'; i++)
		chMap[i] = i - '0';
	for (int i = 'a'; i <= 'z'; i++)
		chMap[i] = i - 'a' + 10;
	for (int i = 'A'; i <= 'Z'; i++)
		chMap[i] = i - 'A' + 10 + 26;
}

int SurroundingGame::build(vector<string> c, vector<string> b)
{
	int sum = 0;

	N = c.size(), M = c.begin()->size();
	NF.S = 0, NF.T = getId(N - 1, M - 1, 1) + 1;

	for (int i = 0; i < N; i++)
		for (int j = 0; j < M; j++)
			if ((i + j) & 1)		// White cell
			{
				sum += chMap[b[i][j]] + max(0, chMap[b[i][j]] - chMap[c[i][j]]);
				NF.addEdge(NF.S, getId(i, j, 1), chMap[b[i][j]]);
				NF.addEdge(getId(i, j, 1), getId(i, j, 0), INF);
				NF.addEdge(NF.S, getId(i, j, 0),
						max(0, chMap[c[i][j]] - chMap[b[i][j]]));
				NF.addEdge(getId(i, j, 0), NF.T,
						max(0, chMap[b[i][j]] - chMap[c[i][j]]));

				// Add edges for adjacent cells (W -> _B, _W -> B, INF)
				for (int k = 0; k < 4; k++)
				{
					int x = i + DIR[k][0], y = j + DIR[k][1];
					if (x < 0 || x >= N || y < 0 || y >= M)
						continue;
					NF.addEdge(getId(i, j, 0), getId(x, y, 1), INF);
					NF.addEdge(getId(i, j, 1), getId(x, y, 0), INF);
				}
			}
			else
			{
				sum += chMap[b[i][j]] + max(0, chMap[b[i][j]] - chMap[c[i][j]]);
				NF.addEdge(getId(i, j, 1), NF.T, chMap[b[i][j]]);
				NF.addEdge(getId(i, j, 0), getId(i, j, 1), INF);
				NF.addEdge(NF.S, getId(i, j, 0),
						max(0, chMap[b[i][j]] - chMap[c[i][j]]));
				NF.addEdge(getId(i, j, 0), NF.T,
						max(0, chMap[c[i][j]] - chMap[b[i][j]]));
			}

	return sum;
}

int SurroundingGame::maxScore(vector<string> cost, vector<string> benefit)
{
	int answer;
	prepare();
	answer = build(cost, benefit);
	answer -= NF.maxFlow();
	return answer;
}
