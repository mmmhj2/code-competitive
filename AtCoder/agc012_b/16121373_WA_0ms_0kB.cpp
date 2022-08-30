#include <cstdio>
#include <vector>

#define REDIRECT(x) freopen(x".in", "r", stdin), freopen(x".out", "w", stdout)
#define CLOSEALL() fclose(stdin), fclose(stdout)
#define eprintf(...) fprintf(stderr, ##__VA_ARGS__)

using namespace std;

const int MAXN = 1e5 + 10;

int u, v;
int N, M, Q;
vector <int> Adj[MAXN];
int color[MAXN];
int V[MAXN], D[MAXN], C[MAXN];

bool vist[MAXN][11];

void solve(int cur, int dep, int col)
{
	if(vist[cur][dep] || dep < 0)
		return;
	vist[cur][dep] = true;

	if(color[cur] == 0)
		color[cur] = col;

	for(vector<int>::iterator itr = Adj[cur].begin(); itr != Adj[cur].end(); ++itr)
		solve(*itr, dep - 1, col);
	solve(cur, dep-1, col);

}

int main()
{
	REDIRECT("splatter");

	scanf("%d%d", &N, &M);
	for(int i = 1; i <= M; i++)
		scanf("%d%d", &u, &v), Adj[u].push_back(v), Adj[v].push_back(u);

	scanf("%d", &Q);
	for(int i = Q; i >= 1; i--)
		scanf("%d%d%d", &V[i], &D[i], &C[i]);
	for(int i = 1; i <= Q; i++)
		solve(V[i], D[i], C[i]);

	for(int i = 1; i <= N; i++)
		printf("%d\n", color[i]);

	CLOSEALL();
	return 0;
}
