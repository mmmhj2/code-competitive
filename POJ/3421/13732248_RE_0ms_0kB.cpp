#include <iostream>
#include <iterator>
#include <vector>
#include <cmath>
using namespace std;

typedef long long int i64;
typedef unsigned long long int ui64;

struct Factor
{
	int base;
	int exp;
	Factor()
	{
		base = exp = 0;
	};
	Factor(int b)
	{
	    Factor();
	    base = b;
	}
};

ui64 fact[25];

void getUniqueFactor(int x, vector<Factor> & UniFac)
{
    UniFac.clear();
    for(int i = 2; i*i <= x; i++)
    {
        if(x % i)
            continue;
        UniFac.push_back(Factor(i));

        while(x % i == 0)
            UniFac.rbegin()->exp++, x /= i;
    }
    if(x != 1)
        UniFac.push_back(Factor(x)), UniFac.rbegin()->exp = 1;
}

void getFact(ui64 x)
{
    fact[0] = fact[1] = 1;
    for(int i = 1; i <= x; i++)
        fact[i] = fact[i-1] * i;
}

int main()
{
    getFact(22);
	vector <Factor> Fact;
	int x ;
	while(cin >> x)
	{
		//cout << getUniqueFactor(x, Fact) << endl ;
		getUniqueFactor(x, Fact);

		ui64 res = 0;
		for(vector<Factor>::iterator itr = Fact.begin(); itr != Fact.end(); itr++)
            res += itr->exp ;
        cout << res << " " ;

        ui64 ans = fact[res];
        for(vector<Factor>::iterator itr = Fact.begin(); itr != Fact.end(); itr++)
            ans /= fact[itr->exp];

        cout << ans << endl ;
	}
}
