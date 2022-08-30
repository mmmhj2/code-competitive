#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
using namespace std;
 
const int MAXN = 1e5 + 10;
 
int N, M;
int C[MAXN];
 
int main()
{
	cin >> N >> M;
	for(int i = 1; i <= M; i++)
	{
		int u, v;
		cin >> u >> v;
		C[u]++, C[v]++;
	}
 
	for(int i = 1; i <= N; i++)
		if(C[i] & 1)
		{
			cout << "NO" << endl;
			return 0;
		}
 
	cout << "YES" << endl ;
 
	return 0;
}
 