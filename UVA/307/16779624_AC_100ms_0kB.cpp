#include <bits/stdc++.h>
using namespace std;
////////////////////////////////////////
const int MAXN = 100 + 10;

int stk[MAXN], units[MAXN], vis[MAXN];

int DFS(int utNow, int utSz, int stNow, int stLen, int stSz)
{
	if(stNow >= stSz)
		return 1;
	for(int i = utNow; i < utSz; i++)
	{
		if(vis[i] || (i != 0 && !vis[i-1] && units[i-1] == units[i]))
			continue;
		if(stk[stNow] + units[i] > stLen)
			continue;
		vis[i] = true;
		stk[stNow] += units[i];

		if(stk[stNow] == stLen)
		{
			if(DFS(0, utSz, stNow + 1, stLen, stSz))
				return true;
		}
		else if(stk[stNow] < stLen)
			if(DFS(i + 1, utSz, stNow, stLen, stSz))
				return true;
		stk[stNow] -= units[i];
		vis[i] = false;
		if(stk[stNow] + units[i] == stLen)
			return false;
		if(!stk[stNow])
			return false;
	}
	return false;
}

int main()
{
	int N;

	while(cin >> N && N)
	{
		int sum = 0, mx = 0;
		for(int i = 0; i < N; i++)
		{
			cin >> units[i], sum += units[i];
			mx = max(mx, units[i]);
			stk[i] = 0, vis[i] = false;
		}

		sort(units, units + N, greater<int>());

		for(int len = mx; len <= sum; len++)
			if(sum % len == 0)
				if(DFS(0, N, 0, len, sum / len))
				{
					cout << len << endl ;
					break;
				}

	}

	return 0;
}