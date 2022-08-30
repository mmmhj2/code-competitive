#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

typedef long long i64;
typedef unsigned long long u64;

const int MAXN = 30000000 + 6;

int ans[MAXN];

void prepare()
{
	for(int C = 1; C <= MAXN / 2; C++)
	{
		for(int A = C << 1; A < MAXN; A += C)
		{
			int B = A - C;

			if((A xor B) == C)
				ans[A] ++;
		}
	}

	for(int i = 1; i < MAXN; i++)
		ans[i] += ans[i-1];
}

int main()
{
	ios::sync_with_stdio(false);

	prepare();

	int K;
	cin >> K;
	for(int CaseCnt = 1; CaseCnt <= K; CaseCnt++)
	{
		int N;
		cin >> N ;
		cout << "Case " << CaseCnt << ": " << ans[N] << endl ;
	}
}
