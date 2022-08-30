#include <bits/stdc++.h>
using namespace std;

const int MAXN = 150000 + 10;

typedef list<int> List;

List lst[MAXN];

int main()
{
	ios::sync_with_stdio(false), cin.tie(nullptr);
	int N, Q;
	while (cin >> N >> Q)
	{
		for(int i = 1; i <= N; i++)
			lst[i].clear();

		while (Q--)
		{
			int op, u, v, w, val;
			cin >> op;
			switch (op)
			{
			case 1:			//insert
				cin >> u >> w >> val;
				if (w == 0)
					lst[u].push_front(val);
				else
					lst[u].push_back(val);
				break;
			case 2:			// query and delete
				cin >> u >> w;

				if (lst[u].empty())
					cout << -1 << endl;
				else
				{
					if (w == 0)
						cout << lst[u].front() << endl, lst[u].pop_front();
					else
						cout << lst[u].back() << endl, lst[u].pop_back();
				}

				break;
			case 3:			// merge
				cin >> u >> v >> w;
				if (w)
					lst[v].reverse();
				lst[u].insert(lst[u].end(), lst[v].begin(), lst[v].end());
				//lst[v].erase(lst[v].begin(), lst[v].end());
				lst[v].clear();
				break;
			}
		}
	}
	return 0;
}
