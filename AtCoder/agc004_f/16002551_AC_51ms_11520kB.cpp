#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

const int MAXN = 100000 + 5;

int N, M;
vector<int> Adj[MAXN];
int fa[MAXN], col[MAXN], dep[MAXN];

bool hasCircle;
int circA, circB;

inline void addEdge(int u, int v)
{
	Adj[u].push_back(v);
	Adj[v].push_back(u);
}

void DFS(int cur)
{
	dep[cur] = dep[fa[cur]] + 1;
	col[cur] = (dep[cur] & 1 ? 1 : -1);

	for (int to : Adj[cur])
	{
		if (to == fa[cur])
			continue;
		if (dep[to])
		{
			if (!hasCircle)
				circA = cur, circB = to, hasCircle = true;
		}
		else
			fa[to] = cur, DFS(to), col[cur] += col[to];
	}
}

int solveAcyclic()
{
	if (col[1])
		return -1;

	int ret = 0;
	for (int i = 1; i <= N; i++)
		ret += abs(col[i]);
	return ret;
}

int solveOddCircle()
{
	if (col[1] & 1)
		return -1;

	int delta = -col[1] / 2, ret = abs(delta), cur;
	cur = circA;
	while (cur)
		col[cur] += delta, cur = fa[cur];
	cur = circB;
	while (cur)
		col[cur] += delta, cur = fa[cur];

	for (int i = 1; i <= N; i++)
		ret += abs(col[i]);
	return ret;
}

int solveEvenCircle()
{
	if (col[1])
		return -1;

	int circle[MAXN] =
	{ 0 }, top = 0;
	for (int cur = circA; cur != circB; cur = fa[cur])
		circle[++top] = col[cur], dep[cur] = 0;

	int mid = (top + 1) >> 1, delta, ret;
	nth_element(&circle[1], &circle[mid], &circle[top + 1]);
	delta = (circle[mid]), ret = abs(delta);

	for (int i = 1; i <= N; i++)
		if (dep[i])
			ret += abs(col[i]);
	for (int i = 1; i <= top; i++)
		ret += abs(circle[i] - delta);
	return ret;
}

int main()
{
	//printf("%d %d\n", 1 & 1, -1 & 1);
	fflush(stdout);

	scanf("%d%d", &N, &M);
	for (int i = 1; i <= M; i++)
	{
		int u, v;
		scanf("%d%d", &u, &v);
		addEdge(u, v);
	}

	DFS(1);

	if (!hasCircle)
		printf("%d\n", solveAcyclic());
	else
	{
		if ((dep[circA] - dep[circB] + 1) & 1)
			printf("%d\n", solveOddCircle());
		else
			printf("%d\n", solveEvenCircle());
	}

	return 0;
}
