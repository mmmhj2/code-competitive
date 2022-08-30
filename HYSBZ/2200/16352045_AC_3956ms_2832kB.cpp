#include <cstdio>
#include <queue>
using std::deque;

const int MAXE = 50000 * 3 + 10;
const int MAXN = 25000 + 10;

int readInt()
{
	int ret = 0, sgn = 1;
	char c;

	do
	{
		c = getchar();
		if (c == '-')
			sgn *= -1;
	} while (c < '0' || '9' < c);

	while ('0' <= c && c <= '9')
		ret = ret * 10 + c - '0', c = getchar();

	return ret * sgn;
}

struct edge;
typedef edge * pEdge;
struct edge
{
	int to, w;
	pEdge nxt;
}E[MAXE];

int T, R, P, S;
int allocCnt;

pEdge head[MAXN];

inline void addEdge(int u, int v, int w)
{
	pEdge cur = &E[allocCnt++];
	cur->nxt = head[u];
	cur->to = v, cur->w = w;
	head[u] = cur;
}

int dist[MAXN];
bool inQueue[MAXN];
void SPFA(int s)
{
	for(int i = 1; i <= T; i++)
		dist[i] = 0x7F7F7F7F, inQueue[i] = false;
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

int main()
{
	int u, v, w;
	T = readInt(), R = readInt(), P = readInt(), S = readInt();

	for(int i = 1; i <= R; i++)
	{
		u = readInt(), v = readInt(), w = readInt();
		addEdge(u, v, w);
		addEdge(v, u, w);
	}
	for(int i = 1; i <= P; i++)
	{
		u = readInt(), v = readInt(), w = readInt();
		addEdge(u, v, w);
	}
	SPFA(S);

	for(int i = 1; i <= T; i++)
		if(dist[i] >= 0x7F7F7F7F)
			puts("NO PATH");
		else
			printf("%d\n", dist[i]);

	return 0;
}
