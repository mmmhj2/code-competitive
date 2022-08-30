// BZOJ4698 Sdoi2008 Sandy的卡片
/*
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
*/


#include <iostream>
#include <cstring>
#include <cstdio>
#include <algorithm>
#define N 1005
#define inf 10000000
using namespace std;
int n,date[N][N],last[N];
int ans=0;
void get_next(int f[],int len)
{
	int j=-1;len--;
	memset(last,-1,sizeof(last));
	for(int i=1;i<=len;i++)
	{
		while(j!=-1 && f[j+1]!=f[i]) j=last[j];
		if(f[j+1]==f[i]) j++;
		last[i]=j;
	}
	return ;
}
int cnt=0;
int kmp(int ptr[],int pt,int str[],int st)
{
	pt--,st--;
	int j=-1,re=-10;
	for(int i=0;i<=pt;i++)
	{
		while(j!=-1 && ptr[i]!=str[j+1]) j=last[j];
		if(str[j+1]==ptr[i]) j++;
		re=max(re,j);
		if(j==st) return ++j;
	}
	if(re!=-10) re++;
	return re;
}
int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
	{
		scanf("%d",&date[i][0]);
		for(int j=1;j<=date[i][0];j++) scanf("%d",&date[i][j]);
		for(int j=1;j<date[i][0];j++) date[i][j]=date[i][j+1]-date[i][j];
		date[i][0]--;
	}
	for(int i=0;i<date[1][0];i++)
	{
		get_next(date[1]+1+i,date[1][0]-i);
		int t=inf;
		for(int j=2;j<=n;j++)
		{
			t=min(t,kmp(date[j]+1,date[j][0],date[1]+1+i,date[1][0]-i));
		}
		ans=max(ans,t);
	}
	cout<<++ans<<endl;
	return 0;
}

