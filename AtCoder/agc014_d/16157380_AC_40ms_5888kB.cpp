#include <algorithm>
#include <cstring>
#include <cstdio>
#include <vector>
 
#define REDIRECT(x) freopen(x".in", "r", stdin), freopen(x".out", "w", stdout)
#define CLOSEALL() fclose(stdin), fclose(stdout)
 
using namespace std;
 
const int MAXN = 1e5 + 10;
 
int N;
bool vist[MAXN], noSolution;
vector <int> Adj[MAXN];
 
inline void addEdge(int u, int v)
{
	Adj[u].push_back(v), Adj[v].push_back(u);
}
 
void DFS(int cur, int pre)
{
	if(noSolution)
		return;
 
	// If it's a leaf, match it with its parent
	if(Adj[cur].size() == 1)
	{
		if(vist[pre])
			noSolution = true;
		vist[cur] = true;
		vist[pre] = true;
		return;
	}
 
	for(vector<int>::iterator itr = Adj[cur].begin(); itr != Adj[cur].end(); ++itr)
	{
		if(*itr == pre)
			continue;
		DFS(*itr, cur);
	}
 
	// If it's not matched
	if(!vist[cur])
	{
		// It's parent is used or its the root
		if(vist[pre] || pre == 0)
			noSolution = true;
		vist[cur] = true;
		vist[pre] = true;
		return;
	}
}
 
int main()
{
	//REDIRECT("blackwhite");
 
	int u, v;
	scanf("%d", &N);
	for(int i = 1; i < N; i++)
		scanf("%d%d", &u, &v),
		addEdge(u, v);
 
	for(int i = 1; i <= N; i++)
		if(Adj[i].size() > 1)
		{
			DFS(i, 0);
			break;
		}
 
	puts(noSolution ? "First" : "Second");
 
	CLOSEALL();
	return 0;
}