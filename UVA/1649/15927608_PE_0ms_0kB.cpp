#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

typedef long long i64;
typedef pair <i64, i64> pi64_2;

vector <pi64_2> answer;

ostream & operator << (ostream & _out, const pi64_2 & p)
{
	return _out << "(" << p.first << "," << p.second << ")";
}

int getBinaryResult(i64 n, i64 m, int k)
{
	i64 C = 1;
	for(int i = 1; i <= k; i++)
	{
		if(m * i / (n - i + 1) / C == 0)
			return 0;
		C = C * (n - i + 1) / i;
	}

	return (C == m ? 1 : 2);
}

int main()
{
	int T;
	scanf("%d", &T);

	while(T--)
	{
		answer.clear();

		i64 M;
		scanf("%lld", &M);

		answer.push_back(make_pair(M, 1LL));
		answer.push_back(make_pair(M, M - 1));

		for(int LF = 2; LF <= 30; LF++)
		{
			i64 L = LF, R = M;

			while(L <= R)
			{
				i64 mid = (L + R) >> 1;

				switch(getBinaryResult(mid, M, LF))
				{
				case 0:
					R = mid - 1;
					break;
				case 1:
					answer.push_back(make_pair(mid, LF));
					answer.push_back(make_pair(mid, mid - LF));
					goto END;
				case 2:
					L = mid + 1;
					break;
				}
			}

			END:
			;
		}

		sort(answer.begin(), answer.end());
		answer.erase(unique(answer.begin(), answer.end()), answer.end());

		cout << answer.size() << endl ;

		for(vector<pi64_2>::iterator itr = answer.begin(); itr != answer.end(); ++itr)
		{
			cout << *itr ;
			if(itr != answer.end())
				cout << " " ;
		}
		cout << endl ;
	}

	return 0;
}
