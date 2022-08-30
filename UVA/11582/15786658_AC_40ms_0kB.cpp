#include <iostream>
using namespace std;

typedef unsigned long long u64;

const int MAXN = 1000;

int Fib[MAXN * MAXN + 10];
int getFib(int MOD)
{
	Fib[0] = 0;
	Fib[1] = 1;

	for(int i = 2; true; i++)
	{
		Fib[i] = (Fib[i-1] + Fib[i-2]) % MOD;

		if(Fib[i - 1] == 0 && Fib[i] == 1)
			return i - 1;
	}
	return -1;
}

u64 FastPow(u64 base, u64 exp, int MOD)
{
	base = base % MOD;
	u64 ans = 1ULL;
	while(exp)
	{
		if(exp & 1)
			ans = ans * base % MOD;
		base = base * base % MOD;
		exp = exp >> 1;
	}
	return ans;
}

int main() {
	ios::sync_with_stdio(false);

	int kase;

	cin >> kase ;
	while(kase--)
	{
		u64 A, B;
		int N;
		cin >> A >> B >> N ;
		
		if(A == 0 || N == 1)
		{
			cout << "0" << endl ;
			continue;
		}

		int modulus = getFib(N);
		cout << Fib[FastPow(A, B, modulus)] << endl ;
	}

	return 0;
}
