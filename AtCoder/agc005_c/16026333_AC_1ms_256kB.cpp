#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

const int MAXN = 100 + 5;

int N, mx;
int A[MAXN], cnt[MAXN];

class noSolution: std::exception
{

};

void findSolution()
{
	if (mx & 1)
	{
		int loBound = mx - mx / 2;

		for (int i = loBound; i <= mx; i++)
		{
			cnt[i] -= 2;
			if (cnt[i] < 0)
				throw noSolution();
		}
		for (int i = loBound; i > 0; i--)
			if (cnt[i])
				throw noSolution();
	}
	else
	{
		int half = mx / 2;
		if (!cnt[half])
			throw noSolution();
		cnt[half] --;

		for (int i = half + 1; i <= mx; i++)
		{
			cnt[i] -= 2;
			if (cnt[i] < 0)
				throw noSolution();
		}
		for (int i = half; i > 0; i--)
			if (cnt[i])
				throw noSolution();

	}
}

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	cin >> N;
	for (int i = 1; i <= N; i++)
		cin >> A[i], mx = max(mx, A[i]), cnt[A[i]]++;

	try
	{
		findSolution();
	}
	catch(noSolution &x)
	{
		cout << "Impossible" << endl ;
		return 0;
	}
	cout << "Possible" << endl ;
	return 0;
}
