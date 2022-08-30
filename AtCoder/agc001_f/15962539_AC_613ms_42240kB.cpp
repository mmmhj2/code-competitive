#include <algorithm>
#include <cstdio>
#include <vector>
#include <queue>

#define REDIRECT(x) freopen(x".in", "r", stdin), freopen(x".out", "w", stdout), freopen("debug.log", "w", stderr)
#define CLOSEALL() fclose(stdin), fclose(stdout)

using namespace std;

const int MAXN = 500000 + 10;

int N, K;

namespace segmentTree
{
int SegTree[MAXN << 2];
int Query(int QL, int QR, int L = 1, int R = N, int x = 1)
{
	if (QL <= L && R <= QR)
		return SegTree[x];

	int mid = (L + R) >> 1;

	if (QR <= mid)
		return Query(QL, QR, L, mid, x << 1);
	if (QL > mid)
		return Query(QL, QR, mid + 1, R, (x << 1) | 1);
	else
		return max(Query(QL, QR, L, mid, x << 1),
				Query(QL, QR, mid + 1, R, (x << 1) | 1));
}

void Modify(int mpos, int num, int L = 1, int R = N, int x = 1)
{
	if (L == mpos && R == mpos)
	{
		SegTree[x] = num;
		return;
	}

	int mid = (L + R) >> 1;

	if (mpos <= mid)
		Modify(mpos, num, L, mid, x << 1);
	else
		Modify(mpos, num, mid + 1, R, (x << 1) | 1);
	SegTree[x] = max(SegTree[x << 1], SegTree[(x << 1) | 1]);
}

}  // namespace segmentTree

int input[MAXN];
int answer[MAXN], ansCnt;
int inDeg[MAXN];
vector<int> Adj[MAXN];

inline void addEdge(int u, int v)
{
	Adj[u].push_back(v);
	inDeg[v]++;
}

void topologySort()
{
	priority_queue<int, vector<int>, greater<int> > PQ;
	for (int i = 1; i <= N; i++)
		if (inDeg[i] <= 0)
			PQ.push(i);

	while (!PQ.empty())
	{
		int cur;
		cur = PQ.top(), PQ.pop();
		answer[cur] = ++ansCnt;

		for (vector<int>::iterator itr = Adj[cur].begin();
				itr != Adj[cur].end(); ++itr)
			if (!(--inDeg[*itr]))
				PQ.push(*itr);
	}
}

int main()
{
	//REDIRECT("swap");

	int k;
	scanf("%d%d", &N, &K);
	for (int i = 1; i <= N; i++)
		scanf("%d", &k), input[k] = i;
	for(int i = 1; i <= N; i++)
	{
		int L = max(1, input[i] - K + 1), R = min(N, input[i] + K - 1);

		k = segmentTree::Query(L, input[i]);
		//fprintf(stderr, "Queried in segment [%d, %d] : %d\n", L, input[i], k);
		if(k != 0)
			addEdge(input[k], input[i]);

		k = segmentTree::Query(input[i], R);
		//fprintf(stderr, "Queried in segment [%d, %d] : %d\n",input[i], R, k);
		if(k != 0)
			addEdge(input[k], input[i]);

		segmentTree::Modify(input[i], i);
	}

	topologySort();

	for(int i = 1; i <= N; i++)
		printf("%d\n", answer[i]);

	CLOSEALL();
	return 0;
}
