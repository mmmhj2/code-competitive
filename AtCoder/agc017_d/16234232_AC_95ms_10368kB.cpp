#include <bits/stdc++.h>
using namespace std;
typedef long long i64;
const int MAXN = 100000 + 10;

int N;
vector <int> Adj[MAXN];

int DFS(int cur, int fa)
{
	int SG = 0;

	for(const int & x : Adj[cur])
		if(x != fa)
			SG ^= (1 + DFS(x, cur));

	return SG;
}

int main()
{
	cin >> N ;
	for(int i = 1; i < N; i++)
	{
		int u, v;
		cin >> u >> v ;
		Adj[u].push_back(v);
		Adj[v].push_back(u);
	}

	cout << (DFS(1, 0) == 0 ? "Bob" : "Alice") << endl ;

	return 0;
}

