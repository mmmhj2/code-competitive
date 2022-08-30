#include<iostream>
#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<ctime>
#include<cmath>
#include<algorithm>
using namespace std;
#define MAXN 510
struct node
{
	double p[MAXN][MAXN];
	node()
	{
		memset(p, 0, sizeof(p));
	}
} a;
int n, l, m, cnt, id, fail[MAXN], ed[MAXN], pos[MAXN], q[MAXN], tr[MAXN][27];
double chty[MAXN];
char ch[MAXN];
inline int read()
{
	int x = 0, f = 1;
	char ch = getchar();
	while (!isdigit(ch))
	{
		if (ch == '-')
			f = -1;
		ch = getchar();
	}
	while (isdigit(ch))
	{
		x = x * 10 + ch - '0';
		ch = getchar();
	}
	return x * f;
}
void insert()
{
	int now = 0;
	for (int i = 1; i <= l; i++)
	{
		if (!tr[now][ch[i] - 'A'])
			tr[now][ch[i] - 'A'] = ++cnt;
		now = tr[now][ch[i] - 'A'];
	}
	ed[now] = 1;
	pos[++id] = now;
}
void build()
{
	int head = 0, tail = 0;
	for (int i = 0; i < m; i++)
		if (tr[0][i])
			q[++tail] = tr[0][i];
	while (++head <= tail)
	{
		int x = q[head];
		ed[x] |= ed[fail[x]];
		for (int i = 0; i < m; i++)
		{
			if (!tr[x][i])
				tr[x][i] = tr[fail[x]][i];
			else
			{
				fail[tr[x][i]] = tr[fail[x]][i];
				q[++tail] = tr[x][i];
			}
		}
	}
}
void get()
{
	for (int i = 0; i <= cnt; i++)
	{
		if (ed[i])
			a.p[i][i] = 1;
		else
			for (int x = 0; x < m; x++)
				a.p[i][tr[i][x]] += chty[x];
	}
}
inline node operator *(node &x, node &y)
{
	node z;
	for (int i = 0; i <= cnt; i++)
		for (int j = 0; j <= cnt; j++)
			for (int k = 0; k <= cnt; k++)
				z.p[i][j] += x.p[i][k] * y.p[k][j];
	return z;
}
int main()
{
	n = read();
	l = read();
	m = read();
	for (int i = 0; i < m; i++)
		chty[i] = (double) read() / read();
	for (int i = 1; i <= n; i++)
	{
		scanf("%s", ch + 1);
		insert();
	}
	build();
	get();
	for (int i = 1; i <= 50; i++)
		a = a * a;
	for (int i = 1; i <= n; i++)
		printf("%.2lf\n", (double) a.p[0][pos[i]]);
	return 0;
}
