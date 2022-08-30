#include <bits/stdc++.h>
using namespace std;
typedef long long i64;
const int MAXN = 5000 + 10;
const int MOD = 1e9 + 7;

namespace ahoCorasick
{
struct _node
{
	static int eCnt;
	int ch[30];
	int fail;
	int endCnt;
} E[MAXN];
int _node::eCnt = 0;

void insert(char * s)
{
	int len = strlen(s), cur = 0;
	for (int i = 0; i < len; i++)
	{
		int x = s[i] - 'a';
		if (E[cur].ch[x] == 0)
			E[cur].ch[x] = ++_node::eCnt;
		cur = E[cur].ch[x];
	}
	E[cur].endCnt++;
}

void construct()
{
	queue<int> Q;
	for (int i = 0; i < 26; i++)
		if (E[0].ch[i])
			Q.push(E[0].ch[i]);

	while (!Q.empty())
	{
		int cur = Q.front();
		Q.pop();

		for(int i = 0; i < 26; i++)
		{
			int & ch = E[cur].ch[i];
			if(ch)
				E[ch].fail = E[E[cur].fail].ch[i],
				E[ch].endCnt |= E[E[ch].fail].endCnt,
				Q.push(ch);
			else
				ch = E[E[cur].fail].ch[i];
		}
	}
}
}

i64 L;
int N, M;
int lnk[MAXN][110];

char basicString[110][MAXN];
int strLen[110];

namespace solve1
{
int dp[MAXN][110];

void solve()
{
	dp[0][0] = 1;
	for(int l = 0; l < L; l++)
		for(int i = 0; i <= ahoCorasick::_node::eCnt; i++)
			if(dp[i][l])
				for(int j = 1; j <= N; j++)
					if(lnk[i][j] >= 0 && l + strLen[j] <= L)
						dp[lnk[i][j]][l + strLen[j]] = (1LL * dp[lnk[i][j]][l + strLen[j]] + dp[i][l]) % MOD;
	i64 ans = 0;
	for(int i = 0; i <= ahoCorasick::_node::eCnt; i++)
		if(!ahoCorasick::E[i].endCnt)
			ans = (ans + dp[i][L]) % MOD;
	printf("%lld\n", ans);
}

}

namespace solve2
{

const int MATRIX_SIZE = MAXN * 2;
int matSiz;
int ansMat[MATRIX_SIZE][MATRIX_SIZE];
int dpMat[MATRIX_SIZE][MATRIX_SIZE];

void matrixMult(int x[MATRIX_SIZE][MATRIX_SIZE], const int y[MATRIX_SIZE][MATRIX_SIZE])
{
	static int result[MATRIX_SIZE][MATRIX_SIZE];
	memset(result, 0x00, sizeof result);

	for(int i = 0; i <= matSiz; i++)
		for(int j = 0; j <= matSiz; j++)
			for(int k = 0; k <= matSiz; k++)
				result[i][j] = (result[i][j] + 1LL * x[i][k] * y[k][j] % MOD) % MOD;

	memcpy(x, result, sizeof result);
}

void solve()
{
	matSiz = ahoCorasick::_node::eCnt * 2 + 1;

	for(int i = 0; i <= ahoCorasick::_node::eCnt; i++)
	{
		for(int j = 1; j <= N; j++)
			if(lnk[i][j] >= 0)
			{
				if(strLen[j] == 1)
					dpMat[lnk[i][j] * 2][i * 2]++;
				else
					dpMat[lnk[i][j] * 2][i * 2 + 1]++;
			}
		dpMat[i * 2 + 1][i * 2] = 1;
	}
	ansMat[0][0] = 1;

	while(L)
	{
		if(L & 1)
			matrixMult(ansMat, dpMat);
		matrixMult(dpMat, dpMat);
		L = L >> 1;
	}

	i64 ans = 0;
	for(int i = 0; i <= ahoCorasick::_node::eCnt; i++)
		if(!ahoCorasick::E[i].endCnt)
			ans = (ans + ansMat[i * 2][0]) % MOD;
	printf("%lld\n", ans);
}
}

int main()
{
	scanf("%d%d%lld", &N, &M, &L);
	for(int i = 1; i <= N; i++)
		scanf("%s", basicString[i]), strLen[i] = strlen(basicString[i]);
	for(int i = 1; i <= M; i++)
		scanf("%s", basicString[N + 1]),
		ahoCorasick::insert(basicString[N + 1]);
	ahoCorasick::construct();

	memset(lnk, 0xFF, sizeof lnk);
	for(int k = 1; k <= N; k++)
		for(int i = 0; i <= ahoCorasick::_node::eCnt; i++)
		{
			int cur = i;
			for(int j = 0; j < strLen[k]; j++)
				if(!ahoCorasick::E[cur].endCnt)
					cur = ahoCorasick::E[cur].ch[basicString[k][j] - 'a'];
				else
					break;

			if(!ahoCorasick::E[cur].endCnt)
				lnk[i][k] = cur;
		}

	if(L <= 100)
		solve1::solve();
	else
		solve2::solve();

	return 0;
}
