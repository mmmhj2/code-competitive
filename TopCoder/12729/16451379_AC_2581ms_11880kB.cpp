#include <bits/stdc++.h>
using namespace std;

class GearsDiv1
{
	static constexpr const int MAXN = 50 + 5;

	bool adjMat[MAXN][MAXN];
	bool vist[MAXN];

	int N;
	int match[MAXN];

	vector<int> A[3];
	vector<int> Adj[MAXN];

	bool findMatch(int x);
	int solve(int x,int y);

public:
	int getmin(string color, vector<string> graph);
};

bool GearsDiv1::findMatch(int x)
{
	for(auto to : Adj[x])
	{
		if(vist[to])
			continue;
		vist[to] = true;

		if(!match[to] || findMatch(match[to]))
		{
			match[to] = x;
			return true;
		}
	}
	return false;
}

int GearsDiv1::solve(int x, int y)
{
	int res = 0;
	for(int i = 1; i <= N; i++)
		Adj[i].clear();

	for(auto a : A[x])
		for(auto b : A[y])
			if(adjMat[a][b])
				Adj[a].push_back(b), Adj[b].push_back(a);

	memset(match, 0x00, sizeof match);

	for(int i = 1; i <= N; i++)
	{
		memset(vist, 0x00, sizeof vist);
		res += findMatch(i);
	}
	return res / 2;
}

int GearsDiv1::getmin(string color, vector<string> graph)
{
	N = color.size();
	for(int i = 0; i < N; i++)
		switch(color[i])
		{
		case 'R':
			A[0].push_back(i + 1);
			break;
		case 'G':
			A[1].push_back(i + 1);
			break;
		case 'B':
			A[2].push_back(i + 1);
			break;
		}

	for(int i = 0; i < N; i++)
		for(int j = 0; j < N; j++)
			if(graph[i][j] == 'Y')
				adjMat[i + 1][j + 1] = 1;

	return min({solve(0, 1), solve(1, 2), solve(0, 2)});

}
