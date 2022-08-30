#include <bits/stdc++.h>
using namespace std;

typedef long long i64;

const int MAXN = 100000 + 5;
const int MOD = 1e9 + 7;

int N;
i64 answer, dp[MAXN];
int degree[MAXN], lenCnt[MAXN];
int pre[MAXN], nxt[MAXN];
bool vis[MAXN];

bool noSolution = false;

void findCycle()
{
	for (int i = 1; i <= N; i++)
	{
		if (degree[i] > 2)
			return noSolution = true, (void) 0;
		if (degree[i] != 2 || vis[i])
			continue;

		int cur = i;

		do
		{
			if (vis[cur])
				return noSolution = true, (void) 0;
			vis[cur] = true;
			pre[nxt[cur]] = cur;
			cur = nxt[cur];
		} while (cur != i);
	}
}

void processCircleBasedTree()
{
	for (int i = 1; i <= N; i++)
	{
		if (degree[i])
			continue;

		int cur = i, footLen = 0, cycleLen = 0;
		while (!vis[cur])
			vis[cur] = true,
			cur = nxt[cur],
			footLen++;
		do
			cur = pre[cur],
			cycleLen++;
		while (degree[cur] == 1);
		if (footLen < cycleLen)
			answer = answer * 2 % MOD;
		if (footLen > cycleLen)
			return noSolution = true, (void) 0;
	}
}

void countCycle()
{
	for (int i = 1; i <= N; i++)
	{
		if (vis[i])
			continue;
		int cur = i, len = 0;
		do
		{
			vis[cur] = true;
			cur = nxt[cur];
			len++;
		} while (cur != i);
		lenCnt[len]++;
	}
}

int main()
{
	answer = 1;
	ios::sync_with_stdio(false), cin.tie(NULL);
	cin >> N;

	for (int i = 1; i <= N; i++)
		cin >> nxt[i], degree[nxt[i]]++;

	findCycle();
	if (noSolution)
		return cout << 0 << endl, 0;
	processCircleBasedTree();
	if (noSolution)
			return cout << 0 << endl, 0;
	countCycle();
	if (noSolution)
		return cout << 0 << endl, 0;

	for (int i = 1; i <= N; i++)
	{
		dp[0] = 1LL;
		for (int j = 1; j <= lenCnt[i]; j++)
		{
			dp[j] = dp[j - 1] * (((i % 2 == 0) || i == 1) ? 1 : 2);
			if (j >= 2)
				dp[j] = (dp[j] + ((((dp[j - 2] * (j - 1)) % MOD) * i) % MOD))
						% MOD;
		}

		answer = answer * dp[lenCnt[i]] % MOD;
	}
	cout << answer << endl;
}

