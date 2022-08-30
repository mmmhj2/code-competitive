#include <cstring>
#include <cstdio>
#include <vector>
using namespace std;

const int MAXN = 5000 + 10;
const int MAXM = 10000 + 10;

int F, R;

namespace adjTable
{
struct edge
{
	int to;
	edge * nxt;
} E[MAXM * 2];

int allocCnt;
edge * head[MAXN];

void clearEdge()
{
	allocCnt = 0;
	memset(head, 0x00, sizeof head);
}

void addEdge(int u, int v)
{
	edge * pEdge;
	pEdge = &E[allocCnt++];
	pEdge->to = v, pEdge->nxt = head[u], head[u] = pEdge;
	pEdge = &E[allocCnt++];
	pEdge->to = u, pEdge->nxt = head[v], head[v] = pEdge;
}

};

namespace Algo_tarjan
{
using namespace adjTable;
int tmStp;
int DFN[MAXN], LOW[MAXN];
bool vist[MAXM * 2];
int lowCnt[MAXN];

void initialize()
{
	tmStp = 0;
	memset(DFN, 0x00, sizeof DFN);
	memset(LOW, 0x00, sizeof LOW);
	memset(vist, 0x00, sizeof vist);
	memset(lowCnt, 0x00, sizeof lowCnt);
}

void tarjan(int cur, int fa)
{
	DFN[cur] = LOW[cur] = ++tmStp;

	for(edge * e = head[cur]; e; e = e->nxt)
	{
		int edgeId = e - E;
		const int & to = e->to;
		if(vist[edgeId])
			continue;
		vist[edgeId] = vist[edgeId ^ 1] = true;

		if(!DFN[to])
			tarjan(to, cur),
			LOW[cur] = min(LOW[cur], LOW[to]);
		else
			LOW[cur] = min(LOW[cur], DFN[to]);
	}
}

int process()
{
	for(int i = 1; i <= F; i++)
		if(!DFN[i])
			tarjan(i, 0);
	for(int i = 1; i <= F; i++)
		for(edge * e = head[i]; e; e = e->nxt)
			if(LOW[i] != LOW[e->to])
				lowCnt[LOW[e->to]]++;

	int answer = 0;
	for(int i = 1; i <= F; i++)
		answer += (lowCnt[i] == 1);
	return answer;
}

};


int main()
{
	int u, v;
	scanf("%d %d", &F, &R);
	for(int i = 1; i <= R; i++)
		scanf("%d %d", &u, &v), adjTable::addEdge(u, v);
	printf("%d\n", (Algo_tarjan::process() + 1) / 2);
	return 0;
}
