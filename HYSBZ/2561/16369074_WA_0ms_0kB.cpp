// BZOJ 2561 最小生成树
#include <algorithm>
#include <cstring>
#include <cstdio>
#include <vector>
using namespace std;

const int MAXN = 20000 + 10;
const int MAXM = 200000 + 10;

typedef struct _edge
{
	int to, cap;
	_edge * nxt;
	_edge * bak;
	static int eCnt;
} edge, *pEdge;

int maxDist;
int N, M;
int S, T, W;
edge E[MAXM * 4];
pEdge head[MAXN];
int _edge::eCnt = 0;

void addEdge(int u, int v, int w)
{

	pEdge p1 = &E[_edge::eCnt++];
	pEdge p2 = &E[_edge::eCnt++];

	p1->to = v, p1->cap = w;
	p1->nxt = head[u], head[u] = p1;
	p2->to = u, p2->cap = 0;
	p2->nxt = head[v], head[v] = p2;

	p1->bak = p2, p2->bak = p1;
}

int dist[MAXN], disCnt[MAXN];
int findAug(int cur, int maxFlow)
{
	int sum(0), minDist(maxDist), delta;
	if (cur == T)
		return maxFlow;

	for (pEdge p = head[cur]; p; p = p->nxt)
		if (p->cap > 0)
		{
			//fprintf(stderr, "To %d , capacity %d\n", p->to, p->cap);
			if (dist[cur] == dist[p->to] + 1)
			{
				delta = findAug(p->to, min(maxFlow - sum, p->cap));
				p->cap -= delta;
				p->bak->cap += delta;
				sum += delta;

				if (dist[S] > maxDist)
					return sum;
				if (sum == maxFlow)
					break;
			}
			minDist = min(minDist, dist[p->to]);
		}

	if (sum == 0)
	{
		disCnt[dist[cur]]--;
		if (disCnt[dist[cur]] <= 0)
			dist[S] = maxDist + 1;
		dist[cur] = minDist + 1;
		disCnt[dist[cur]]++;
	}
	return sum;
}

int ISAP()
{
	memset(disCnt, 0x00, sizeof disCnt);
	memset(dist, 0x00, sizeof dist);

	int flow = 0;
	disCnt[S] = maxDist + 1;
	while (dist[S] <= maxDist)
		flow += findAug(S, 0x7F7F7F7F);
	return flow;
}

vector <pair<pair<int,int>,int> > vec;
int main()
{
	int u, v, w;
	scanf("%d%d", &N, &M);
	for(int i = 0; i < M; i++)
		scanf("%d%d%d", &u, &v, &w), vec.push_back(make_pair(make_pair(u, v), w));
	scanf("%d%d%d", &S, &T, &W);
	maxDist = N ;

	memset(head, 0x00, sizeof head), edge::eCnt = 0;
	for(int i = 0; i < M; i++)
		if(vec[i].second < W)
			addEdge(vec[i].first.first, vec[i].first.second, 1),
			addEdge(vec[i].first.second, vec[i].first.first, 1);
	int f1 = ISAP();

	memset(head, 0x00, sizeof head), edge::eCnt = 0;
	for(int i = 0; i < M; i++)
		if(vec[i].second > W)
			addEdge(vec[i].first.first, vec[i].first.second, 1),
			addEdge(vec[i].first.second, vec[i].first.first, 1);
	int f2 = ISAP();
	printf("%d\n", f1 + f2);
	return 0;
}
