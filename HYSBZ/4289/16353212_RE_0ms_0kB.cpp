// BZOJ 4289 PA2012 Tax
#include <algorithm>
#include <cstring>
#include <cstdio>
#include <vector>
#include <queue>
using namespace std;

const int MAXN = 4e5 + 10;
const int MAXM = MAXN * 10;
typedef long long i64;

int N, M;
int T;
const int S = 0;

struct edge
{
	static int idCnt;
	int u, v;
	i64 w;
	int id;
	edge()
	{
		u = v = id = 0;
		w = 0;
	}
	edge(int _u, int _v, i64 _w, int _id)
	{
		u = _u, v = _v;
		w = _w;
		id = _id;
	}

	bool operator <(const edge & rhs) const
	{
		return w < rhs.w;
	}
};
int edge::idCnt = 0;

struct _edge
{
	int to;
	_edge * nxt;
	i64 w;
} E[MAXM];
typedef _edge * pEdge;

vector<edge> Adj[MAXN];
int allocCnt;
pEdge head[MAXN];

inline void addEdge(int u, int v, i64 w)
{
//	fprintf(stderr, "Adding edge : %d %d %lld\n", u, v, w);
	pEdge p = &E[allocCnt++];
	p->nxt = head[u], head[u] = p;
	p->w = w, p->to = v;
}

i64 dist[MAXN];
i64 dijkstra_Heap()
{
	memset(dist, 0x7F, sizeof dist);
	priority_queue<pair<i64, int>, vector<pair<i64, int> >, greater<pair<i64, int> > > PQ;
	dist[S] = 0, PQ.push(make_pair(0LL, S));

	while (!PQ.empty())
	{
		pair<i64, int> cur;
		cur = PQ.top(), PQ.pop();
		if (cur.first != dist[cur.second])
			continue;
		if (cur.second == T)
			return dist[T];

		for (pEdge e = head[cur.second]; e; e = e->nxt)
			if (dist[e->to] > dist[cur.second] + e->w)
			{
				dist[e->to] = dist[cur.second] + e->w;
				PQ.push(make_pair(dist[e->to], e->to));
			}
	}
	return -1;
}

int main()
{
	int u, v, w;
	scanf("%d%d", &N, &M);
	for (int i = 1; i <= M; i++)
	{
		scanf("%d%d%d", &u, &v, &w);
		Adj[u].push_back(edge(u, v, w, ++edge::idCnt));
		Adj[v].push_back(edge(v, u, w, ++edge::idCnt));
	}
	T = edge::idCnt + 1;

//	fputs("Adding edge phrase 1", stderr);
	for (int i = 1; i <= N; i++)
	{
		sort(Adj[i].begin(), Adj[i].end());

		for (vector<edge>::iterator itr = Adj[i].begin() + 1;
				itr != Adj[i].end(); ++itr)
			addEdge(itr->id, (itr - 1)->id, 0), addEdge((itr - 1)->id, itr->id,
					itr->w - (itr - 1)->w);
	}
//	fputs("Adding edge phrase 2", stderr);
	for (int i = 1; i <= N; i++)
	{
		int to, sz;
		for (vector<edge>::iterator itr = Adj[i].begin(); itr != Adj[i].end();
				++itr)
		{
			to = itr->v;
			sz = Adj[to].size();
			int pos = lower_bound(Adj[to].begin(), Adj[to].end(), *itr)
					- Adj[to].begin();
			if (pos > 0)
				addEdge(itr->id, Adj[to][pos - 1].id, itr->w);
			if (pos < sz)
				addEdge(itr->id, Adj[to][pos].id, Adj[to][pos].w);
		}
	}
//	fputs("Adding edge phrase 3", stderr);
	for (vector<edge>::iterator itr = Adj[1].begin(); itr != Adj[1].end();
			++itr)
		addEdge(S, itr->id, itr->w);
	for (vector<edge>::iterator itr = Adj[N].begin(); itr != Adj[N].end();
			++itr)
		addEdge(itr->id, T, 0);
//	fflush (stderr);
	printf("%lld\n", dijkstra_Heap());

	return 0;
}

