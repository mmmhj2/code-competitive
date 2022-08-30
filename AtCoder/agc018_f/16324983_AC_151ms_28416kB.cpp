#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

const int MAXN = 1e5 + 5;

int N;
int root[2];
int res[MAXN];
int match[2][MAXN];
int parity[2][MAXN];
vector <int> 	Adj[2][MAXN];
vector <int> newAdj[2][MAXN];

int curG;

void DFS(int cur)
{
	for(auto x : Adj[curG][cur])
	{
		DFS(x);
		newAdj[curG][cur].push_back(newAdj[curG][x].front());
	}
	while(newAdj[curG][cur].size() > 1)
	{
		int u = newAdj[curG][cur].back();
		newAdj[curG][cur].pop_back();
		int v = newAdj[curG][cur].back();
		newAdj[curG][cur].pop_back();
		match[curG][u] = v;
		match[curG][v] = u;
	}
	if(newAdj[curG][cur].empty())
		parity[curG][cur] = 1, newAdj[curG][cur].push_back(cur);
}

void getRes(int cur)
{
	for(int G = 0; G < 2; G++)
	{
		int to = match[G][cur];
		if(to != 0 && res[to] == 0)
			res[to] = -res[cur], getRes(to);
	}
}

int main(int argc, char **argv)
{
	cin >> N ;
	for(curG = 0; curG < 2; curG++)
	{
		for(int i = 1; i <= N; i++)
		{
			int fa;
			cin >> fa;
			if(fa == -1)
				root[curG] = i;
			else
				Adj[curG][fa].push_back(i);
		}
		DFS(root[curG]);
	}

	for(int i = 1; i <= N; i++)
		if(parity[0][i] != parity[1][i])
		{
			cout << "IMPOSSIBLE" << endl ;
			return 0;
		}

	for(int i = 1; i <= N; i++)
	{
		if(parity[0][i] == 0 || (parity[0][i] == 1 && res[i]))
			continue;
		res[i] = 1;
		getRes(i);
	}

	cout << "POSSIBLE" << endl ;
	for(int i = 1; i <= N; i++)
		cout << res[i] << " ";
	cout << endl ;
}

