#include <bits/stdc++.h>
using namespace std;

typedef long long i64;
class SettingShield
{
	static const int MAXN = 100000 + 100;

	int N, H, T;
	int prot[MAXN], rval[MAXN], pnum[MAXN];
	int cL, cR;

	void decrypt(int n, int h, int t, vector<int> val0, vector<int> a,
			vector<int> b, vector<int> m);
	i64 f(int p);
public:
	i64 getOptimalCost(int n, int h, int t, vector<int> val0, vector<int> a,
			vector<int> b, vector<int> m);
};

void SettingShield::decrypt(int n, int h, int t, vector<int> val0,
		vector<int> a, vector<int> b, vector<int> m)
{
	memset(rval, 0xFF, sizeof rval);

	N = n, H = h, T = t;
	prot[0] = val0[0];
	for (int i = 1; i < N; i++)
		prot[i] = (1LL * a[0] * prot[i - 1] + b[0]) % m[0];

	cL = val0[1], cR = val0[2];
	rval[cL] = max(rval[cL], cR);
	for (int i = 1; i < H; i++)
	{
		int nL = min(1LL * N - 1, (1LL * a[1] * cL + b[1]) % m[1]);
		int dist = cR - cL;
		int nR = min(1LL * N - 1, (1LL * a[2] * dist + b[2]) % m[2]);
		cL = nL, cR = nR;
		rval[cL] = max(rval[cL], cR);
	}

	for (int i = 1; i < N; i++)
		rval[i] = max(rval[i], rval[i - 1]);
}

inline i64 SettingShield::f(int p)
{
	i64 c = 1LL * p * T;
	int cnt = p;
	memset(pnum, 0x00, sizeof pnum);

	for(int i = 0; i < N; i++)
	{
		cnt -= pnum[i];
		if(prot[i] > cnt)
		{
			int diff = prot[i] - cnt;
			c += diff;
			cnt += diff;
			pnum[rval[i] + 1] += diff;
		}
	}
	return c;
}

inline i64 SettingShield::getOptimalCost(int n, int h, int t, vector<int> val0,
		vector<int> a, vector<int> b, vector<int> m)
{
	decrypt(n, h, t, val0, a, b, m);

	int Lo = 0, Hi = 1;
	for (int i = 0; i < N; i++)
		if (rval[i] < i)
			Lo = max(Lo, prot[i]);
	for (int i = 0; i < N; i++)
		Hi = max(Hi, prot[i]);

	while (Hi - Lo > 5)
	{
		int mid1 = (2 * Lo + Hi) / 3;
		int mid2 = (2 * Hi + Lo) / 3;

		if (f(mid1) > f(mid2))
			Lo = mid1;
		else
			Hi = mid2;
	}

	i64 res = 0x7F7F7F7F7F7F7F7F;
	for (int i = Lo; i <= Hi; i++)
		res = min(res, f(i));
	return res;

}
