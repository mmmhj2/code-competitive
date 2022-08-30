#include <iostream>
#include <cstring>
#include <vector>
using namespace std;
typedef long long i64;
const int MAXN = 1e5 + 10;

i64 answer;
i64 totCnt;
i64 N, M;
i64 check[MAXN];
i64 cnt[3];

bool flag;

vector<pair<i64, i64> > Adj[MAXN];

inline void addEdge(i64 u, i64 v, i64 w)
{
	Adj[u].emplace_back(v, w);
}

void DFS(int cur)
{
	cnt[check[cur]] ++;

	for(auto x : Adj[cur])
	{
		totCnt += (x.second == 1);

		if(check[x.first] != -1)
		{
			if((check[cur] + x.second) % 3 != check[x.first])
				flag = true;
		}
		else
		{
			check[x.first] = (check[cur] + x.second) % 3;
			DFS(x.first);
		}
	}
}

int main()
{
	ios::sync_with_stdio(false), cin.tie(nullptr);

	cin >> N >> M;
	for (int i = 1; i <= M; i++)
	{
		i64 u, v;
		cin >> u >> v;
		addEdge(u, v, 1);
		addEdge(v, u, 2);
	}

	memset(check, -1, sizeof check);

	for(int i = 1; i <= N; i++)
	{
		if(check[i] != -1)
			continue;

		check[i] = 0, totCnt = 0;
		cnt[0] = cnt[1] = cnt[2] = 0;
		flag = false;

		DFS(i);
		if(flag)
			answer += (cnt[0] + cnt[1] + cnt[2]) * (cnt[0] + cnt[1] + cnt[2]);
		else if(!cnt[0] || !cnt[1] || !cnt[2])
			answer += totCnt;
		else
			answer += cnt[0] * cnt[1] + cnt[1] * cnt[2] + cnt[2] * cnt[0];

	}

	cout << answer << endl ;

	return 0;
}