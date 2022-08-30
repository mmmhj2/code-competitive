#include <bits/stdc++.h>
using namespace std;

const int MAXN = 1e5 + 10;

int N;
int fail[MAXN];
int p[MAXN];
char s[MAXN];
bool vis[30];

int main()
{
	cin >> N ;
	fail[0] = -1;
	for(int i = 1; i <= N; i++)
		cin >> p[i], fail[i] = i - p[i];

	for(int i = 0; i < N; i++)
		if(fail[i+1] != 0)
			s[i] = s[fail[i+1]-1];
		else
		{
			memset(vis, 0x00, sizeof vis);
			int x = fail[i];
			while(x != -1)
				vis[s[x] - 'a'] = true, x = fail[x];

			int ch = 0;
			while(vis[ch])
				ch++;
			s[i] = 'a' + ch;
		}

	cout << s << endl ;
	return 0;
}
