#include <algorithm>
#include <cstdio>
#include <vector>
using namespace std;

typedef long long i64;
const int MOD = 924844033;
const int MAXN = 200000 + 15;

int N;
int A[MAXN * 4], B[MAXN * 4], rev[MAXN * 4];
int fact[MAXN], inv[MAXN], siz[MAXN];

vector <int> Adj[MAXN];

template <class T>
inline T modularExp(T base, T exp)
{
	T ret(1);

	while(exp)
	{
		if(exp & 1)
			ret = 1LL * ret * base % MOD ;
		base = 1LL * base * base % MOD ;
		exp = exp >> 1;
	}

	return ret;
}

namespace NumberTheoryTransformation
{

const int PrimitiveRoot = 5;

inline int Get_wn(int i)
{
	return modularExp(PrimitiveRoot, (MOD - 1) / (i << 1));
}

void NTT(int * coef, int n, int f)
{
	for(int i = 0; i < n; i++)
		if(i < rev[i])
			swap(coef[i], coef[rev[i]]);

	for(int i = 1; i < n; i = i << 1)
	{
		int x, y, wn = Get_wn(i);

		for(int j = 0; j < n; j = j + i * 2)
			for(int k = 0, w = 1; k < i; k++, w = 1LL * w * wn % MOD)
				x = coef[j + k], y = 1LL * coef[j + k + i] * w % MOD,
				coef[j + k] = (x + y) % MOD, coef[j + k + i] = (x - y) % MOD;
	}

	if(f == 1)		// Inverted?
		return;
	reverse(coef + 1, coef + n);
	int inverse = modularExp(n, MOD - 2);
	for(int i = 0; i < n; i++)
		coef[i] = 1LL * coef[i] * inverse % MOD;
}

void convolution(int n)
{
	NTT(A, n, 1), NTT(B, n, 1);
	for(int i = 0; i < n; i++)
		A[i] = 1LL * A[i] * B[i] % MOD;
	NTT(A, n, -1);
}

}

void prepare()
{
	fact[0] = 1;
	for(int i = 1; i < MAXN; i++)
		fact[i] = 1LL * fact[i-1] * i % MOD;

	inv[MAXN - 1] = modularExp(fact[MAXN-1], MOD - 2);
	for(int i = MAXN - 1; i > 0; i--)
		inv[i-1] = 1LL * inv[i] * i % MOD;
}

void DFS(int cur)
{
	siz[cur] = 1;

	for(int to : Adj[cur])
	{
		if(siz[to])
			continue;
		DFS(to);

		siz[cur] += siz[to];
		A[siz[to]] --, A[N - siz[to]]--;
	}
}

int main()
{
	int s, l = 0;
	prepare();

	scanf("%d", &N), A[N] = N;

	for(int i = 1; i < N; i++)
	{
		int u, v;
		scanf("%d%d", &u, &v);
		Adj[u].push_back(v), Adj[v].push_back(u);
	}

	DFS(1);

	for(int i = 1; i <= N; i++)
		A[i] = 1LL * A[i] * fact[i] % MOD;
	for(int i = 0; i <= N; i++)
		B[i] = inv[N - i];

	for(s = 1; s <= N * 2; s = s * 2)
		l++;
	for(int i = 0; i < s; i++)
		rev[i] = ((rev[i >> 1] >> 1) | ((i & 1) << (l - 1)));

	NumberTheoryTransformation::convolution(s);
	for(int i = 1; i <= N; i++)
		printf("%lld\n", 1LL * (A[N + i] + MOD) * inv[i] % MOD);
}
