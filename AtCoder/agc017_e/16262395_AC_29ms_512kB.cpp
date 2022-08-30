#include <bits/stdc++.h>
using namespace std;
typedef long long i64;

const int MAXN = (200 + 10) * 2;

class no_solution : public std::exception
{
public:
	const char * what(void) const noexcept
	{
		return "no solution reachable";
	}
};

namespace disjointSet
{
int fa[MAXN];

void init()
{
	memset(fa, 0x00, sizeof fa);
}

int find(int x)
{
	if(fa[x])
		return fa[x] = find(fa[x]);
	return x;
}

void merge(int x, int y)
{
	x = find(x), y = find(y);
	if(x != y)
		fa[x] = y;
}

}

bool loop[MAXN];
int inDeg[MAXN], outDeg[MAXN];
int N, H;

void solve()
{
	for(int i = 0; i <= 2 * H; i++)
	{
		if(i > H)
			if(inDeg[i] > outDeg[i])
				throw no_solution();
		if(i < H)
			if(outDeg[i] > inDeg[i])
				throw no_solution();

		bool found = false, isLoop = loop[i];

		for(int j = 0; j <= 2 * H; j++)
			if(found)
				break;
			else
				if(disjointSet::find(i) == disjointSet::find(j))
				{
					if(i != j)
						isLoop = true;
					if(inDeg[j] != outDeg[j])
						found = true;
				}

		if(!found && isLoop)
			throw no_solution();
	}
}

int main()
{
	ios::sync_with_stdio(false), cin.tie(nullptr);

	cin >> N >> H ;
	for(int i = 1; i <= N; i++)
	{
		int a, b, c, d, L, R;
		cin >> a >> b >> c >> d;
		L = c ? H - c : H + a;
		R = d ? H + d : H - b;
		disjointSet::merge(L, R);
		inDeg[R]++, outDeg[L]++;

		if(L == R)
			loop[L] = true;
	}


	try
	{
		solve();
		cout << "YES" << endl;
	}
	catch(std::exception & x)
	{
		cout << "NO" << endl ;
	}

	return 0;
}

