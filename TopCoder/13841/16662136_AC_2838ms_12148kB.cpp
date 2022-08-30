#include <bits/stdc++.h>
using namespace std;

class Balance
{
	const int DIR[4][2] = { { 0, 1 }, { 0, -1 }, { 1, 0 }, { -1, 0 } };

	typedef function<void(int, int, int)> funcVIII;

	vector<string> wrap(const vector<string> s);
	vector<int> topo(vector<string> & s);
public:
	string canTransform(vector<string> inital, vector<string> target);
};

vector<string> Balance::wrap(const vector<string> s)
{
    int n = s.size(), m = s[0].size();
    vector<string> r(n+2, string(m+2, '#') );
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            r[i+1][j+1] = s[i][j];
        }
    }
    return r;
}
vector<int> Balance::topo(vector<string> &s)
{
    vector<list<int>> tree;
    s = this->wrap(s);
    // Flood fill:
    int n = s.size(), m = s[0].size();
    vector<vector<int>> id(n, vector<int>(m, -1));
    vector<int> id_parent(1000, -1);
    function<void(int,int,int)> fill = [&](int x, int y, int z) {
        id[x][y] = z;
        int dx = 0, dy = 1;
        for (int i = 0; i < 4; i++) {
            int nx = x + dx, ny = y + dy;
            if ( (0 <= nx && nx < n) && (0 <= ny && ny < m) ) {
                if (id[nx][ny] == -1) {
                    if (s[nx][ny] == s[x][y]) {
                        fill(nx,ny,z);
                    }
                } else if (id[nx][ny] < z) {
                    if (id_parent[z] == -1) {
                        id_parent[z] = id[nx][ny];
                        tree[id_parent[z]].push_back(z);
                    }
                }
            }
            tie(dx,dy) = make_tuple(dy, -dx);
        }
    };
    // Create the tree:
    int id_count = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (id[i][j] == -1) {
                tree.push_back(list<int>());
                fill(i,j, id_count++);
            }
        }
    }

    // Save the tree using that Prefix notation format:
    n = tree.size();
    vector<vector<int>> topo(n);
    for (int i = n - 1; i >= 0; i--) {
        vector<vector<int>> options;
        for (auto x: tree[i]) {
            options.push_back( topo[x] );
        }
        sort(options.begin(), options.end());
        topo[i].push_back( options.size() );
        for (auto x: options) {
            for (int y: x) {
                topo[i].push_back(y);
            }
        }
    }

    return topo[0];
}

inline string Balance::canTransform(vector<string> inital,
		vector<string> target)
{
	return (topo(inital) == topo(target) ? "Possible" : "Impossible");
}
