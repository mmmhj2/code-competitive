#include <algorithm>
#include <iostream>
#include <iomanip>
#include <cstring>
#include <vector>
#include <cmath>
#include <queue>

#define printfDbg(...) fprintf(stderr, __VA_ARGS__), fflush(stderr)

using namespace std;

const int MAXN = 10000;

int N, M;

int fa[MAXN];
char ans[MAXN];
bool vist[MAXN];
bool forbidden[10];

bool BFS()
{
	queue <int> Q ;
	Q.push(0);

	while(!Q.empty())
	{
		int cur = Q.front();
		//printfDbg("Now searching : %d\n", cur);
		Q.pop();

		for(int i = 0; i <= 9; i++)
		{
			if(forbidden[i] || ((!cur) && (!i)))
				continue;

			int nxt = (cur * 10 + i) % N;
			if(vist[nxt])
				continue;
			//printfDbg("%d %d %d\n", cur, i, nxt);
			ans[nxt] = '0' + i;
			vist[nxt] = true;
			fa[nxt] = cur;

			if(nxt == 0)
				return true;
			Q.push(nxt);
		}
	}
	return false;
}

string generateAns()
{
	string ans;

	int pos = 0;
	while(pos != 0 || ans.empty())
	{
		//printfDbg("Processing : %d, %d\n", pos, (int)ans[pos]);
		ans.push_back(::ans[pos]);
		pos = fa[pos];
	}

	reverse(ans.begin(), ans.end());
	//cerr << "Answer : " << ans << endl ;
	return ans;
}

int main()
{
	int kase = 0, t;

	while(scanf("%d%d", &N, &M) != EOF)
	{
		memset(vist, 0x00, sizeof vist);
		memset(forbidden, 0x00, sizeof forbidden);

		for(int i = 1; i <= M; i++)
			scanf("%d", &t), forbidden[t] = true;

		string ans;
		if(BFS())
			ans = generateAns();
		else
			ans = "-1";

		printf("Case %d: %s\n", ++kase, ans.c_str());
		fflush(stdout);
	}

}

