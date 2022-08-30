#include <bits/stdc++.h>
using namespace std;

typedef long long i64;
const i64 INF = 1e16;
const int MAXN = 100000 + 10;

struct edge
{
	static int eCnt;
	i64 to, w;
	edge * nxt;
}E[MAXN];
int edge::eCnt = 0;

edge * head[MAXN];
void addEdge(i64 u, i64 v, i64 w)
{
	edge * p = &E[++edge::eCnt];
	p->to = u, p->w = w;
	p->nxt = head[v], head[v] = p;
}

i64 N;
i64 a[MAXN], b[MAXN];

void DFS(i64 cur, i64 fa, i64 p)
{
	for(edge * p = head[cur]; p; p = p->nxt)
		DFS(p->to, cur, p->w);

	if(a[cur] < b[cur])
		b[fa] += b[cur] - a[cur];
	else if(a[cur] > b[cur])
	{
		double t;
		t = 1.0 * (b[cur] - a[cur]) * p;
		if(t < -INF)
			exit((puts("NO"), 0));
		b[fa] += (b[cur] - a[cur]) * p;
		if(b[fa] < -INF)
			exit((puts("NO"), 0));
	}
}


int main()
{
	i64 v, w;
	ios::sync_with_stdio(false);
	cin >> N ;

	for(int i = 1; i <= N; i++)
		cin >> b[i] ;
	for(int i = 1; i <= N; i++)
		cin >> a[i] ;
	for(int i = 2; i <= N; i++)
		cin >> v >> w,
		addEdge(i, v, w);

	for(edge * p = head[1]; p; p = p->nxt)
		DFS(p->to, 1, p->w);

	cout << (b[1] >= a[1] ? "YES" : "NO") << endl ;

	return 0;
}
