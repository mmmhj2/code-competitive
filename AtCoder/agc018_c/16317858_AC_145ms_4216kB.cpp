#include <bits/stdc++.h>
#include <tuple>
using namespace std;
typedef long long i64;
const int MAXN = 200000 + 10;

typedef tuple<int, int, int> person;

int x, y, z, N;
person p[MAXN];
i64 sumx[MAXN], sumy[MAXN];

int main()
{
	cin >> x >> y >> z;
	N = x + y + z;
	for (int i = 1; i <= N; i++)
		cin >> get<0>(p[i]) >> get<1>(p[i]) >> get<2>(p[i]);
	sort(p + 1, p + N + 1, [](const person & a, const person & b) -> bool
	{	return ((get<0>(a) - get<1>(a)) > (get<0>(b) - get<1>(b)));});

	i64 sum = 0;
	priority_queue<int> PQ;

	for(int i = 1; i <= N; i++)
	{
		PQ.push(get<2>(p[i]) - get<0>(p[i]));
		sum += get<2>(p[i]) - get<0>(p[i]);

		if(PQ.size() > x)
			sum -= PQ.top(), PQ.pop();
		sumx[i] = sum;

	}

	sum = 0;
	while(!PQ.empty())
		PQ.pop();
	for(int i = N; i > 0; i--)
	{
		PQ.push(get<2>(p[i]) - get<1>(p[i]));
		sum += get<2>(p[i]) - get<1>(p[i]);
		if(PQ.size() > y)
			sum -= PQ.top(), PQ.pop();
		sumy[i] = sum;
	}

	i64 answer = -0x7F7F7F7F7F7F7F7FLL;
	for(int i = x; i <= N - y; i++)
		answer = max(answer, -(sumx[i] + sumy[i+1]));
	for(int i = 1; i <= N; i++)
		answer += get<2>(p[i]);
	cout << answer << endl;
}
