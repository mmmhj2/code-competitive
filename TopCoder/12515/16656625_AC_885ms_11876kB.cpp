#include <bits/stdc++.h>
using namespace std;

class WellTimedSearch
{
	int count(int x, int a, int n);
	int sum(int x, int y, int a, int b);
public:
	double getProbability(int N, int A, int B);
};

int WellTimedSearch::count(int x, int a, int n)
{
	if(x > 1 && a == 1)
		return -1;
	int ret = 0, tx = x;

	for(int i = a - 1; i >= 1; i--)
	{
		x = (x + 1) / 2;
		if(x > 1 && i == 1)
			return -1;
		if(x == 1)
		{
			ret += i;
			break;
		}
		ret += x;
	}
	if(ret + tx > n)
		return -1;
	ret = n - ret - tx;
	return ret;
}

int WellTimedSearch::sum(int x, int y, int a, int b)
{
	int ret = 0;
	for(int i = a + 1; i <= b; i++)
	{
		x *= 2, ret += x;
		if(ret >= y)
			return y;
	}
	return ret;
}

double WellTimedSearch::getProbability(int N, int A, int B)
{
	int ans = 0;
	for(int i = 1; i <= N; i++)
	{
		int p = count(i, A, N);
		if(p < 0)
			break;
		ans = max(ans, i + sum(i, p, A, B));
	}
	return 1.0 * ans / N;
}
