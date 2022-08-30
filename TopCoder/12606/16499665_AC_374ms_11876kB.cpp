#include<cstdio>
#include<algorithm>
#include<string>
#include<vector>
using namespace std;

const int MAXN = 55;

int ans[MAXN], cnt[MAXN], tag[MAXN];
int head[MAXN], ecnt;
struct node
{
	int v, nxt;
} E[MAXN * 2];

void addEdge(int u, int v)
{
	E[++ecnt] = (node
			)
			{ v, head[u] };
	head[u] = ecnt;
}

void dfs(int u, int fa = -1)
{
	for (int i = head[u]; i; i = E[i].nxt)
	{
		int v = E[i].v;
		if (fa == v)
			continue;
		dfs(v, u);
		ans[u] += ans[v];
	}
	if (u != 0 && tag[u] && (ans[u] & 1) != cnt[u])
		ans[u]++;
}

class TurnOnLamps
{
public:
	int minimize(vector<int> roads, string initState, string isImportant)
	{
		int m = roads.size();
		for (int i = 0; i < (int) roads.size(); i++)
		{
			addEdge(i + 1, roads[i]);
			addEdge(roads[i], i + 1);
		}
		for (int i = 0; i < m; i++)
			tag[i + 1] = (isImportant[i] == '1' ? 1 : 0);
		for (int i = 0; i < m; i++)
		{
			if (isImportant[i] == '0')
				continue;
			cnt[i + 1] = (initState[i] == '1' ? 0 : 1);
		}
		dfs(0);
		return (ans[0] + 1) / 2;
	}
};
