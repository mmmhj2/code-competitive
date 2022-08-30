#include <bits/stdc++.h>
using namespace std;
list<int> lst[150000 + 5];
int main()
{
	int N, Q;
	while (~scanf("%d%d", &N, &Q))
	{
		for(int i = 1; i <= N; i++)
			lst[i].clear();
		while (Q--)
		{
			int op, u, v, w;
			scanf("%d", &op);
			switch (op)
			{
			case 1:
				scanf("%d%d%d", &u, &w, &v);
				if (w == 0)
					lst[u].push_front(v);
				else
					lst[u].push_back(v);
				break;
			case 2:
				scanf("%d%d", &u, &w);
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
			case 3:
				scanf("%d%d%d", &u, &v, &w);
				if (w)
					lst[v].reverse();
				lst[u].splice(lst[u].end(), lst[v]);
				break;
			}
		}
	}
	return 0;
}
