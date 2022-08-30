#include <bits/stdc++.h>
using namespace std;

int adjMat[25][25];
bool vis[25];
vector<int> path;
int to;
int cnt;

bool isConnected[25][25];
void Floyd()
{
	for(int k = 1; k <= 20; k++)
		for(int i = 1; i <= 20; i++)
			for(int j = 1; j <= 20; j++)
				isConnected[i][j] |= isConnected[i][k] && isConnected[k][j];
}

void DFS(int cur)
{
	//fprintf(stderr, "%d\n", cur);
	//fflush(stderr);
	if (cur == to)
	{
		for(vector<int>::iterator itr = path.begin(); itr != path.end(); ++itr)
			printf("%d%c", *itr, " \n"[itr == path.end() - 1]);
		cnt++;
	}

	for(int i = 1; i <= 20; i++)
		if(adjMat[cur][i] && isConnected[cur][to] && !vis[i])
		{
			path.push_back(i);
			vis[i] = true;
			DFS(i);
			vis[i] = false;
			path.pop_back();
		}
}

int main()
{
	int _case = 0;
	while (cin >> to)
	{
		cnt = 0;
		memset(isConnected, 0x00, sizeof isConnected);
		memset(adjMat, 0x00, sizeof adjMat);
		path.clear();
		
		int u, v;
		while (cin >> u >> v)
		{
			if ((!u) && (!v))
				break;
			adjMat[u][v] = 1, adjMat[v][u] = 1;
			isConnected[u][v] = isConnected[v][u] = true;
		}
		Floyd();
		printf("CASE %d:\n", ++_case);
		path.push_back(1);
		vis[1] = true;
		DFS(1);
		vis[1] = false;
		path.pop_back();
		printf("There are %d routes from the firestation to streetcorner %d.\n", cnt, to);
	}
	return 0;
}
