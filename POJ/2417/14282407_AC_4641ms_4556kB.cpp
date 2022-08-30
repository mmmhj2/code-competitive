#include <iostream>
#include <utility>
#include <vector>
#include <cmath>
#include <map>
using namespace std;
typedef long long i64;

i64 QUICK_POW(i64 base, i64 exp, i64 mod)
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

i64 log(i64 a, i64 b, i64 n)
{
    i64 tmp = 1;
    i64 sq = (int)round(sqrt(n));
    i64 pm = QUICK_POW(a, n - sq - 1, n);

    map <i64, i64> table ;
    table[1] = sq;

    for(int i = 1; i < sq; i++)
    {
        tmp = (tmp * a) % n ;
        if(!table[tmp])
            table[tmp] = i;
    }

    for(int i = 0; i < sq; i++)
    {
        if(table[b])
            return i * sq + (table[b] == sq ? 0 : table[b]);
        b = (b * pm) % n ;
    }
    return -1;
}


int main()
{
    int n, a, b ;
    while(cin >> n >> a >> b)
    {
        int ans = log(a, b, n);
        if(ans == -1)
            cout << "no solution" << endl ;
        else
            cout << ans << endl ;
    }
    return 0;
}
