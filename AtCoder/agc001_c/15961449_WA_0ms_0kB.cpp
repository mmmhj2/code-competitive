#include <cstdio>
#include <vector>

#define REDIRECT(x) freopen(x".in", "r", stdin), freopen(x".out", "w", stdout);
#define CLOSEALL() fclose(stdin), fclose(stdout)

using namespace std;

template <class T>
T emplaceMin(T & x, const T & y)
{
	if(x > y)
		x = y;
	return x;
}

const int MAXN = 2000 + 5;

vector<int> Adj[MAXN];
int dep[MAXN];
int N, K;
int ans (0x7F7F7F7F);

void DFS(int cur, int fa, int deep)
{
	dep[cur] = deep;
	for(vector<int>::iterator itr = Adj[cur].begin(); itr != Adj[cur].end(); ++itr)
		if(*itr != fa)
			DFS(*itr, cur, deep + 1);
}

int main()
{
	REDIRECT("shorten");

	int u, v;

	scanf("%d%d", &N, &K);
	for (int i = 1; i < N; i++)
		scanf("%d%d", &u, &v), Adj[u].push_back(v), Adj[v].push_back(u);

	if((K & 1) == 0)			// If K is even then the tree can be halved
		for(int i = 1; i <= N; i++)
		{
			int nans = 0;
			DFS(i, 0, 0);
			for(int k = 1; k <= N; k++)
				nans += (dep[k] > (K / 2));
			emplaceMin(ans, nans);
		}
	else						// If K is odd things will be complicated
		for(int i = 1; i <= N; i++)					// Raise two nodes as one root, then the tree can be halved
			for(vector<int>::iterator itr = Adj[i].begin(); itr != Adj[i].end(); ++itr)
			{
				int nans = 0;
				DFS(i, *itr, 0);
				DFS(*itr, i, 0);
				for(int k = 1; k <= N; k++)
					nans += (dep[k] > (K / 2));
				emplaceMin(ans, nans);
			}

	printf("%d\n", ans);

	CLOSEALL();
	return 0;
}
