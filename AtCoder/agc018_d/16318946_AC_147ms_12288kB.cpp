#include <bits/stdc++.h>
using namespace std;
typedef long long i64;
const int MAXN = 100000 + 10;

int N;
i64 sum;
int answer;
vector <pair<int, int>>Adj[MAXN];

inline void addEdge(int u, int v, int w)
{
	Adj[u].emplace_back(v, w);
	Adj[v].emplace_back(u, w);
}

int centroid, val[MAXN], siz[MAXN], mx[MAXN];

void DFS(int cur, int fa)
{
	siz[cur] = 1, mx[cur] = 0;
	for(auto x : Adj[cur])
		if(x.first != fa)
		{
			val[x.first] = x.second;
			DFS(x.first, cur);
			siz[cur] += siz[x.first];
			mx[cur] = max(mx[cur], siz[x.first]);
		}

	mx[cur] = max(mx[cur], N - siz[cur]);
	if(mx[cur] * 2 < N)
		centroid = cur;
	if(siz[cur] * 2 == N)
		answer = val[cur];
	sum += 2LL * min(siz[cur], N - siz[cur]) * val[cur];
}

int main()
{
	int u, v, w;
	answer = 0x7F7F7F7F;
	cin >> N ;
	for(int i = 1; i < N; i++)
		cin >> u >> v >> w, addEdge(u, v, w);

	DFS(1, 0);

	if(answer >= 0x7F7F7F7F)
		for(auto x : Adj[centroid])
			answer = min(answer, x.second);

	cout << sum - answer << endl ;
}
