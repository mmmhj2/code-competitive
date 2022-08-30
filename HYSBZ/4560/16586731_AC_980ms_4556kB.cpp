#include <cstdio>
#include <cstring>
#include <iostream>
using namespace std;

const int MAXN = 10000 + 10;
int N, M;
int len[5], vis[5], ch[MAXN];
char S[MAXN];
int f[MAXN][16], g[MAXN][16];
int sg[MAXN][16];

struct FenwickTree
{
	int s[MAXN], typ;
	inline int cmp(int a, int b)
	{
		return ((a > b) ^ typ) ? a : b;
	}
	inline void update(int x, int v)
	{
		x++;
		for (int i = x; i; i -= i & -i)
			s[i] = cmp(s[i], v);
	}
	inline int query(int x)
	{
		x++;
		int i, ret = s[0];
		for (i = x; i <= M + 1; i += i & -i)
			ret = cmp(ret, s[i]);
		return ret;
	}
} s1[16], s2[16];

void KMP_prepare()
{
	static char T[5][MAXN];
	static int nxt[MAXN];
	for (int i = 1; i <= N; i++)
	{
		int j, k;
		memset(nxt, 0, sizeof(nxt));
		scanf("%s", T[i]), len[i] = strlen(T[i]);
		nxt[0] = k = -1, j = 0;
		while (j < len[i])
			if (k == -1 || T[i][j] == T[i][k])
				nxt[++j] = ++k;
			else
				k = nxt[k];
		j = k = 0;
		while (j < M)
		{
			if (k == -1 || S[j] == T[i][k])
				j++, k++;
			else
				k = nxt[k];
			if (k == len[i])
				ch[j - len[i]] |= 1 << (i - 1);
		}
	}
	memset(vis, 0, sizeof(vis));
	for (int a = 1; a <= N; a++)
		for (int b = 1; b <= N; b++)
			if (a != b && !vis[a] && !vis[b])
			{
				int j, k;
				memset(nxt, 0, sizeof(nxt));
				nxt[0] = k = -1, j = 0;
				while (j < len[a])
					if (k == -1 || T[a][j] == T[a][k])
						nxt[++j] = ++k;
					else
						k = nxt[k];
				j = k = 0;
				while (j < len[b])
				{
					if (k == -1 || T[b][j] == T[a][k])
						j++, k++;
					else
						k = nxt[k];
					if (k == len[a])
					{
						vis[a] = 1;
						break;
					}
				}
			}
}

void DP()
{
	memset(s1, 0xc0, sizeof(s1)), memset(s2, 0x3f, sizeof(s2)), memset(sg, 0x3f,
			sizeof(sg)), memset(f, 0xc0, sizeof(f)), memset(g, 0x3f, sizeof(g));

	for (int i = 0; i < 1 << N; i++)
		s1[i].typ = 0, s2[i].typ = 1, f[0][i] = -1 << 30, g[0][i] = 1 << 30;
	for (int i = 0; i <= M; i++)
		for (int j = 0; j < 1 << N; j++)
		{
			if (!i)
			{
				if (!j)
					f[0][0] = g[0][0] = sg[0][0] = 0;
				else
					f[0][j] = s1[j].query(i) + i, g[0][j] = s2[j].query(i) + i;
			}
			else
				f[i][j] = max(f[i][j], f[i - 1][j]), sg[i][j] = min(sg[i][j],
						sg[i - 1][j]), f[i][j] = max(f[i][j],
						s1[j].query(i) + i), g[i][j] = min(sg[i][j],
						s2[j].query(i) + i);
			for (int k = 1; k <= N; k++)
				if (!((j >> (k - 1)) & 1) && ((ch[i] >> (k - 1)) & 1))
				{
					s1[j | (1 << (k - 1))].update(i + len[k], f[i][j] - i), f[i
							+ len[k]][j | (1 << (k - 1))] = max(
							f[i + len[k]][j | (1 << (k - 1))], f[i][j] + len[k]);
					if (!vis[k])
						s2[j | (1 << (k - 1))].update(i + len[k], g[i][j] - i), sg[i
								+ len[k]][j | (1 << (k - 1))] = min(
								sg[i + len[k]][j | (1 << (k - 1))],
								g[i][j] + len[k]);
				}
		}
}

void work()
{
	scanf("%s", S), M = strlen(S);
	scanf("%d", &N);
	int tmp = (1 << N) - 1;
	memset(ch, 0, sizeof(ch));

	KMP_prepare();

	for (int i = 1; i <= N; i++)
		if (vis[i])
			tmp ^= 1 << (i - 1);

	DP();

	int ans = 0;
	for (int i = 1; i < 1 << N; i++)
		if ((i & tmp) == tmp)
			ans = max(ans, f[M][i]);

	printf("%d %d\n", g[M][tmp], ans);
}

int main()
{
	int T;
	scanf("%d", &T);
	while (T--)
		work();
	return 0;
}
