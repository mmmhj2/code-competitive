#include <bits/stdc++.h>
using namespace std;

typedef long long i64;
const int MAXN = 3e5 + 10;

int N, M;
i64 sumA, sumB;
int a[MAXN], b[MAXN];

int aLen, bLen;

int main()
{

	cin >> N ;
	for(int i = 1; i <= N; i++)
		cin >> a[i], sumA += a[i];
	cin >> M ;
	for(int i = 1; i <= M; i++)
		cin >> b[i], sumB += b[i];

	if(sumA != sumB)
		return cout << -1 << endl, 0;

	aLen = N, bLen = M;

	for(int i = 1, j = 1; i <= N && j <= M; i++, j++)
	{
		sumA = a[i], sumB = b[j];
		while(sumA != sumB)
			if(sumA > sumB)
				sumB += b[++j], bLen--;
			else
				sumA += a[++i], aLen--;

		if(i > N || j > M)
			return cout << -1 << endl, 0;
	}

	if(aLen != bLen)
		cout << -1 << endl ;
	else
		cout << aLen << endl ;
	return 0;
}
