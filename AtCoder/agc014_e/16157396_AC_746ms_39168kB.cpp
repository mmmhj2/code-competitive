#include <functional>
#include <algorithm>
#include <iostream>
#include <numeric>
#include <queue>
#include <map>
#include <set>
using namespace std;
 
typedef pair<int, int> pii;
const int MAXN = 1e5 + 10;
 
int N;
int fa[MAXN];
set<int> Adj[MAXN];
queue<pii> dualEdges;
map<pii, int> edgeCnt;
 
int find(int x)
{
	if (x == fa[x])
		return x;
	return fa[x] = find(fa[x]);
}
 
inline void addEdge(int u, int v)
{
	Adj[u].insert(v), Adj[v].insert(u);
	if (u > v)
		swap(u, v);
	if (++edgeCnt[make_pair(u, v)] == 2)
		dualEdges.emplace(u, v);
}
 
int main()
{
	int u, v;
	cin >> N;
 
	for (int i = 1; i <= 2 * N - 2; i++)
		cin >> u >> v, addEdge(u, v);
	iota(&fa[0], &fa[N + 1], 0);
 
	for (int i = 1; i < N; i++)
	{
		int x = 0, y = 0;
		do
		{
			if (dualEdges.empty())
			{
				puts("NO");
				return 0;
			}
			tie(x, y) = dualEdges.front();
			dualEdges.pop();
			x = find(x), y = find(y);
		} while (x == y);
 
		if (Adj[x].size() > Adj[y].size())
			swap(x, y);
		fa[x] = y, Adj[x].erase(y), Adj[y].erase(x);
		edgeCnt.erase(make_pair(min(x, y), max(x, y)));
 
		for(int z : Adj[x])
		{
			z = find(z);
			edgeCnt[make_pair(min(x, z), max(x, z))]--;
			if(z == y)
				continue;
			Adj[z].erase(x);
			addEdge(y, z);
		}
	}
 
	puts("YES");
 
	return 0;
}