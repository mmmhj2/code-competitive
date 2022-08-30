// BZOJ2150 部落战争
#include <algorithm>
#include <cstring>
#include <cstdio>
using namespace std;

const int MAXN = 10;
const int MAXM = 2500 + 50;

int N, M, R, C;
int cityCnt;

int mp[MAXM][MAXM], match[MAXM];
int id[MAXM][MAXM];
int dx[5], dy[5];

bool flag[MAXM];
bool findMatch(int x)
{
	for(int i = 1; i <= cityCnt; i++)
		if(mp[x][i] && !flag[i])
		{
			flag[i] = true;
			if(match[i] == 0 || findMatch(match[i]))
			{
				match[i] = x;
				return true;
			}
		}
	return false;
}

int maxMatch()
{
	int ret = 0;
	for(int i = 1; i <= cityCnt; i++)
	{
		memset(flag, 0x00, sizeof flag);
		if(findMatch(i))
			ret++;
	}
	return ret;
}

int main()
{
	char ch[60][60];
	scanf("%d%d%d%d", &N, &M, &R, &C);
	dx[1] = R, dx[2] = R, dx[3] = C, dx[4] = C;
	dy[1] = C, dy[2] = -C, dy[3] = R, dy[4] = -R;

	for(int i = 1; i <= N; i++)
	{
		scanf("%s", ch[i]+1);
		for(int j = 1; j <= M; j++)
			if(ch[i][j] == '.')
				id[i][j] = ++cityCnt;
	}

	for(int i = 1; i <= N; i++)
		for(int j = 1; j <= M; j++)
			if(ch[i][j] == '.')
				for(int k = 1; k <= 4; k++)
				{
					int x = i + dx[k], y = j + dy[k];
					if(x < 1 || x > N || y < 1 || y > M)
						continue;
					if(ch[x][y])
						mp[id[i][j]][id[x][y]] = true;
				}
	printf("%d\n", cityCnt - maxMatch());
	return 0;
}
