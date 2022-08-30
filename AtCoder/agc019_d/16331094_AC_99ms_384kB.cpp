#include <algorithm>
#include <iostream>
#include <cstring>
#include <string>
using namespace std;

const int MAXN = 2000 + 10;

int N;
string a, b;
int answer = 0x7F7F7F7F;
int asum, bsum;

int pre[MAXN], nxt[MAXN], mx[MAXN];
void solve()
{
	memset(pre, 0x00, sizeof pre);
	memset(nxt, 0x00, sizeof nxt);
	for(int i = 0; i < N; i++)
	{
		for(int j = 0; j < N; j++)
			if(b[(i-j+N) % N] == '1')
			{
				pre[i] = j;
				break;
			}
		for(int j = 0; j < N; j++)
			if(b[(i+j)%N]  == '1')
			{
				nxt[i] = j;
				break;
			}
	}

	for(int i = 0; i < N; i++)
	{
		int tCnt = 0;
		memset(mx, 0x00, sizeof mx);
		for(int j = 0; j < N; j++)
			if(a[j] != b[(i + j) % N])
				tCnt++, mx[pre[j]] = max(mx[pre[j]], nxt[j]);
		int mn = 0x7F7F7F7F, cnt = i;
		for(int j = N - 1; j >= 0; j--)
			mn = min(mn, cnt + j), cnt = max(cnt, mx[j]);
		answer = min(answer, 2 * mn - i + tCnt);
	}
}

int main()
{
	cin >> a >> b ;
	N = a.length();

	for(const auto & x : a)
		if(x == '1')
			asum++;
	for(const auto & x : b)
		if(x == '1')
			bsum++;

	if(asum == 0 && bsum == 0)
		return cout << 0 << endl, 0;
	else if(bsum == 0)
		return cout << -1<< endl, 0;

	solve();
	reverse(a.begin(), a.end()), reverse(b.begin(), b.end());
	solve();
	cout << answer << endl ;
	return 0;

}
