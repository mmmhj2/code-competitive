// POJ 2942 Knights of the Round Table
#include <algorithm>
#include <iostream>
#include <cstring>
#include <cstdio>
#include <vector>
#include <stack>
#include <set>
using namespace std;

const int MAXN = 100000 + 5;

int N, M;

int tmStp, blkCnt;
int DFN[MAXN], LOW[MAXN];
stack<pair<int, pair<int, int> > > blkStk;

vector<pair<int, int> > Adj[MAXN];
vector<int> finalAnswer;

void addEdge(int u, int v, int index)
{
	Adj[u].emplace_back(v, index);
	Adj[v].emplace_back(u, index);
}

void tarjan(int cur, int fa)
{
	DFN[cur] = LOW[cur] = ++tmStp;

	for (vector<pair<int, int> >::iterator itr = Adj[cur].begin();
			itr != Adj[cur].end(); ++itr)
	{
		const int & to = itr->first;

		if (!DFN[to])
		{
			blkStk.emplace(cur, make_pair(to, itr->second));
			tarjan(to, cur);
			LOW[cur] = min(LOW[cur], LOW[to]);

			if (LOW[to] >= DFN[cur])
			{
//				fprintf(stderr, "Found new block\n");
				pair<int, pair<int, int> > tmp;
				vector<int> answer;
				set<int> vexs;

				do
				{
					tmp = blkStk.top(), blkStk.pop();
//					fprintf(stderr, "Edge between %d and %d\n", tmp.first,
//							tmp.second);
					vexs.insert(tmp.first);
					vexs.insert(tmp.second.first);
					answer.push_back(tmp.second.second);
				} while (!(tmp.first == cur && tmp.second.first == to));

				if (answer.size() == vexs.size())
					for (auto x : answer)
						finalAnswer.push_back(x);

			}

		}
		else if (to != fa)
		{
			LOW[cur] = min(LOW[cur], DFN[to]);
			if (DFN[cur] > DFN[to])
				blkStk.emplace(cur, make_pair(to, itr->second));
		}
	}
}

int main()
{
	int u, v;
	cin >> N >> M;
	for (int i = 1; i <= M; i++)
		cin >> u >> v, addEdge(u, v, i);
	for (int i = 1; i <= N; i++)
		if (!DFN[i])
			tarjan(1, -1);

	sort(finalAnswer.begin(), finalAnswer.end());
	finalAnswer.erase(unique(finalAnswer.begin(), finalAnswer.end()),
			finalAnswer.end());
	cout << finalAnswer.size() << endl;
	for (auto x : finalAnswer)
		cout << x << " ";
	cout << endl;

	return 0;
}
