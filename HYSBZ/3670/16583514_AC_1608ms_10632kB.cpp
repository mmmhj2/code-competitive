// BZOJ3670 动物园
#include <bits/stdc++.h>
using namespace std;

typedef long long i64;
const int MAXN = 1000000 + 10;
const int MOD = 1e9 + 7;

int N;
string p;
int fail[MAXN], dep[MAXN];

void getFail()
{
	int i = 0, j = -1;
	fail[0] = -1, dep[0] = 0;
	while(i < p.length())
		if(j == -1|| p[i] == p[j])
			dep[++i] = dep[++j] + 1, fail[i] = j;
		else
			j = fail[j];
}

int main()
{
	cin >> N ;
	while(N--)
	{
		i64 ans = 1;
		int i = 0, j = -1;

		cin >> p ;
		getFail();

		while(i < p.length())
			if(j == -1 || p[i] == p[j])
			{
				i++, j++;
				while(j != -1 && (j * 2) > i)
					j = fail[j];
				if(j != -1 && i != -1)
					ans = ans * (1LL + dep[j]) % MOD;
			}
			else
				j = fail[j];

		cout << ans << endl ;
	}
	return 0;
}
