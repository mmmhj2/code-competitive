#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

typedef long long i64;
typedef unsigned long long u64;

int dfs(u64 n, int p)
{
	u64 t;
	for(int i = p - 2, j = 1; i >= 0; i--, j++)
	{
		t = (i == 0 ? 1 : 1ULL << (i - 1));

		for(int k = 0; k < j; k++)
			if(t < n)
				n -= t;
			else
				return dfs(n, i);
	}
	return p;
}

int solve(u64 n)
{
	if(n <= 1)
		return 0;
	n -= 1;

	int i = 0;

	while(true)
	{
		u64 t = 1ULL << i;

		if(t < n)
			n -= t;
		else
			return dfs(n, i + 1);

		i++;
	}

}

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	
	u64 N;
	while(cin >> N && N)
	{
		cout << solve (N) << endl ;
	}
}

