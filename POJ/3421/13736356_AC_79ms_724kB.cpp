#include <iostream>
#include <iterator>
#include <vector>
#include <cmath>
using namespace std;

typedef unsigned long long int ui64;

const int MAXN = 20;

ui64 factorial[MAXN+5];

void getFact(int n)
{
    factorial[0] = 1;
    for(int i = 1; i <= n; i++)
        factorial[i] = factorial[i-1] * i;
}

void solve(int x)
{
    ui64 expsum = 0, div = 1;
    for(ui64 i = 2; i * i <= x; i++)
    {
        if(x % i)
            continue;
        int tcnt = 0;
        while(!(x % i))
            tcnt++, x /= i ;
        expsum += tcnt ;
        div *= factorial[tcnt];
    }
    if(x != 1)
        expsum++;
    cout << expsum << " " << factorial[expsum] / div << endl ;
}

int main()
{
    getFact(22);
    int x ;
	while(cin >> x)
	{
        solve(x);
	}
    return 0;
}