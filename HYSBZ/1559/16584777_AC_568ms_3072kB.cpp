// BZOJ1559
#include <bits/stdc++.h>
using namespace std;

typedef long long i64;
const int MAXN = 100 + 10;
const int MAXM = 10 + 10;

namespace ahoCorasick
{
struct _node
{
	static int eCnt;
	int ch[30];
	int fail;
	int end;
} node[MAXN];
int _node::eCnt = 0;

void insert(const char * s, int p)
{
	int cur = 0;
	for (int i = 0; s[i] != '\0'; i++)
	{
		int f = s[i] - 'a';
		if (node[cur].ch[f] == 0)
			node[cur].ch[f] = ++_node::eCnt;
		cur = node[cur].ch[f];
	}
	node[cur].end |= 1 << (p - 1);
}

void buildFail()
{
	queue<int> Q;
	for (int i = 0; i < 26; i++)
		if (node[0].ch[i])
			Q.push(node[0].ch[i]);

	while (!Q.empty())
	{
		int cur = Q.front();
		Q.pop();
		for (int i = 0; i < 26; i++)
		{
			int & ch = node[cur].ch[i];
			if (ch)
				node[ch].fail = node[node[cur].fail].ch[i], Q.push(ch);
			else
				ch = node[node[cur].fail].ch[i];
		}
	}
}

void printTrie()
{
	for(int i = 0; i <= _node::eCnt; i++)
	{
		printf("%d : %d %d\n", i, node[i].fail, node[i].end);
		for(int j = 0; j < 26; j++)
			if(node[i].ch[j])
				printf("%c : %d ", 'a' + j, node[i].ch[j]);
		printf("\n");
	}
}

}

char s[MAXM][MAXM];
int len[MAXM], mthPos[MAXM][MAXM];

int getLnk(int x, int y)
{
	int i;
	for (i = min(len[x], len[y]); i; i--)
	{
		bool flag = true;
		for (int j = 0; j < i; j++)
			if (s[x][len[x] - i + j] != s[y][j])
			{
				flag = false;
				break;
			}
		if (flag)
			break;
	}
	return i;
}

bool del[MAXM], vis[MAXN];
string ans[50];
int pos[20];
int L, N;
int cnt, ansCnt;
i64 answer;

void DFS(int x)
{
	if (x > cnt)
	{
		ansCnt++;
		ans[ansCnt].clear();
		for (int i = 1; i < x; i++)
			for (int j = mthPos[pos[i - 1]][pos[i]]; j < len[pos[i]]; j++)
				//ans[ansCnt][k++] = s[pos[i]][j];
				ans[ansCnt].push_back(s[pos[i]][j]);
		if (ans[ansCnt].length() != L)
			ansCnt--;
		return;
	}
	for (int i = 1; i <= N; i++)
		if (!del[i] && !vis[i])
		{
			vis[i] = true;
			pos[x] = i;
			DFS(x + 1);
			vis[i] = false;
		}
}

bool cmpStr(int x, int y)
{
	for (int i = 0; i < L; i++)
		if (ans[x][i] != ans[y][i])
			return ans[x][i] < ans[y][i];
	return false;
}

i64 dp[2][MAXN][1 << 10];
int rnk[50];

int main()
{
	using namespace ahoCorasick;
	scanf("%d%d", &L, &N), cnt = N;
	for (int i = 1; i <= N; i++)
		scanf("%s", s[i]), len[i] = strlen(s[i]);

	for (int i = 1; i <= N; i++)
		for (int j = 1; j <= N; j++)
			mthPos[i][j] = getLnk(i, j);

	for (int i = 1; i <= N; i++)
		for (int j = 1; j <= N; j++)
			if (i != j && !del[i] && !del[j])
				if (len[i] >= len[j] && strstr(s[i], s[j]) != 0)
					del[j] = true, cnt--;

	for (int i = 1; i <= N; i++)
		if (!del[i])
			insert(s[i], i);
	buildFail();
	//printTrie();

	int dpCur = 0;
	dp[0][0][0] = 1;
	for(int i = 0; i < L; i++)
	{
		int x;
		memset(dp[dpCur ^ 1], 0, sizeof dp[dpCur ^ 1]);
		for(int j = 0; j <= _node::eCnt; j++)
			for(int k = 0; k < (1 << N); k++)
				if(dp[dpCur][j][k])
					for(int l = 0; l < 26; l++)
						x = node[j].ch[l],
						dp[dpCur ^ 1][x][k | node[x].end] += dp[dpCur][j][k];
		dpCur ^= 1;
	}

	int finalState = 0;
	for(int i = 1; i <= N; i++)
		if(!del[i])
			finalState |= 1 << (i-1);

	for(int i = 0; i <= _node::eCnt; i++)
		answer += dp[dpCur][i][finalState];
	printf("%lld\n", answer);

	if(answer <= 42)
	{
		DFS(1);
		sort(ans + 1, ans + answer + 1);
		for(int i = 1; i <= answer; i++)
			printf("%s\n", ans[i].c_str());
	}

}
