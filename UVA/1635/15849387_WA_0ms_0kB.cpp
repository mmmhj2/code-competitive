#include <algorithm>
#include <iostream>
#include <cstring>
#include <vector>
#include <cmath>
using namespace std;

const int MAXN = 100000 + 10;

vector <int> factor, answer;
bool avail[MAXN];

void defactorize(int x, vector <int> & output)
{
	int lim = sqrt(x) + 1;

	for(int i = 2; i <= lim; i++)
		if(x % i == 0)
		{
			output.push_back(i);
			while(x % i == 0)
				x /= i;
		}
	if(x > 1)
		output.push_back(x);
}

int main()
{
	int N, M;
	while(cin >> N >> M)
	{
		memset(avail, 0x01, sizeof avail);

		N--;
		factor.clear();
		answer.clear();
		defactorize(M, factor);

		for(vector<int>::iterator itr = factor.begin(); itr != factor.end(); ++itr)
		{
			int lb = 0;

			int x = M;
			while(x % (*itr) == 0)
				x /= (*itr), lb++;

			for(int k = 1; k < N; k++)
			{
				int res = 0;
				x = N - k + 1;
				while(x % (*itr) == 0)
					x /= (*itr), res++;
				x = k;
				while(x % (*itr) == 0)
					x /= (*itr), res--;

				if(res < lb)
					avail[k] = false;
			}
		}

		for(int i = 1; i < N; i++)
			if(avail[i])
				answer.push_back(i + 1);

		cout << answer.size() << endl ;
		for(vector<int>::iterator itr = answer.begin(); itr != answer.end(); ++itr)
			cout << *itr << " \n"[itr != answer.begin()] ;
	}
}

