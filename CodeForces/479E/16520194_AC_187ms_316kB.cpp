// Codeforces479E Riding in a Lift
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 5000 + 10;
const int MOD = 1e9 + 7;

int N, A, B, K;
int dp1[MAXN], dp2[MAXN];
int prefix[MAXN];
int *dpOld, *dpNew;

int main()
{
	dpOld = dp1, dpNew = dp2;
	cin >> N >> A >> B >> K ;

	dpNew[A] = 1;
	for(int i = 1; i <= K; i++)
	{
		swap(dpNew, dpOld);
		prefix[0] = 0;
		for(int j = 1; j <= N; j++)
			prefix[j] = (prefix[j-1] + dpOld[j]) % MOD;

		for(int j = 1; j <= N; j++)
		{
			if(j == B)
				continue;
			else if(j < B)
				dpNew[j] = (prefix[(B - j - 1) / 2 + j] + MOD) % MOD;
			else
				dpNew[j] = (prefix[N] - prefix[j - (j - B + 1) / 2] + MOD) % MOD;
			dpNew[j] = (dpNew[j] - dpOld[j] + MOD) % MOD;
		}
	}

	int answer = 0;
	for(int i = 1; i <= N; i++)
		answer = (answer + dpNew[i]) % MOD;
	cout << answer << endl ;

	return 0;
}
