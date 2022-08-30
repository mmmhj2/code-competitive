#include <bits/stdc++.h>
using namespace std;

class Balance
{
	const int DIR[4][2] = { { 0, 1 }, { 0, -1 }, { 1, 0 }, { -1, 0 } };

	typedef function<void(int, int, int)> funcVIII;

	vector<string> warpper(vector<string> s);
	vector<int> expand(vector<string> & s);
public:
	string canTransform(vector<string> inital, vector<string> target);
};

inline vector<string> Balance::warpper(vector<string> s)
{
	int n = s.size(), m = s[0].size();
	vector<string> ret(n + 1, string(m + 2, '#'));
	for (int i = 0; i < n; i++)
		for (int j = 0; j <= m; j++)
			ret[i + 1][j + 1] = s[i][j];
	return ret;
}

inline vector<int> Balance::expand(vector<string>& s)
{
	vector<list<int>> tree;
	s = warpper(s);

	int n = s.size(), m = s[0].size();
	vector<vector<int>> id(n, vector<int>(m, -1));
	vector<int> id_parent(1000, -1);

	funcVIII fill = [&](int x, int y, int cid) -> void
	{
		id[x][y] = cid;
		int dx = 0, dy = 1;
		for(int k = 0; k < 4; k++)
		{
			int nx = x + dx, ny = y + dy;
			if(0 <= nx && nx < n && 0 <= ny && ny < m)
			{
				if(id[nx][ny] == -1)
				{
					if(s[nx][ny] == s[x][y])
					{
						fill(nx, ny, cid);
					}
				}
				else if(id[nx][ny] < cid)
				{
					if(id_parent[cid] == -1)
					{
						id_parent[cid] = id[nx][ny],
						tree[id_parent[cid]].push_back(cid);
					}
				}
			}
			tie(dx, dy) = make_tuple(dy, -dx);
		}
	};

	int idCnt = 0;
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			if (id[i][j] == -1)
				tree.push_back(list<int>()), fill(i, j, idCnt++);

	n = tree.size();
	vector<vector<int>> topo(n);
	for (int i = n - 1; i >= 0; i--)
	{
		vector<vector<int>> opt;
		for (auto x : tree[i])
			opt.push_back(topo[x]);
		sort(opt.begin(), opt.end());
		topo[i].push_back(opt.size());
		for (auto x : opt)
			for (auto y : x)
				topo[i].push_back(y);
	}
	return topo[0];
}

inline string Balance::canTransform(vector<string> inital,
		vector<string> target)
{
	return (expand(inital) == expand(target) ? "Possible" : "Impossible");
}
