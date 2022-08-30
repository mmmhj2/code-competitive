#include <algorithm>
#include <iostream>
#include <string>
using namespace std;
typedef long long i64;
typedef int *pint;
const int MAXN = 100 + 20;
 
int a[MAXN], b[MAXN];
int p1, p2;
int M = 100;
i64 N;
 
int main()
{
	p1 = 0, p2 = 0;
	cin >> N, N++;
 
	while (N > 1)
	{
		if (N & 1)
			a[++p1] = M, M--, N--;
		else
			b[++p2] = M, M--, N >>= 1;
	}
 
	cout << ((p1 + p2) << 1) << endl;
 
	for (int i = 1; i <= p1; i++)
		cout << a[i] << " ";
	for (int i = p2; i >= 1; i--)
		cout << b[i] << " ";
	for (int i = 100 - p1 - p2 + 1; i <= 100; i++)
		cout << i << " ";
	cout << endl;
 
	return 0;
}