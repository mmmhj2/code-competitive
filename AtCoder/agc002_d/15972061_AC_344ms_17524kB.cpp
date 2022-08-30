#include <bits/stdc++.h>
using namespace std;

typedef pair <int, int> pii;

const int MAXN = 1e5 + 10;

vector <pii> edge;

namespace DisjointSet
{
int fa[MAXN], rnk[MAXN];

void init()
{
	iota(fa, fa + MAXN, 0);
	fill(rnk, rnk + MAXN, 1);
}

int find(int x)
{
	if(fa[x] == x)
		return x;
	return find(fa[x]);
}

int merge(int x, int y)
{
	int a = find(x), b = find(y);
	if(a == b)
		return -1;
	if(rnk[a] < rnk[b])
		swap(a, b);
	rnk[a] += rnk[b];
	fa[b] = a;

	return 0;
}

}

int N, M, Q;
int X[MAXN], Y[MAXN], Z[MAXN];
int Lo[MAXN], Hi[MAXN], Mid[MAXN];
bool QueryStatus[MAXN];

vector <int> answer[MAXN];

int main()
{

	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	cin >> N >> M ;
	for(int i = 1; i <= M; i++)
	{
		int u, v;
		cin >> u >> v ;
		edge.push_back(make_pair(u, v));
	}
	cin >> Q ;
	for(int i = 1; i <= Q; i++)
		cin >> X[i] >> Y[i] >> Z[i] ,
		Lo[i] = -1, Hi[i] = M;

	int availCnt ;
	while(true)
	{
		availCnt = 0;
		for(int i = 1; i <= Q; i++)
		{
			Mid[i] = (Hi[i] + Lo[i]) >> 1;

			if(Lo[i] + 1 < Hi[i])
				QueryStatus[i] = true,
				availCnt++, answer[Mid[i]].push_back(i);
			else
				QueryStatus[i] = false;
		}

		if(availCnt <= 0)
			break;

		DisjointSet::init();
		for(int i = 0; i < M; i++)
		{
			int u, v;
			u = edge[i].first, v = edge[i].second;
			DisjointSet::merge(u, v);

			for(vector<int>::iterator itr = answer[i].begin(); itr != answer[i].end(); ++itr)
			{
				const int & qid = *itr;
				int sz = DisjointSet::rnk[DisjointSet::find(X[qid])];
				if(DisjointSet::find(X[qid]) != DisjointSet::find(Y[qid]))
					sz += DisjointSet::rnk[DisjointSet::find(Y[qid])];

				assert(Mid[qid] == i);
				if(sz >= Z[qid])
					Hi[qid] = Mid[qid];
				else
					Lo[qid] = Mid[qid];
			}
		}

		for(int i = 1; i <= Q; i++)
			if(QueryStatus[i])
				answer[Mid[i]].clear();
	}

	for(int i = 1; i <= Q; i++)
		cout << Hi[i] + 1 << endl ;

	return 0;
}
