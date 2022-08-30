#include <iostream>
#include <vector>
using namespace std;
typedef long long i64;
const int MAXN = 2e5 + 10;

int N;
vector<int> Adj[MAXN];
int sz[MAXN], Lo[MAXN], mx1st[MAXN], mx2nd[MAXN];
char color[MAXN];
i64 answer;

inline void addEdge(int u, int v)
{
	Adj[u].push_back(v);
	Adj[v].push_back(u);
}

void DFS(int cur, int fa = 0)
{
	sz[cur] = (color[cur] == '1');
	Lo[cur] = (sz[cur] ? 0 : 0x7F7F7F7F);

	for (const int & to : Adj[cur])
	{
		if (to == fa)
			continue;
		DFS(to, cur);

		int tmp = mx1st[to] + 1;
		if (tmp > mx1st[cur])
			mx2nd[cur] = mx1st[cur], mx1st[cur] = tmp;
		else
			mx2nd[cur] = max(mx2nd[cur], tmp);

		if (sz[to])
			sz[cur] += sz[to], Lo[cur] = min(Lo[cur], tmp);
	}
}

void solve(int cur, int fa = 0)
{
	if (fa)
	{
		int tmp = (mx1st[fa] == mx1st[cur] + 1 ? mx2nd[fa] : mx1st[fa]) + 1;
		if(tmp > mx1st[cur])
			mx2nd[cur] = mx1st[cur], mx1st[cur] = tmp;
		else
			mx2nd[cur] = max(mx2nd[cur], tmp);
		if(sz[1] - sz[cur])
			Lo[cur] = min(Lo[cur], tmp);
	}

	int delta = min(mx2nd[cur] + 1, mx1st[cur] - 1) - Lo[cur] + 1;
	if(delta > 0)
		answer += delta;

	for(const int & to : Adj[cur])
		if(to != fa)
			solve(to, cur);
}

int main()
{
	int u, v;
	ios::sync_with_stdio(false), cin.tie(nullptr);

	cin >> N ;
	for(int i = 1; i < N; i++)
		cin >> u >> v , addEdge(u, v);
	cin >> (color + 1);

	DFS(1), solve(1);

	cout << answer + 1 << endl ;

	return 0;
}
