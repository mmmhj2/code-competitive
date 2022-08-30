#include <algorithm>
#include <iostream>
#include <cstring>
#include <vector>
using namespace std;

typedef long long i64;
const int MAXN = 140000;

vector <pair<i64, i64>> dp[MAXN], tmp1, tmp2;
vector <int> Adj[MAXN];

int N;
int fa[MAXN], dis[MAXN], ch[MAXN][2], chCnt[MAXN];
i64 dep[MAXN];
i64 lim;

template <class T>
void myInsert(vector <T> & result, const T & x)
{
	int p = result.size() - 1;
	if(p < 0)
		result.push_back(x);
	else if(x.second < result[p].second)
		result.push_back(x);
}

template <class T>
void merge(T & result, const T & L, const T & R)
{
	result.clear();
	int x = L.size(), y = R.size();
	int p = 0, q = 0;
	if(!y)
		return;

	while(p != x)
	{
		while(q != y && L[p].second + R[q].first <= lim)
			q++;
		if(q)
			q--;
		if(L[p].second + R[q].first <= lim)
			result.emplace_back(L[p].first, R[q].second);
		p++;
	}
}

template <class T>
void mergesort(T & result, const T & L, const T & R)
{
	result.clear();
	int x = L.size(), y = R.size();
	int p = 0, q = 0;

	while(p != x || q != y)
	{
		if(p == x)
			myInsert(result, R[q++]);
		else if(q == y)
			myInsert(result, L[p++]);
		else if(L[p].first < R[q].first)
			myInsert(result, L[p++]);
		else
			myInsert(result, R[q++]);
	}
}

void DFS(int cur)
{
	if(!chCnt[cur])
	{
		dp[cur].clear();
		dp[cur].emplace_back(dep[cur], dep[cur]);
		return;
	}

	const int &ls = ch[cur][0], &rs = ch[cur][1];
	DFS(ls), DFS(rs);

	lim += 2 * dep[cur];

	merge(tmp1, dp[ls], dp[rs]);
	merge(tmp2, dp[rs], dp[ls]);

	mergesort(dp[cur], tmp1, tmp2);

	lim -= 2 * dep[cur];

}

int main(int argc, char * argv[])
{
	ios::sync_with_stdio(false), cin.tie(nullptr);
	cin >> N ;

	for(int i = 2; i <= N; i++)
		cin >> fa[i] >> dis[i] ,
		dep[i] = dep[fa[i]] + dis[i],
		ch[fa[i]][chCnt[fa[i]]++] = i;

	i64 L = 0, R = 1e13, answer = (L + R) >> 1;

	while(L < R)
	{
		lim = answer;
		DFS(1);

		if(dp[1].size())
			R = answer;
		else
			L = answer + 1;
		answer = (L + R) >> 1;
	}

	cout << answer << endl ;
	return 0;
}
