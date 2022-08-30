#include <bits/stdc++.h>
using namespace std;

const int MAXN = 1000 + 10;

int top;
pair <int, int> stk[MAXN];

int N, M;
char mp[MAXN][MAXN];
int height[MAXN], ans[MAXN * 2];

int main()
{
	int T;
	scanf("%d", &T);
	while(T--)
	{
		top = 0;
		memset(stk, 0x00, sizeof stk);
		memset(mp, 0x00, sizeof mp);
		memset(height, 0x00, sizeof height);
		memset(ans, 0x00, sizeof ans);
		
		scanf("%d%d", &N, &M);
		for(int i = 1; i <= N; i++)
			scanf("%s", mp[i] + 1);
		
		for(int i = 1 ; i <= N; i++)
		{
			for(int j = 1; j <= M; j++)
				if(mp[i][j] == '.')
					height[j]++;
				else
					height[j] = 0;
			top = 0;
			for(int j = 1; j <= M; j++)
				if(height[j])
				{
					if(!top)
					{
						ans[height[j]+1]++;
						stk[++top] = make_pair(j, height[j]);
						continue;
					}
					while(top > 1 && stk[top - 1].second >= height[j])
						top--;
					if(stk[top].second > height[j])
						stk[top].second = height[j];
					if(top > 1 && stk[top].second - stk[top].first <= stk[top-1].second - stk[top-1].first)
						top--;
					if(height[j] - j > stk[top].second - stk[top].first)
						stk[++top] = make_pair(j, height[j]);
					ans[j - stk[top].first + 1 + stk[top].second]++;
				}
				else
					top = 0;
		}
		
		for(int i = 1; i <= M + N; i++)
			if(ans[i])
				printf("%d x %d\n", ans[i], i * 2);
		
	}
	
	return 0;
}
