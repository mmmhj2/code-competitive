#include <algorithm>
#include <vector>
#include <cstdio>
using namespace std;

template<class T>
T myAbs(const T & x)
{
	if (x > 0)
		return x;
	return (-x);
}

const int MAXN = (1e5 + 10) * 2;
const int MOD = 998244353;

struct edge
{
	int to, id;
	edge(int _to = 0, int _id = 0)
	{
		to = _to, id = _id;
	}
};

vector<edge> Adj[MAXN], circle;
bool vis[MAXN], visEdge[MAXN];
bool inCircle[MAXN];

int cnt[MAXN], rev_cnt[MAXN];

edge stk[MAXN];
int top;

int dfsCircle(int cur, int fa = 0)
{
	vis[cur] = true;
	int answer = 0;

	for (vector<edge>::iterator itr = Adj[cur].begin(); itr != Adj[cur].end();
			++itr)
	{
		if (itr->id == fa || visEdge[myAbs(itr->id)])
			continue;
		visEdge[myAbs(itr->id)] = true;

		if (vis[itr->to])
		{
			if (!circle.empty())
				return (answer = -1);
			answer = 1;

			int tempTop = top;

			while (stk[tempTop].to != itr->to && tempTop > 0)
				tempTop--;
			while (tempTop <= top && tempTop > 0)
				circle.push_back(stk[tempTop++]);
			circle.push_back(edge(cur, itr->id));

		}
		else
		{
			stk[++top] = edge(cur, itr->id);
			answer |= dfsCircle(itr->to, -(itr->id));
			top--;
		}
	}

	return answer;
}

void dfs1(int cur, int fa = 0)
{
	//printf("DFS1 : %d\n", cur);
	cnt[cur] = 0;
	for (vector<edge>::iterator itr = Adj[cur].begin(); itr != Adj[cur].end();
			++itr)
		if ((!inCircle[itr->to]) && fa != itr->id)
			dfs1(itr->to, -(itr->id)), cnt[cur] +=
					(cnt[itr->to] + (itr->id < 0));
}

int mn, mnCnt;
void dfs2(int cur, int fa = 0, int _cnt = 0)
{
	//printf("%d %d %d, %d %d\n", cur, fa, _cnt, cnt[cur], rev_cnt[cur]);
	rev_cnt[cur] = _cnt;
	if (mn == cnt[cur] + rev_cnt[cur])
		mnCnt++;
	else if (mn > cnt[cur] + rev_cnt[cur])
		mnCnt = 1, mn = cnt[cur] + rev_cnt[cur];
		//printf("Minimal switched to : %d, %d + %d\n", mn, cnt[cur], rev_cnt[cur]);


	for (vector<edge>::iterator itr = Adj[cur].begin(); itr != Adj[cur].end(); ++itr)
		if (itr->id != fa)
			_cnt += (cnt[itr->to] + (itr->id < 0));
	for (vector<edge>::iterator itr = Adj[cur].begin(); itr != Adj[cur].end(); ++itr)
		if (itr->id != fa)
			dfs2(itr->to, -(itr->id),
					_cnt - (cnt[itr->to] + (itr->id < 0)) + (itr->id > 0));
}

pair<int, int> solve(int u)
{
	pair <int, int> answer (0, 0);
	top = 0, circle.clear();

	switch(dfsCircle(u))
	{
	case -1:
		return make_pair(-1, -1);
		break;
	case 0:
		//printf("Case 2\n");

		mn = 0x7F7F7f7F, mnCnt = 0;
		dfs1(u);
		dfs2(u);
		answer = make_pair(mn, mnCnt);
		break;
	default:
		//printf("Case 3, circle size : %d\n", circle.size());

		int _cnt = 0;
		for(vector<edge>::iterator itr = circle.begin(); itr != circle.end(); ++itr)
			inCircle[itr->to] = true, _cnt += (itr->id > 0);
		answer.first += min(_cnt, (int)circle.size() - _cnt);
		for(vector<edge>::iterator itr = circle.begin(); itr != circle.end(); ++itr)
			dfs1(itr->to) ,answer.first += cnt[itr->to];

		answer.second = (_cnt == ((int)circle.size() - _cnt)) + 1;
	}
	return answer;
}

bool CmpEdge(const edge & x, const edge & y)
{
	return (x.id > y.id);
}

int main()
{
//	freopen("back.in", "r", stdin);
//	freopen("back.out", "w", stdout);

	int T;
	scanf("%d", &T);

	while(T--)
	{
		int N;
		pair <int, int> answer(0, 1);

		scanf("%d", &N);

		for(int i = 1; i <= 2 * N; i++)
			Adj[i].clear(), inCircle[i] = false, vis[i] = false, visEdge[i] = false;

		for(int i = 1; i <= N; i++)
		{
			int u, v;
			scanf("%d%d", &u, &v);
			Adj[v].push_back(edge(u, i));
			if(u != v)
				Adj[u].push_back(edge(v, -i));
		}

		for(int i = 1; i <= 2 * N; i++)
			sort(Adj[i].begin(), Adj[i].end(), CmpEdge);

		for(int i = 1; i <= 2 * N; i++)
			if(!vis[i])
			{
				pair <int, int> tmp = solve(i);
				if(tmp.first == -1 && tmp.second == -1)
				{
					answer = make_pair(-1, -1);
					break;
				}
				//printf("%d : %d %d\n", i, tmp.first, tmp.second);
				answer.first += tmp.first;
				answer.second = 1LL * answer.second * tmp.second % MOD;
			}

		printf("%d %d\n", answer.first, answer.second);
	}

	return 0;
}
