#include <bits/stdc++.h>
using namespace std;
typedef long long i64;

const int MAXN = 200000 + 10;

int N, M;
int A[MAXN];
int answer;

int covCnt[MAXN], ptr[MAXN];

void addSeg(int x)
{
	int newL = x - covCnt[x];
	covCnt[x] ++;
	if(newL > 0)
		ptr[newL]++;
	if(newL > 0 && ptr[newL] == 1)
		answer--;
}

void removeSeg(int x)
{
	covCnt[x]--;
	int newL = x - covCnt[x];
	
	if(newL > 0)
		ptr[newL]--;
	if(newL > 0 && ptr[newL] == 0)
		answer++;
}

int main()
{
	ios::sync_with_stdio(false), cin.tie(nullptr);

	cin >> N >> M;
	for(int i = 1; i <= N; i++)
		cin >> A[i], addSeg(A[i]);
	answer += N;

	for(int i = 1; i <= M; i++)
	{
		int x, y;
		cin >> x >> y ;
		removeSeg(A[x]);
		A[x] = y;
		addSeg(A[x]);
		cout << answer << endl ;
	}

	return 0;
}

