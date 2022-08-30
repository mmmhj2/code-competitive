#include <iostream>
#include <iomanip>
#include <cmath>
using namespace std;
typedef long long i64;
i64 ExtGcd(i64, i64, i64&, i64&);
i64 Gcd(i64 a, i64 b)
{
    if(b == 0)
        return a;
    return Gcd(b, a%b);
}

int main()
{
    i64 s1, s2, v1, v2, b;
    i64 x, y;
    cin >> s1 >> s2 >> v1 >> v2 >> b;
    i64 a = v1-v2, c = s2-s1;

    if(a < 0)
        a += b;

    i64 GCD = Gcd(a, b);
    if(c % GCD)
    {
        cout << -1 << endl ;
        return 0;
    }

    a /= GCD, b /= GCD, c /= GCD;
    ExtGcd(a, b, x, y);

    x *= c, x %= b;
    while(x < 0)
        x += b;

    cout << x << endl;
}

i64 ExtGcd(i64 a, i64 b, i64 &x, i64 &y)
{
    if(b == 0)
    {
        x = 1, y = 0;
        return a;
    }
    i64 ret = ExtGcd(b, a%b, y, x);
    y -= a/b*x;
    return ret;
}
