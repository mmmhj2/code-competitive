#include <bits/stdc++.h>
using namespace std;

class EllysTree
{
	static constexpr const int MAXN = 100 + 5;
	int N;
	bool connected[MAXN][MAXN];
	bool vist[MAXN];
	int topSort[MAXN];

	void Floyd(const vector<int> & parent);

public:
	vector<int> getMoves(vector<int> parent);
};

void EllysTree::Floyd(const vector<int>& parent)
{
	for (int i = 0; i < N - 1; i++)
		connected[parent[i]][i + 1] = true;
	for (int k = 0; k < N; k++)
		for (int i = 0; i < N; i++)
			for (int j = 0; j < N; j++)
				connected[i][j] = (connected[i][j]
						|| (connected[i][k] && connected[k][j]));
}

vector<int> EllysTree::getMoves(vector<int> parent)
{
	vector<int> res;
	N = parent.size() + 1;
	res.resize(N, -1);

	vist[0] = true, topSort[0] = 0;
	for(int i = 1; i < N; i++)
	{
		int k = -1;
		for(int j = 0; j < N; j++)
			if(!vist[j] && vist[parent[j-1]])
				k = j;
		topSort[i] = k;
		vist[k] = true;
	}

	Floyd(parent);
	memset(vist, 0x00, sizeof vist);

	for(int i = 0; i < N; i++)
	{
		for(int j = 0; j < N; j++)
		{
			if(!vist[j] && ((i == 0) || connected[res[i-1]][j] || connected[j][res[i-1]]))
			{
				bool bad = false;
				res[i] = j, vist[j] = true;
				for(int k = i + 1; k < N; k++)
				{
					int b = -1;
					for(int s = 0; s < N; s++)
						if(!vist[topSort[s]] && (connected[res[k-1]][topSort[s]] || connected[topSort[s]][res[k-1]]))
							b = topSort[s];

					if(b != -1)
					{
						res[k] = b;
						vist[b] = true;
						continue;
					}
					bad = true;
					continue;
				}

				for(int k = i + 1; k < N; k++)
					if(res[k] != -1)
						vist[res[k]] = false,
						res[k] = -1;

				if(bad)
					vist[j] = false, res[i] = -1;
				else
					break;
			}
		}

		if((res[i] == -1) || ((i == 0) && (res[i] != 0)))
		{
			//cerr << "No Solution" << endl ;
			return vector<int>{};
		}
	}

	res.erase(res.begin());
	return res;
}
