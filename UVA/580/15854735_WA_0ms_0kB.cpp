#include <algorithm>
#include <iostream>
#include <fstream>
#include <cstring>
#include <vector>
#include <cmath>
using namespace std;
typedef long long i64;
const int MAXN = 40;

i64 f[MAXN], g[MAXN];

void prepare()
{
	f[0] = f[1] = f[2] = 0;
	g[0] = 1, g[1] = 2, g[2] = 4;

	for(int i = 3; i <= 30; i++)
	{
		f[i] = 1LL << ( i - 3);

		for(int j = 2; j <= i - 2; j++)
			f[i] += g[j-2] * (1LL << (i - j - 2));

		g[i] = (1LL << i);
	}
}

int main()
{
	prepare();
	int N;
	while(cin >> N && N)
	{
		cout << f[N] << endl ;
	}
}

