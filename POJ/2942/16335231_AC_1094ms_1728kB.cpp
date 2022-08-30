// POJ 2942 Knights of the Round Table
#include <algorithm>
#include <cstring>
#include <cstdio>
#include <vector>
#include <queue>
#include <stack>
using namespace std;

const int MAXN = 1000 + 5;

int N, M;
bool isHatred[MAXN][MAXN];

int tmStp, blkCnt;
int DFN[MAXN], LOW[MAXN];
stack<pair<int, int> > blkStk;

vector<int> Adj[MAXN];
vector<int> DCC[MAXN];

bool isBicolorale;
short int color[MAXN];
bool isOk[MAXN];

void initialize()
{
	while(!blkStk.empty())
		blkStk.pop();

	tmStp = 0, blkCnt = 0;
	memset(DFN, 0x00, sizeof DFN);
	memset(LOW, 0x00, sizeof LOW);
	memset(isOk, 0x00, sizeof isOk);
	memset(isHatred, 0x00, sizeof isHatred);
	for(int i = 1; i <= N; i++)
		Adj[i].clear();
}

void beginBicolor()
{
	isBicolorale = true;
	memset(color, 0x00, sizeof color);
	for(int i = 1; i <= N; i++)
		DCC[i].clear();
}

void bicoloring(int cur, int fa)
{
	if(fa <= 0)
		color[cur] = 1;
	else
		color[cur] = ~color[fa];

	for(vector<int>::iterator itr = DCC[cur].begin(); itr != DCC[cur].end(); ++itr)
		if(color[*itr] == 0)
			bicoloring(*itr, cur);
		else if(color[*itr] != ~color[cur])
			isBicolorale = false;

}

void buildComplementary()
{
	for (int i = 1; i <= N; i++)
		for (int j = i + 1; j <= N; j++)
			if (!isHatred[i][j])
				Adj[i].push_back(j), Adj[j].push_back(i);//, fprintf(stderr, "Add edge : %d %d\n", i, j);
}

void tarjan(int cur, int fa)
{
	DFN[cur] = LOW[cur] = ++tmStp;

	for (vector<int>::iterator itr = Adj[cur].begin(); itr != Adj[cur].end();
			++itr)
	{
		const int & to = *itr;

		if (!DFN[to])
		{
			blkStk.push(make_pair(cur, to));
			tarjan(to, cur);
			LOW[cur] = min(LOW[cur], LOW[to]);

			if (LOW[to] >= DFN[cur])
			{
//				fprintf(stderr, "Found new block\n");
				beginBicolor();
				pair<int, int> tmp;
				do
				{
					tmp = blkStk.top(), blkStk.pop();
//					fprintf(stderr, "Edge between %d and %d\n", tmp.first,
//							tmp.second);
					DCC[tmp.first].push_back(tmp.second);
					DCC[tmp.second].push_back(tmp.first);
				} while (!(tmp.first == cur && tmp.second == to));

				bicoloring(tmp.first, 0);
				if(!isBicolorale)
					for(int i = 1; i <= N; i++)
						if(DCC[i].size())
							isOk[i] = true;
			}

		}
		else if (to != fa)
		{
			LOW[cur] = min(LOW[cur], DFN[to]);
			if (DFN[cur] > DFN[to])
				blkStk.push(make_pair(cur, to));
		}
	}
}

int main()
{
	int u, v;
	while (scanf("%d%d", &N, &M) != EOF)
	{
		if (N == 0 && M == 0)
			break;

		initialize();

		for (int i = 1; i <= M; i++)
			scanf("%d%d", &u, &v), isHatred[u][v] = isHatred[v][u] = true;
		buildComplementary();
		for(int i = 1; i <= N; i++)
			if(!DFN[i])
				tarjan(i, 0);

		int answer = 0;
		for(int i = 1; i <= N; i++)
			answer += (!isOk[i]);
		printf("%d\n", answer);
	}
	return 0;
}
