#include <bits/stdc++.h>
using namespace std;

const int MAXN = 1000000 + 10;

pair<int, int> state[MAXN];
int N;

int main()
{
	int kase;
	scanf("%d", &kase);

	while(kase--)
	{
		int ans = 0, tmp;
		scanf("%d", &N);
		for(int i = 1; i <= N; i++)
			scanf("%d", &state[i].second);
		for(int i = 1; i <= N; i++)
			scanf("%d", &state[i].first);
		tmp = 0x7F7F7F7F;
		for(int i = N; i >= 1; i--)
		{
			tmp = min(tmp, state[i].first);
			tmp = max(tmp, state[i].second);
			state[i].first = tmp;
		}
		tmp = 0x7F7F7F7F;
		for(int i = 1; i <= N; i++)
		{
			tmp = max(tmp, state[i].second);
			tmp = min(tmp, state[i].first);
			state[i].first = tmp;
			ans += state[i].first - state[i].second;
		}
		printf("%d\n", ans);
	}

	return 0;
}
