#include <algorithm>
#include <iostream>
#include <iomanip>
#include <vector>
#include <cmath>
using namespace std;

#define DEBUGTRIGGER (cerr << "Triggered at [" << __PRETTY_FUNCTION__ << "]:(" << __LINE__ << ")" << endl)

typedef long long i64;
typedef unsigned long long u64;

const int MAXN = 100000 + 10;

struct Element
{
	i64 gcd;
	int pos;

	static i64 GCD(i64 x, i64 y)
	{
		if(!y)
			return x;
		return GCD(y, x % y);
	}

	void replaceGCD(i64 x)
	{
		this->gcd = GCD(this->gcd, x);
	}

	static bool compare(const Element & lhs, const Element & rhs)
	{
		if(lhs.gcd < rhs.gcd)
			return true;
		if(lhs.gcd > rhs.gcd)
			return false;

		if(lhs.pos < rhs.pos)
			return true;
		return false;
	}
};

int N;
i64 A[MAXN];


int main()
{
	ios::sync_with_stdio(false);
	cin.tie(NULL);

	int K;
	cin >> K ;
	while(K--)
	{
		vector <Element> table;
		i64 ans = 0;
		cin >> N ;
		for(int i = 1; i <= N; i++)
			cin >> A[i];

		for(int i = 1; i <= N; i++)
		{
			vector <Element> nTable;

			table.push_back(Element{0, i});
			for(vector<Element>::iterator itr = table.begin(); itr != table.end(); ++itr)
				itr->replaceGCD(A[i]);
			sort(table.begin(), table.end(), Element::compare);

			for(vector<Element>::iterator itr = table.begin(); itr != table.end(); ++itr)
			{
				if(itr != table.begin() && itr->gcd == (itr-1)->gcd)
					continue;

				nTable.push_back(*itr);
				ans = max(ans, itr->gcd * (i - itr->pos + 1));
			}

			table = nTable;
		}

		cout << ans << endl ;
	}

	return 0;
}
