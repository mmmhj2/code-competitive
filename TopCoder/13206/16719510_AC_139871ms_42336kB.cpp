#include <bits/stdc++.h>
using namespace std;

class TreeColoring
{
	typedef long long i64;
	const static int BLKSZ = 100;
	const static int MAXN = 100000 + 10;

	int distance[MAXN], parent[MAXN];
	int queryType[MAXN], queryNode[MAXN];

	int N, Q, startSeed, threshold, maxDist;
	int curValue;

	int genNextRandom()
	{
		curValue = (curValue * 1999 + 17) % 1000003;
		return curValue;
	}

	int parVal[MAXN][20], pre[MAXN], last[MAXN];
	i64 parDist[MAXN][20];
	i64 dist[MAXN];

	int tmStp;
	int DFN_in[MAXN], DFN_out[MAXN];
	void DFS(int x)
	{
		//fprintf(stderr, "in %d\n", x);
		DFN_in[x] = ++tmStp;
		int j = last[x];
		while (j >= 0)
			dist[j] = dist[x] + distance[j], DFS(j), j = pre[j];
		DFN_out[x] = ++tmStp;
	}

	inline bool isAncestor(int x, int y)
	{
		return (DFN_in[x] <= DFN_in[y] && DFN_out[y] <= DFN_out[x]);
	}

	int LCA(int x, int y)
	{
		if (isAncestor(x, y))
			return x;
		for (int k = 20 - 1; k >= 0; k--)
			if (!isAncestor(parVal[x][k], y))
				x = parVal[x][k];
		return parent[x];
	}

	i64 getDist(int u, int v)
	{
		return dist[u] + dist[v] - 2 * dist[LCA(u, v)];
	}

	i64 preCalc[MAXN];
	int blueCnt[MAXN];
	void reCalc()
	{
		int total = 0;
		for (int i = 0; i < N; i++)
			blueCnt[i] = painted[i], total += blueCnt[i];
		for (int i = N - 1; i; i--)
			blueCnt[parent[i]] += blueCnt[i];

		preCalc[0] = 0;
		for (int i = 0; i < N; i++)
			preCalc[0] += (painted[i] ? dist[i] : 0);

		for (int i = 1; i < N; i++)
			preCalc[i] = preCalc[parent[i]], preCalc[i] += 1LL * distance[i]
					* ((total - blueCnt[i]) - blueCnt[i]);

	}

	bool painted[MAXN];

public:

	i64 color(int _N, int _Q, int _startSeed, int _threshold, int _maxDist)
	{
		int sq = (int) (sqrt(_Q) + 0.5);
		vector<int> blk;
		i64 ret = 0;

		N = _N, Q = _Q, startSeed = _startSeed;
		threshold = _threshold, maxDist = _maxDist;
		curValue = startSeed;
////////////////// Generate Input //////////////////
		for (int i = 0; i < N - 1; i++)
		{
			distance[i + 1] = genNextRandom() % maxDist;
			parent[i + 1] = genNextRandom();
			if (parent[i + 1] < threshold)
				parent[i + 1] = i;
			else
				parent[i + 1] = parent[i + 1] % (i + 1);
		}
		for (int i = 0; i < Q; i++)
			queryType[i] = genNextRandom() % 2 + 1, queryNode[i] =
					genNextRandom() % N;
////////////////// Preprocessing //////////////////
		for (int i = 0; i < N; i++)
			parVal[i][0] = parent[i], parDist[i][0] = distance[i];

		for (int k = 1; k < 20; k++)
			for (int i = 0; i < N; i++)
				parVal[i][k] = parVal[parVal[i][k - 1]][k - 1], parDist[i][k] =
						parDist[i][k - 1] + parDist[parVal[i][k - 1]][k - 1];

		for (int i = 0; i < N; i++)
			last[i] = -1;
		for (int i = 1; i < N; i++)
			pre[i] = last[parent[i]], last[parent[i]] = i;

		dist[0] = tmStp = 0;
		DFS(0);
////////////////// Solve the problem //////////////////
		for (int i = 0; i < Q; i++)
		{
			int v = queryNode[i];
			if (queryType[i] == 1)
			{
				if (painted[v])
					continue;
				painted[v] = true;
				blk.push_back(v);

				if (blk.size() > sq)
					reCalc(), blk.clear();
			}
			else
			{
				i64 ans = preCalc[v];
				for (int x : blk)
					ans += getDist(x, v);
				ret ^= ans;
			}
		}
		return ret;
	}

};

