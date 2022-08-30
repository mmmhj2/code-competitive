#include <iostream>
using namespace std;

const int MAXN = 100 * 2 + 5;
const int MAX_ENUM = 10000;


int N, op;
int X[MAXN];

void Solve()
{
	for(int a = 0; a <= MAX_ENUM; a++)
		for(int b = 0; b <= MAX_ENUM; b++)
		{
			bool feasible = true;
			for(int i = 2; i <= 2 * N; i += 2)
			{
				X[i] = (a * X[i-1] + b) % 10001;

				if(i + 1 > 2 * N)
					continue;
				if((a * X[i] + b) % 10001 != X[i+1])
				{
					feasible = false;
					break;
				}
			}

			if(feasible)
				return;
		}
}

int main() {
	ios::sync_with_stdio(false);

	cin >> N ;
	for(int i = 1; i <= N * 2 - 1; i += 2)
		cin >> X[i];
	Solve();
	for(int i = 2; i <= N * 2; i += 2)
		cout << X[i] << endl ;

	return 0;
}
