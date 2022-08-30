// BZOJ 4479 [Jsoi2013]吃货jyy
#include <algorithm>
#include <cstring>
#include <cstdio>
#include <queue>
using namespace std;

const int MAXN = 13 + 2;
const int MAXSTATE = 1594323 + 10;

typedef struct edge * pEdge;
struct edge
{
	static int eCnt;

	int to, w;
	pEdge nxt;
} E[MAXN * 10];
int edge::eCnt = 0;
pEdge head[MAXN];

int N, M;
int dis[MAXN][MAXN];
int pow_2[MAXN], pow_3[MAXN];

void addEdge(int u, int v, int w)
{
	pEdge p;
	p = &E[++edge::eCnt];
	p->nxt = head[u], head[u] = p;
	p->to = v, p->w = w;

	p = &E[++edge::eCnt];
	p->nxt = head[v], head[v] = p;
	p->to = u, p->w = w;
}

void Floyd()
{
	for (int k = 1; k <= N; k++)
		for (int i = 1; i <= N; i++)
			for (int j = 1; j <= N; j++)
				dis[i][j] = min(dis[i][j], dis[i][k] + dis[k][j]);
}

int g[10000], f[MAXSTATE];

void prepareDP()
{
	memset(g, 0x3F, sizeof g);
	g[0] = 0;
	for (int i = 0; i < pow_2[N]; i++)
		for (int j = 1; j <= N; j++)
			if (!(i & pow_2[j - 1]))
				for (int k = j + 1; k <= N; k++)
					if (!(i & pow_2[k - 1]))
						g[i ^ pow_2[j - 1] ^ pow_2[k - 1]] = min(
								g[i ^ pow_2[j - 1] ^ pow_2[k - 1]],
								g[i] + dis[j][k]);
}

void runDP()
{
	int a[MAXN] =
	{ 0 };
	queue<int> Q;
	memset(f, 0x3F, sizeof f);
	f[2] = 0, Q.push(2);

	while (!Q.empty())
	{
		int s = Q.front(), tot = 0;
		Q.pop();

		for (int i = 1; i <= N; i++)
			if (s / pow_3[i - 1] % 3 > 0)
				a[++tot] = i;

		for (int i = 1; i <= N; i++)
			if (s / pow_3[i - 1] % 3 == 0)
			{
				for (pEdge p = head[i]; p; p = p->nxt)
					if (s / pow_3[p->to - 1] % 3 > 0)
					{
						int s1 = s + pow_3[i - 1] * 2;
						if (f[s] >= f[s1])
							continue;
						if (f[s1] == 0x3F3F3F3F)
							Q.push(s1);
						f[s1] = f[s];
					}

				for (int j = 1; j <= tot; j++)
				{
					int s1 = s + pow_3[i - 1];
					s1 += (s / pow_3[a[j] - 1] % 3 == 1) ?
							pow_3[a[j] - 1] : -pow_3[a[j] - 1];
					if (f[s] + dis[i][a[j]] >= f[s1])
						continue;
					if (f[s1] == 0x3F3F3F3F)
						Q.push(s1);
					f[s1] = f[s] + dis[i][a[j]];
				}
			}

	}

}

int deg[MAXN];
int main()
{
	scanf("%d%d", &N, &M);

	pow_2[0] = pow_3[0] = 1;
	for (int i = 1; i <= N; i++)
		pow_2[i] = pow_2[i - 1] * 2, pow_3[i] = pow_3[i - 1] * 3;
	memset(dis, 0x3F, sizeof dis);

	for (int i = 1; i <= M; i++)
	{
		int u, v, w;
		scanf("%d%d%d", &u, &v, &w);
		addEdge(u, v, w);
		dis[u][v] = dis[v][u] = min(dis[u][v], w);
		deg[u]++, deg[v]++;
	}

	scanf("%d", &M);
	for (int i = 1; i <= M; i++)
	{
		int u, v, w;
		scanf("%d%d%d", &u, &v, &w);
		dis[u][v] = dis[v][u] = min(dis[u][v], w);
	}

	Floyd();
	prepareDP();
	runDP();
	// Calculate final answer

	int answer = 0x3F3F3F3F;
	for(int s = 0; s < pow_3[N]; s++)
	{
		bool flag = false;
		for(int i = 1; i <= N; i++)
			if(head[i] && !(s / pow_3[i-1] % 3))
			{
				flag = true;
				break;
			}
		if(flag)
			continue;

		int now = s, s1 = 0;
		for(int i = 1; i <= N; i++)
			if(deg[i] & 1)
				now += (s / pow_3[i-1] % 3 == 1) ? pow_3[i-1] : -pow_3[i-1];
		for(int i = 1; i <= N; i++)
			if(now / pow_3[i-1] % 3 == 1)
				s1 ^= pow_2[i-1];
		answer = min(answer, f[s] + g[s1]);
	}

	for(int i = 1; i <= edge::eCnt; i += 2)
		answer += E[i].w;

	printf("%d\n", answer);
	return 0;
}
