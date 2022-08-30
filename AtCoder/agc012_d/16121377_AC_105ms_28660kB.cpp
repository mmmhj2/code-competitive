#include <algorithm>
#include <cassert>
#include <cstring>
#include <cstdio>
#include <vector>

#define REDIRECT(x) freopen(x".in", "r", stdin), freopen(x".out", "w", stdout)
#define CLOSEALL() fclose(stdin), fclose(stdout)
#define eprintf(...) fprintf(stderr, ##__VA_ARGS__), fflush(stderr)

using namespace std;

const int MAXN = 2e5 + 10;
const long long MOD = 1e9 + 7;
typedef long long i64;

template<class T>
T modularExp(T base, T  exp)
{
	T answer(1);
	while (exp)
	{
		if (exp & 1)
			answer = answer * base % MOD;
		base = base * base % MOD;
		exp = exp >> 1;
	}
	return answer;
}

int N, X, Y;
vector<int> Adj[MAXN], finalBlk;

vector <pair<int, int> > col[MAXN], smallest;

int C[MAXN], W[MAXN];
bool vist[MAXN];

int totCnt, colCnt[MAXN];

i64 answer;
i64 fact[MAXN], inv[MAXN];

inline void addEdge(int u, int v)
{
	Adj[u].push_back(v);
	Adj[v].push_back(u);
}

void prepare()
{
	fact[0] = 1;
	for (int i = 1; i < MAXN; i++)
		fact[i] = fact[i - 1] * i % MOD;

	inv[MAXN - 1] = modularExp(fact[MAXN - 1], MOD - 2) % MOD;
	for (int i = MAXN - 2; i >= 0; i--)
		inv[i] = inv[i + 1] * (i + 1) % MOD;
	//assert(inv[1] == 2);
}

void DFS(int cur)
{
	vist[cur] = true;
	totCnt++, colCnt[C[cur]]++;
	finalBlk.push_back(C[cur]);

	for(int to : Adj[cur])
		if(!vist[to])
			DFS(to);

}

int main()
{
	//REDIRECT("colorball");
	prepare();

	scanf("%d%d%d", &N, &X, &Y);

	for (int i = 1; i <= N; i++)
		scanf("%d%d", &C[i], &W[i]),
		col[C[i]].emplace_back(W[i], i);

	for(int i = 1; i <= N; i++)
	{
		if(col[i].empty())
			continue;
		sort(col[i].begin(), col[i].end());
		smallest.push_back(col[i].front());

		for(auto x = col[i].begin() + 1; x != col[i].end(); ++x)
			if(x->first + col[i].front().first <= X)
				addEdge(x->second, col[i].front().second);
	}

	sort(smallest.begin(), smallest.end());
	if(smallest.size() > 0)
		for(int i = 1; i <= N; i++)
		{
			if(C[i] == C[smallest.front().second])
				continue;
			if(W[i] + W[smallest.front().second] > Y)
				continue;
			addEdge(i, smallest.front().second);
		}

	if(smallest.size() > 1)
		for(auto x : col[C[smallest[0].second]])
			if(x.first + W[smallest[1].second] <= Y)
				addEdge(x.second, smallest[1].second);

	DFS(smallest.front().second);

	answer = fact[totCnt];
	for(int x : finalBlk)
		answer = answer * inv[colCnt[x]] % MOD,
		colCnt[x] = 0;

	printf("%lld\n", answer);

	return 0;
}
