#include <algorithm>
#include <iostream>
#include <cstring>
#include <cstdio>

using namespace std;

const int MAXN = 2e5 + 10;

int N;
int A[MAXN];
bool B[MAXN];

bool check(int mid)
{
	const int Nmid = (N + 1) >> 1;
	int Lft = 0, Rht = N + 1;

	for (int i = 1; i <= N; i++)
		B[i] = (A[i] >= mid);

	for (int i = Nmid; i > 1; i--)
		if (B[i] == B[i - 1])
		{
			Lft = i;
			break;
		}
	for (int i = Nmid; i < N; i++)
		if (B[i] == B[i + 1])
		{
			Rht = i;
			break;
		}
	if(Lft == 0 && Rht == N + 1)
		return B[1];
	else if(Nmid - Lft > Rht - Nmid)
		return B[Rht];
	else
		return B[Lft];
}

int main()
{
	cin >> N;
	N = (N << 1) - 1;
	for (int i = 1; i <= N; i++)
		cin >> A[i];

	// [L, R)
	int L = 1, R = N + 1;
	while (L + 1 < R)
	{
		int mid = (L + R) >> 1;
		//cerr << L << " " << mid << " " << R << endl ;

		if (check(mid))
			L = mid;
		else
			R = mid;
	}

	cout << L << endl;

	return 0;
}
