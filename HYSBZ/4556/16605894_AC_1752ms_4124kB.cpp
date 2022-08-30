// BZOJ3238 差异
#include <bits/stdc++.h>
using namespace std;
typedef long long i64;
const int MAXN = 100000 + 10;

int N, M;
char s[MAXN];

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

	getHeight();

	memset(rk1, 0x00, (sizeof (int)) * (N + 1));
	for(int i = 1; i <= N; i++)
		rk1[sa1[i] - 1] = i;
}
}

int solve(int a, int b, int c, int d)
{
	using namespace SuffixArray;
	int len1 = 0, len2 = 0x7F7F7F7F;
	int sfx = rk1[c - 1];

	if(sa1[sfx] >= a && sa1[sfx] <= b)
		len1 = max(len1, min(d - c + 1, b - sa1[sfx] + 1));
	for(int i = sfx; i > 1; i--)
	{
		if(h[i] == 0 || h[i] <= len1)
			break;
		if(sa1[i-1] >= a && sa1[i-1] <= b)
			len1 = max(len1, min(min(min(len2, h[i]), b - sa1[i-1] + 1), d - c + 1));
		len2 = min(len2, h[i]);
	}

	len2 = 0x7F7F7F7F;
	for(int i = sfx + 1; i <= N; i++)
	{
		if(h[i] == 0 || h[i] <= len1)
			break;
		if(sa1[i] >= a && sa1[i] <= b)
			len1 = max(len1, min(min(min(len2, h[i]), b - sa1[i] + 1), d - c + 1));
		len2 = min(len2, h[i]);
	}
	return len1;
}

int main()
{

	scanf("%d%d%s", &N, &M, s + 1), N = strlen(s + 1);
	for(int i = 1; i <= N; i++)
		SuffixArray::w[i] = s[i] - 'a' + 1;
	SuffixArray::suffixArray();

	for(int i = 1; i <= M; i++)
	{
		int a, b, c, d;
		scanf("%d%d%d%d", &a, &b, &c, &d);
		printf("%d\n", solve(a, b, c, d));
	}

	return 0;
}
