// CF #1000 E We Need More Bosses
#include <iostream>
#include <cstring>
#include <cassert>
#include <vector>
#include <stack>
using namespace std;

const int MAXN = 3e5 + 10;


int N, M;
vector<int> Adj[MAXN];
vector<int> newAdj[MAXN];

int tmStp;
int DFN[MAXN], LOW[MAXN];
int SCCid[MAXN];
int SCCcnt;
stack<int> stk;

void tarjan(int cur, int fa)
{
	DFN[cur] = LOW[cur] = ++tmStp;
	stk.push(cur);

	for(const auto & x : Adj[cur])
	{
		if(!DFN[x])
		{
			tarjan(x, cur);
			LOW[cur] = min(LOW[cur], LOW[x]);
		}
		else if(x != fa)
			LOW[cur] = min(LOW[cur], DFN[x]);
	}

	if(LOW[cur] == DFN[cur])
	{
		SCCcnt++;
		int x;
		do
		{
			x = stk.top(), stk.pop();
			SCCid[x] = SCCcnt;
		}while(x != cur);
	}

}

int dist[MAXN];
void DFS(int u, int fa)
{
	dist[u] = dist[fa] + 1;
	for(const auto & x : newAdj[u])
		if(x != fa)
			DFS(x, u);
}

int main()
{
	int u, v;
	cin >> N >> M;
	for (int i = 1; i <= M; i++)
		cin >> u >> v, Adj[u].push_back(v), Adj[v].push_back(u);

	tarjan(1, 0);

	int centroid = 1, answer = 0;
	for(int i = 1; i <= N; i++)
		for(const auto & x : Adj[i])
			if(SCCid[i] != SCCid[x])
				newAdj[SCCid[i]].push_back(SCCid[x]);

	DFS(1, 0);
	for(int i = 1; i <= SCCcnt; i++)
		if(dist[i] > dist[centroid])
			centroid = i;
	DFS(centroid, 0);
	for(int i = 1; i <= SCCcnt; i++)
		answer = max(answer, dist[i] - 1);

	cout << answer << endl ;

	return 0;
}
