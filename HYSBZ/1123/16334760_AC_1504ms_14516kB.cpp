// bzoj 1123 BLO
#include <algorithm>
#include <cstdio>
#include <vector>
using namespace std;
typedef long long i64;
const int MAXN = 100000 + 10;

int N, M;
vector <int> Adj[MAXN];

bool isCutPnt[MAXN];

int tmStp, rootSon;
int LOW[MAXN], DFN[MAXN];
int chSiz[MAXN];

i64 dpOnTree[MAXN];

void DFS(int cur, int fa)
{
	int chSum = 0;
	chSiz[cur] = 1;
	LOW[cur] = DFN[cur] = ++tmStp;

	for(vector<int>::iterator itr = Adj[cur].begin(); itr != Adj[cur].end(); ++itr)
	{
		const int & to = *itr;
		if(!DFN[to])
		{
			DFS(to, cur);
			chSiz[cur] += chSiz[to];
			LOW[cur] = min(LOW[cur], LOW[to]);
			/*
			if(LOW[to] >= DFN[cur])
				if(fa != 0)
					isCutPnt[cur] = true;
				else
					rootSon++;
			*/
			if(LOW[to] >= DFN[cur])
				dpOnTree[cur] += 1LL * chSum * chSiz[to],
				chSum += chSiz[to];
		}
		else if(to != cur)
			LOW[cur] = min(LOW[cur], DFN[to]);
	}
	dpOnTree[cur] += 1LL * chSum * (N - chSum - 1);
}

int main()
{
	scanf("%d%d", &N, &M);
	for(int i = 1; i <= M; i++)
	{
		int u, v;
		scanf("%d%d", &u, &v);
		Adj[u].push_back(v);
		Adj[v].push_back(u);
	}

	DFS(1, 0);
//	if(rootSon >= 2)
//		isCutPnt[1] = true;
	for(int i = 1; i <= N; i++)
		printf("%lld\n", (dpOnTree[i] + N - 1) * 2);
	return 0;
}
