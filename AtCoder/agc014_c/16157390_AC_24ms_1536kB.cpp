#include <algorithm>
#include <cstring>
#include <cstdio>
#include <queue>
#include <cmath>
 
#define REDIRECT(x) freopen(x".in", "r", stdin), freopen(x".out", "w", stdout)
#define CLOSEALL() fclose(stdin), fclose(stdout)
 
using namespace std;
 
const int MAXN = 800 + 5;
const int DIRX[] =
{ 1, -1, 0, 0 };
const int DIRY[] =
{ 0, 0, 1, -1 };
 
int H, W, K;
int stX, stY;
char mz[MAXN][MAXN];
bool vist[MAXN][MAXN];
 
int answer = 0x7F7F7F7F;
 
void BFS()
{
	queue<pair<pair<int, int>, int> > Q;
	Q.push(make_pair(make_pair(stX, stY), 0));
 
	while (!Q.empty())
	{
		pair<pair<int, int>, int> cur = Q.front();
		Q.pop();
 
		if(vist[cur.first.first][cur.first.second])
			continue;
		vist[cur.first.first][cur.first.second] = true;
 
		int curAns = min(min(cur.first.first - 1, H - cur.first.first),
				min(cur.first.second - 1, W - cur.first.second));
		curAns = (curAns + K - 1) / K;
		answer = min(answer, curAns + 1);
 
		if (cur.second >= K)
			continue;
 
		for (int i = 0; i < 4; i++)
		{
			pair<int, int> newPos = make_pair(cur.first.first + DIRX[i],
					cur.first.second + DIRY[i]);
			if(newPos.first <= 0 || newPos.first > H)
				continue;
			if(newPos.second <= 0 || newPos.second > W)
				continue;
			if(mz[newPos.first][newPos.second] != '#' && !vist[newPos.first][newPos.second])
				Q.push(make_pair(newPos, cur.second + 1));
		}
	}
}
 
int main()
{
 
	//REDIRECT("room");
 
	scanf("%d%d%d", &H, &W, &K);
	for (int i = 1; i <= H; i++)
	{
		scanf("%s", mz[i] + 1);
		for (int j = 1; j <= W; j++)
			if (mz[i][j] == 'S')
				stX = i, stY = j;
	}
 
	BFS();
 
	printf("%d\n", answer);
 
	CLOSEALL();
	return 0;
}