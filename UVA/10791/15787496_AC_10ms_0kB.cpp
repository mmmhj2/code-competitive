#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

typedef long long i64;
typedef unsigned long long u64;

pair<i64, int> defactorize(i64 x);

int N;
int main()
{
	int CaseCnt = 0;
	while(cin >> N)
	{
		if(!N)
			break;

		cout << "Case " << ++CaseCnt << ": " ;

		pair <i64, int> result = defactorize(N);

		// Only one integer can be found
		if(result.second <= 1)
			result.first += 1;

		cout << result.first << endl ;
	}
}

pair<i64, int> defactorize(i64 x)
{
	i64 sum = 0;
	int cnt = 0;
	int lim = sqrt(x) + 1;

	for(int i = 2; i <= lim; i++)
		if(x % i == 0)
		{
			i64 tmp = 1;

			cnt++;
			while(x % i == 0)
				x /= i, tmp *= i;

			sum += tmp;
		}

	if(x != 1 || cnt == 0)
		cnt += 1, sum += x;

	return make_pair(sum, cnt);
}
