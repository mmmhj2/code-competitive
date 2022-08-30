#include <cstring>
#include <cstdio>
#include <queue>
using std::deque;

const int MAXE = 5000 + 10;
const int MAXN = 1500 + 10;
const int MOD  = 1000000007;
typedef long long i64;

struct edge;
typedef edge * pEdge;
struct edge
{
	int from, to, w;
	pEdge nxt;
}E[MAXE];

int N, M;
int allocCnt;

pEdge head[MAXN];

inline void addEdge(int u, int v, int w)
{
	pEdge cur = &E[allocCnt++];
	cur->nxt = head[u];
	cur->from = u, cur->to = v, cur->w = w;
	head[u] = cur;
}

int dist[MAXN];
bool inQueue[MAXN];
void SPFA(int s)
{
	memset(dist, 0x7F, sizeof dist);
	memset(inQueue, 0x00, sizeof inQueue);
	deque <int> Q;

	dist[s] = 0, inQueue[s] = true;
	Q.push_back(s);

	while(!Q.empty())
	{
		s = Q.front(), Q.pop_front();
		inQueue[s] = false;

		for(pEdge e = head[s]; e; e = e->nxt)
			if(dist[e->to] > dist[s] + e->w)
			{
				dist[e->to] = dist[s] + e->w;
				if(!inQueue[e->to])
				{
					inQueue[e->to] = true;
					if(Q.empty())
						Q.push_back(e->to);
					else
					{
						if(dist[e->to] > dist[Q.front()])
							Q.push_back(e->to);
						else
							Q.push_front(e->to);
					}
				}
			}
	}

}

bool vist[MAXN];
int inCnt[MAXN], dp1[MAXN], dp2[MAXN];
i64 answer[MAXE];

void getCnt(int x)
{
	vist[x] = true;
	for(pEdge e = head[x]; e; e = e->nxt)
	{
		if(dist[x] + e->w != dist[e->to])
			continue;
		inCnt[e->to] ++;
		if(!vist[e->to])
			getCnt(e->to);
	}
}

void DFS1(int x)
{
	for(pEdge e = head[x]; e; e = e->nxt)
	{
		if(dist[e->to] != dist[x] + e->w)
			continue;
		inCnt[e->to]--;
		dp1[e->to] = (dp1[e->to] + dp1[x]) % MOD;
		if(inCnt[e->to] == 0)
			DFS1(e->to);
	}
}

void DFS2(int x)
{
	dp2[x] = 1;
	for(pEdge e = head[x]; e; e = e->nxt)
	{
		if(dist[e->to] != dist[x] + e->w)
			continue;
		if(dp2[e->to] != 0)
			continue;
		DFS2(e->to);
		dp2[x] = (dp2[x] + dp2[e->to]) % MOD ;
	}
}

int main()
{
	int u, v, w;

	scanf("%d%d", &N, &M);
	for (int i = 0; i < M; i++)
		scanf("%d%d%d", &u, &v, &w),
		addEdge(u, v, w);

	for(int i = 1; i <= N; i++)
	{
		memset(dp1, 0x00, sizeof dp1);
		memset(dp2, 0x00, sizeof dp2);
		memset(vist, 0x00, sizeof vist);
		dp1[i] = 1;
		SPFA(i);
		getCnt(i);
		DFS1(i), DFS2(i);

		for (int j = 0; j < M; j++)
			if(dist[E[j].to] == dist[E[j].from] + E[j].w)
				answer[j] = (answer[j] + (1LL * dp1[E[j].from] * dp2[E[j].to] % MOD)) % MOD;
	}

	for(int i = 0; i < M; i++)
		printf("%lld\n", answer[i]);

	return 0;
}
