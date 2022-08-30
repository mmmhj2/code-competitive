#include <iostream>
#include <vector>
using namespace std;

const int MAXN = 1e5 + 10;

vector <int> Adj[MAXN];
int N, K;
int fa[MAXN], dep[MAXN];
int answer;

void DFS(int cur)
{
	dep[cur] = 1;
	for(int x : Adj[cur])
		DFS(x), dep[cur] = max(dep[cur], dep[x] + 1);

	if(fa[cur] != 1 && dep[cur] == K)
		answer++, dep[cur] = 0;
}

int main()
{
	cin >> N >> K;
	cin >> fa[1];

	if(fa[1] != 1)	//Loop
		fa[1] = 1, answer ++;

	for(int i = 2; i <= N; i++)
	{
		cin >> fa[i] ;
		Adj[fa[i]].push_back(i);
	}
	DFS(1);

	cout << answer << endl ;
}

