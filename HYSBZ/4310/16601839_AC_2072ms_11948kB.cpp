// BZOJ4310 跳蚤
#include <bits/stdc++.h>
using namespace std;

typedef long long i64;
const int MAXN = 100000 + 10;

int len, K;

namespace SuffixArray
{
int cnt[MAXN], w[MAXN];
int height[MAXN];
int SA[MAXN];
int id[MAXN];
int arr[2][MAXN];

int *t, *rk;

void suffixArray(int len, int up)
{
	int d(1), p(0);
	t = arr[0], rk = arr[1];

	for (int i = 0; i < len; i++)
		cnt[rk[i] = w[i]]++;
	for (int i = 1; i < up; i++)
		cnt[i] += cnt[i - 1];
	for (int i = len - 1; i >= 0; i--)
		SA[--cnt[rk[i]]] = i;
	while (true)
	{
		for (int i = len - d; i < len; i++)
			id[p++] = i;
		for (int i = 0; i < len; i++)
			if (SA[i] >= d)
				id[p++] = SA[i] - d;

		for (int i = 0; i < up; i++)
			cnt[i] = 0;
		for (int i = 0; i < len; i++)
			cnt[t[i] = rk[id[i]]]++;
		for (int i = 1; i < up; i++)
			cnt[i] += cnt[i - 1];
		for (int i = len - 1; i >= 0; i--)
			SA[--cnt[t[i]]] = id[i];

		p = 1;
		swap(t, rk);
		rk[SA[0]] = 0;

		for (int i = 0; i < len - 1; i++)
			if (SA[i] + d < len && SA[i + 1] + d < len
					&& t[SA[i]] == t[SA[i + 1]]
					&& t[SA[i] + d] == t[SA[i + 1] + d])
				rk[SA[i + 1]] = p - 1;
			else
				rk[SA[i + 1]] = p++;
		if (p == len)
			break;
		d = d << 1, up = p, p = 0;
	}
}

void getHeight(int len)
{
	int *rnk = arr[1];
	for (int i = 1; i <= len; i++)
		rnk[SA[i]] = i;
	for (int i = 0, k = 0; i < len; i++)
	{
		int x = SA[rnk[i] - 1];
		k = max(k - 1, 0);
		while (w[x + k] == w[i + k])
			k++;
		height[rnk[i]] = k;
	}
}
}

namespace doubling
{
int fa[MAXN][20];

void construct()
{
	using namespace SuffixArray;
	for (int i = 1; i <= len; i++)
		fa[i][0] = height[i];
	for (int k = 1; k < 20; k++)
		for (int i = 1; i <= len - (1 << (k - 1)); i++)
			fa[i][k] = min(fa[i][k - 1], fa[i + (1 << (k - 1))][k - 1]);
}

int LCP(int a, int b)
{
	using namespace SuffixArray;
	if (a == b)
		return len - SA[a];
	if (a > b)
		swap(a, b);
	int k = log2(b - a);
	return min(fa[a + 1][k], fa[b - (1 << k) + 1][k]);
}

}

int Ls, Rs;
int Lans, Rans;
i64 sum;

char s[MAXN];

void kth(i64 x)
{
	using namespace SuffixArray;
	i64 t = x;
	for (int i = 1; i <= len; i++)
		if (t > len - SA[i] - height[i])
			t -= len - SA[i] - height[i];
		else
			return Ls = SA[i], Rs = SA[i] + height[i] + t - 1, (void) 0;
}

bool compare(int x1, int y1, int x2, int y2)
{
	using namespace SuffixArray;
	int L1 = y1 - x1 + 1, L2 = y2 - x2 + 1;
	int lcp = doubling::LCP(arr[1][x1], arr[1][x2]);

	if(lcp >= L1)
		return L1 <= L2;
	else if(lcp >= L2)
		return false;
	return s[x1 + lcp] <= s[x2 + lcp];
}

bool check()
{
	int last = len - 1, cnt = 1;
	for(int i = len - 1; i >= 0; i--)
		if(s[i] > s[Ls])
			return false;
		else if(!compare(i, last, Ls, Rs))
		{
			cnt++, last = i;
			if(cnt > K)
				return false;
		}
	return true;
}

int main()
{
	scanf("%d%s", &K, s), len = strlen(s);
	for(int i = 0; i < len; i++)
		SuffixArray::w[i] = s[i] - 'a' + 1;
	SuffixArray::suffixArray(len + 1, 28);
	SuffixArray::getHeight(len);

	for(int i = 1; i <= len; i++)
		sum += len - SuffixArray::SA[i] - SuffixArray::height[i];
	doubling::construct();

	i64 L = 1, R = sum;

	while(L <= R)
	{
		i64 mid = (L + R) >> 1;
		kth(mid);
		if(check())
			Lans = Ls, Rans = Rs, R = mid - 1;
		else
			L = mid + 1;
	}

	for(int i = Lans; i <= Rans; i++)
		putchar(s[i]);
	puts("");

	return 0;
}
