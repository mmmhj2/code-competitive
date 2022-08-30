#include <bits/stdc++.h>
using namespace std;

typedef long long i64;
const int MAXN = 1e5 + 10;

i64 answer;
int N, tmp;
int A[MAXN], B[MAXN];

multiset<int> a, b;

namespace disjointSet_map
{
	map<int, int> fa;

	void clear()
	{
		fa.clear();
	}

	void setCircle(int x)
	{
		fa[x] = x;
	}

	int find(int x)
	{
		if (fa[x] == x)
			return x;
		return fa[x] = find(fa[x]);
	}

	void merge(int x, int y)
	{
		fa[find(x)] = find(y);
	}
}

int main()
{
	cin >> N;

	for (int i = 1; i <= N; i++)
		cin >> A[i], A[0] ^= A[i];
	for (int i = 0; i <= N; i++)
		a.insert(A[i]);

	for (int i = 1; i <= N; i++)
		cin >> B[i], B[0] ^= B[i];
	for (int i = 0; i <= N; i++)
		b.insert(B[i]);

	if (a != b)
		return cout << "-1" << endl, 0;

	disjointSet_map::setCircle(A[0]);
	for (int i = 1; i <= N; i++)
		if (A[i] != B[i])
			disjointSet_map::setCircle(A[i]);

	for (int i = 1; i <= N; i++)
		if (A[i] != B[i])
			disjointSet_map::merge(A[i], B[i]), answer++;

	for_each(disjointSet_map::fa.begin(), disjointSet_map::fa.end(),
			[] (pair<int, int> x )
			{	answer += (x.first == x.second);});

	cout << answer - 1 << endl;

	return 0;
}
