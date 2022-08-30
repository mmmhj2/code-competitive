#include <bits/stdc++.h>
using namespace std;

int N;
int maxDep;
int solution[100];

bool IDDFS(int dep, int cur)
{
	if (dep > maxDep || cur <= 0 || (cur << (maxDep - dep)) < N)
		return false;
	if (cur == N || (cur << (maxDep - dep)) == N)
		return true;

	//sol.push_back(cur);
	solution[dep] = cur;

	for (int i = 0; i <= dep; i++)
		if (IDDFS(dep + 1, cur + solution[i]))
			return true;
		else if (IDDFS(dep + 1, cur - solution[i]))
			return true;

	return false;
}

int main()
{
	ios::sync_with_stdio(false);
	while (cin >> N)
	{
		maxDep = 0;
		while (!IDDFS(0, 1))
			maxDep++;

		cout << maxDep << endl;
	}

}
