#include <algorithm>
#include <cstdio>
#include <vector>
using namespace std;

const int MAXN = 200000 + 5;

int N, X, Y, answer;
vector<int> rAdj[MAXN], bAdj[MAXN];
int fa[MAXN], dep[MAXN];

class noSolution : std::exception
{

};

void findBlueFa(int cur, int pre) noexcept
{
	fa[cur] = pre;

	for (int to : bAdj[cur])
		if (to != pre)
			dep[to] = dep[cur] + 1, findBlueFa(to, cur);
}

bool isShortPath(int u, int v) noexcept
{
	if (dep[u] < dep[v])
		swap(u, v);

	for (int len = 0; len < 2; len++)
	{
		if (u == v)
			break;

		if (dep[u] < dep[v])
			v = fa[v];
		else
			u = fa[u];
	}
	return (u == v);
}

void DFS(int cur, int pre = -1, int constrain = 0) //throw (solution)
{
	answer = max(answer, dep[cur]);
	if(dep[cur] <= constrain)
		return;

	for(int to : rAdj[cur])
	{
		if(to == pre)
			continue;
		if(!isShortPath(cur, to))
			throw noSolution();
		DFS(to, cur, constrain + 1);
	}
}

int main()
{
	int u, v;
	scanf("%d%d%d", &N, &X, &Y);
	for(int i = 1; i < N; i++)
		scanf("%d%d", &u, &v), rAdj[u].push_back(v), rAdj[v].push_back(u);
	for(int i = 1; i < N; i++)
		scanf("%d%d", &u, &v), bAdj[u].push_back(v), bAdj[v].push_back(u);

	findBlueFa(Y, 0);

	try
	{
		DFS(X);
		printf("%d\n", answer * 2);
	}
	catch (noSolution & x)
	{
		printf("-1\n");
	}

	return 0;
}
