// BZOJ4698 Sdoi2008 Sandy的卡片
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 1000 + 10 ;
int N, ans;
int seq[MAXN][MAXN], nxt[MAXN];

void getNxt(int * str, int len)
{
	len--;
	int j = -1;
	memset(nxt, 0xFF, sizeof nxt);
	for(int i = 1; i <= len; i++)
	{
		while(j != -1 && str[j+1] != str[i])
			j = nxt[j];
		if(str[j+1] == str[j])
			j++;
		nxt[i] = j;
	}
}

int KMP(int * pat, int patLen, int * str, int strLen)
{
	patLen--, strLen--;
	int j = -1, mx = -10;

	for(int i = 0; i <= patLen; i++)
	{
		while(j != -1 && pat[i] != str[j+1])
			j = nxt[j];
		if(str[j+1] == pat[i])
			j++;
		mx = max(mx, j);
		if(j == strLen)
			return ++j;
	}

	if(mx != -10)
		mx++;
	return mx;

}


int main()
{
	//cin >> N ;
	scanf("%d", &N);
	for(int i = 1; i <= N; i++)
	{
		//cin >> seq[i][0] ;
		scanf("%d", &seq[i][0]);
		for(int j = 1; j <= seq[i][0]; j++)
			//cin >> seq[i][j];
			scanf("%d", &seq[i][j]);
		seq[i][0] -= 1;
		for(int j = 1; j <= seq[i][0]; j++)
			seq[i][j] = seq[i][j+1] - seq[i][j];
	}

	for(int i = 0; i < seq[1][0]; i++)
	{
		getNxt(seq[1] + 1 + i, seq[1][0] - i);
		int tans = 0x7F7F7F7F;
		for(int j = 2; j <= N; j++)
			tans = min(tans, KMP(seq[j] + 1, seq[j][0], seq[1] + 1 + i, seq[1][0] - i));
		ans = max(tans, ans);
	}
	//cout << ans + 1 << endl ;
	printf("%d\n", ans + 1);
	return 0;
}
