// BZOJ3238 差异
#include <bits/stdc++.h>
using namespace std;
typedef long long i64;
const int MAXN = 500000 + 10;

int N;
char s[MAXN];
i64 ans;

namespace SuffixArray
{
int w[MAXN];
int _sa[2][MAXN], _rk[2][MAXN];
int bin[MAXN], h[MAXN];
int *sa1, *rk1, *sa2, *rk2;

void radixSort(int * sa1, int * rk1, int * sa2, int * rk2, int k)
{
	for (int i = 1; i <= N; i++)
		bin[rk1[sa1[i]]] = i;
	for (int i = N; i > 0; i--)
		if (sa1[i] > k)
			sa2[bin[rk1[sa1[i] - k]]--] = sa1[i] - k;
	for (int i = N - k + 1; i <= N; i++)
		sa2[bin[rk1[i]]--] = i;
	for (int i = 1; i <= N; i++)
		rk2[sa2[i]] = rk2[sa2[i - 1]]
				+ (rk1[sa2[i - 1]] != rk1[sa2[i]]
						|| rk1[sa2[i - 1] + k] != rk1[sa2[i] + k]);
}

void suffixArray()
{
	sa1 = _sa[0], sa2 = _sa[1];
	rk1 = _rk[0], rk2 = _rk[1];
	for (int i = 1; i <= N; i++)
		bin[w[i]]++;
	for (int i = 1; i <= 30; i++)
		bin[i] += bin[i - 1];
	for (int i = 1; i <= N; i++)
		sa1[bin[w[i]]--] = i;
	for (int i = 1; i <= N; i++)
		rk1[sa1[i]] = rk1[sa1[i - 1]] + (w[sa1[i - 1]] != w[sa1[i]]);
	for (int k = 1; k < N; k <<= 1, swap(sa1, sa2), swap(rk1, rk2))
		radixSort(sa1, rk1, sa2, rk2, k);
}

void getHeight()
{
	for (int k = 0, i = 1; i <= N; i++)
	{
		int j = sa1[rk1[i] - 1];
		while (s[j + k] == s[i + k])
			k++;
		h[rk1[i]] = k;
		if (k > 0)
			k--;
	}
}
}

int L[MAXN], R[MAXN];

void solve()
{
	using namespace SuffixArray;
	static int stk[MAXN], top;

	top = 0;
	h[0] = 0x80808080;
	for (int i = 1; i <= N; i++)
		ans += 1LL * i * (N - 1);

	for (int i = 1; i <= N; i++)
	{
		while(h[i] <= h[stk[top]])
			top--;
		L[i] = stk[top] + 1;
		stk[++top] = i;
	}

	h[N + 1] =0x7F7F7F7F, top = 0;
	for(int i = N; i >= 1; i--)
	{
		while(h[i] < h[stk[top]])
			top--;
		R[i] = stk[top] - 1;
		stk[++top] = i;
	}

	for(int i = 1; i <= N; i++)
		ans -= 2LL * (i - L[i] + 1) * (R[i] - i + 1) * h[i];
}

int main()
{

	scanf("%s", s + 1), N = strlen(s + 1);
	for(int i = 1; i <= N; i++)
		SuffixArray::w[i] = s[i] - 'a' + 1;
	SuffixArray::suffixArray();
	SuffixArray::getHeight();
	solve();

	printf("%lld\n", ans);
	return 0;
}
