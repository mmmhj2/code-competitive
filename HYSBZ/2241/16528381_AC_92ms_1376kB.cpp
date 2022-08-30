#include <bits/stdc++.h>
using namespace std;

const int MAXN = 100 + 5;

int sum;
int N, M;
int a[MAXN][MAXN];

bool check(int x, int y)
{
	static int prefix[MAXN][MAXN];

	if(sum % (x * y))
		return false;
	memset(prefix, 0x00, sizeof prefix);

	for(int i = 1; i <= M; i++)
		for(int j = 1; j <= N; j++)
		{
			prefix[i][j] += prefix[i-1][j] + prefix[i][j-1] - prefix[i-1][j-1];
			if(prefix[i][j] > a[i][j])
				return false;

			int delta = a[i][j] - prefix[i][j];
			if(((i > M - x + 1) || (j > N - y + 1)) && delta)
				return false;
			if(!delta)
				continue;
			prefix[i][j] += delta;
			prefix[i+x][j] -= delta;
			prefix[i][j+y] -= delta;
			prefix[i+x][j+y] += delta;
		}
	return true;
}

int main()
{
	int ans = 0;
	cin >> M >> N ;
	for(int i = 1; i <= M; i++)
		for(int j = 1; j <= N; j++)
			cin >> a[i][j], sum += a[i][j];

	for(int i = M; i >= 1; i--)
		for(int j = N; j >= 1; j--)
			if(i * j > ans && check(i, j))
				ans = i * j;
	cout << sum / ans << endl ;
}




