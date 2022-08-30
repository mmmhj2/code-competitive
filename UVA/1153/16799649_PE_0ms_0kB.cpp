#include <bits/stdc++.h>
using namespace std;

const int MAXN = 800000 + 10;

int N;
struct order
{
	int q, d;
	bool operator < (const order & rhs) const
	{
		return (d < rhs.d || (d == rhs.d && q < rhs.q));
	}
}ord[MAXN];

int solve()
{
	long long sum = 0;
	priority_queue<int> Q;
	for(int i = 1; i <= N; i++)
	{
		if(ord[i].q + sum <= ord[i].d)
			Q.push(ord[i].q), sum += ord[i].q;
		else if (!Q.empty())
		{
			int top = Q.top();
			if(top > ord[i].q)
				Q.pop(), Q.push(ord[i].q), sum = sum - top + ord[i].q;
		}
	}
	return Q.size();
}

int main()
{
	int T;
	scanf("%d", &T);

	while(T--)
	{
		cin >> N ;
		for(int i = 1; i <= N; i++)
			cin >> ord[i].q >> ord[i].d;
		sort(&ord[1], &ord[N + 1]);
		cout << solve() << endl << endl ;
	}

	return 0;
}
