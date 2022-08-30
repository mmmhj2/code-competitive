#include <bits/stdc++.h>
using namespace std;

typedef long long i64;
const int MAXN = 100000 + 10;

int N, M;
vector<i64> cost[4];

i64 prefixW3[MAXN], prefixW2[MAXN], prefixW1[MAXN];

i64 f(int w3, int w2)
{
	return prefixW2[w2] + prefixW1[min(M - w3 * 3 - w2 * 2, (int)cost[1].size())];
}

int main()
{
	i64 ans = 0, w, c;
	ios::sync_with_stdio(false), cin.tie(nullptr);

	cin >> N >> M;
	for (int i = 1; i <= N; i++)
		cin >> w >> c, cost[w].push_back(c);
	for (int i = 1; i <= 3; i++)
		sort(cost[i].begin(), cost[i].end(), greater<int>());
	for (unsigned j = 0; j < cost[3].size(); j++)
		prefixW3[j + 1] = prefixW3[j] + cost[3][j];
	for (unsigned j = 0; j < cost[2].size(); j++)
		prefixW2[j + 1] = prefixW2[j] + cost[2][j];
	for (unsigned j = 0; j < cost[1].size(); j++)
		prefixW1[j + 1] = prefixW1[j] + cost[1][j];

	for(int w3 = 0; w3 <= min((int)cost[3].size(), M / 3); w3++)
	{
		int L = 0, R = min((int)cost[2].size(), (M - w3 * 3) / 2);
//		cerr << "Searching : " << w3 << " " << L << " " << R << endl ;
		while(L + 1 < R)
		{
			int mid1 = (L + R) >> 1;
			int mid2 = (mid1 + R) >> 1;
//			cerr << L << mid1 << " " << mid2 << " " << R << endl ;
			assert(L <= mid1 && mid1 <= R);
			assert(L <= mid2 && mid2 <= R);
			if(f(w3, mid1) > f(w3, mid2))
				R = mid2;
			else
				L = mid1;
		}
//		cerr << "Updating answer : " << w3 << " " << L << " " << R << endl ;
		ans = max(ans, 1LL * max(f(w3, L), f(w3, R)) + prefixW3[w3]);
	}

	cout << ans << endl ;

	return 0;
}
