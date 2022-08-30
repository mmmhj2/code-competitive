#include <bits/stdc++.h>
using namespace std;

const int MAXN = 100000 + 10;

struct contract
{
	int num, sgn, id;
	
	static bool cmpByNum(const contract & lhs, const contract & rhs)
	{
		return lhs.num > rhs.num;
	}
	
	static bool cmpById(const contract & lhs, const contract & rhs)
	{
		return lhs.id < rhs.id;
	}
	
}con[MAXN];

int N;

int main()
{
	//freopen("out", "w", stdout);
	while(~scanf("%d", &N))
	{
		long long sum = 0;
		for(int i = 1; i <= N; i++)
			scanf("%d", &con[i].num), sum += con[i].num, con[i].id = i, con[i].sgn = 0;
		
		if(sum & 1)
		{
			puts("No");
			continue;
		}
		
		sum = sum / 2;
		sort(&con[1], &con[N + 1], contract::cmpByNum);
		for(int i = 1; i <= N; i++)
		{
			printf("Trying %d, %d %lld\n", i, con[i].num, sum);
			if(con[i].num <= sum)
				sum -= con[i].num, con[i].sgn = 1;
			else
				con[i].sgn = -1;
		}
		sort(&con[1], &con[N + 1], contract::cmpById);
		puts("Yes");
		for(int i = 1; i <= N; i++)
			printf("%d%c", con[i].sgn, " \n"[i == N]);
	}
}
