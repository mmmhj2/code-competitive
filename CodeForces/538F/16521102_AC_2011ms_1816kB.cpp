// Codeforces538F A Heap of Heaps
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 2e5 + 10;

int N;
int a[MAXN], diff[MAXN];

int main()
{
	ios::sync_with_stdio(false);

	cin >> N ;
	for(int i = 1; i <= N; i++)
		cin >> a[i] ;

	for(int i = 2; i <= N; i++)
	{
		const int v = i - 2;
		for(int j = 1, last = 0; j <= v; j = last + 1)
		{
			last = v / (v / j);
			if(a[v/j + 1] > a[i])
				diff[j]++, diff[last + 1]--;
		}
		if(a[1] > a[i])
			diff[i-1]++, diff[N]--;
	}

	for(int i = 1; i < N; i++)
		diff[i] += diff[i-1];
	for(int i = 1; i < N; i++)
		cout << diff[i] << " \n"[i == N - 1] ;

	return 0;
}
