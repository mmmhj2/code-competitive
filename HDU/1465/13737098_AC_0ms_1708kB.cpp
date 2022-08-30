#include <iostream>
using namespace std;

typedef long long i64;

i64 factorial[25];

void getFact(int n)
{
    factorial[0] = 1;
    for(int i = 1; i <= n; i++)
        factorial[i] = i * factorial[i-1];
}

int main()
{
    getFact(21);
    int n;
    while(cin >> n)
    {
        i64 ans = factorial[n];

        for(int i = 1; i <= n; i++)
            ans += (i & 1 ? -1LL : 1LL) * factorial[n] / factorial[i] ;

        cout << ans << endl ;
    }
    return 0;
}

