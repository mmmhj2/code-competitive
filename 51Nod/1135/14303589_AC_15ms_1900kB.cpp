#include <algorithm>
#include <iostream>
#include <iterator>
#include <vector>
#include <cmath>
using namespace std;

typedef vector<int> vint;
typedef long long i64;

void GetDecomp(int x, vint & ans)
{
    int sq = sqrt(x) + 0.5;

    for(int i = 2; i <= sq; i++)
    {
        if(x % i == 0)
        {
            ans.push_back(i);
            while(!(x % i))
                x /= i;
        }

        if(x == 1)
            break;
    }
    if(x > 1)
        ans.push_back(x);
}

i64 QuickPow(i64 base, i64 exp, i64 mod)
{
    i64 ans = 1;

    while(exp)
    {
        if(exp & 1)
            ans = (ans * base) % mod;
        base = (base * base) % mod;
        exp >>= 1;
    }

    return ans ;
}

int main()
{
    int p;
    vint decomp;
    /*
    while(cin >> n)
    {
        vint ans ;
        GetDecomp(n, ans);
        copy(ans.begin(), ans.end(), ostream_iterator<int> (cerr, " "));
        cerr << endl ;
    }

    int m, k;
    while(cin >> n >> m >> k)
    {
        cout << QuickPow(n, m, k) << endl ;
    }
    */

    cin >> p ;
    GetDecomp(p-1, decomp);

    //  a ^ ((p-1) / pi) % p != 1
    i64 a;  bool is_primRoot;
    for(a = 2; a <= p; a++)
    {
        is_primRoot = true ;

        for(vint::iterator itr = decomp.begin(); itr != decomp.end(); itr++)
            if(QuickPow(a, (p-1) / *itr, p) == 1LL)
            {
                is_primRoot = false;
                break;
            }

        if(is_primRoot)
            break;
    }
    cout << a << endl ;
    return 0;
}
