#include <iostream>
#include <cmath>
using namespace std;

#define OUTPUT(a) a << " "

typedef long long int i64;

i64 GCD(i64 a, i64 b)
{
    if(b == 0)
        return a;
    return GCD(b, a % b);
}

i64 cntFact(i64 a)
{
    i64 ans = 0;
    for(int i = 1; i * i <= a; i++)
        if(a % i == 0)
        {
            ans++;
            if(i * i != a)
                ans++;
        }

    return ans;
}

int main()
{
    i64 a, b, c;
    cin >> a >> b;
    c = GCD(a, b);
    cerr << c << endl ;
    a = cntFact(a);
    b = cntFact(b);
    c = cntFact(c);
    cerr << OUTPUT(a) << OUTPUT(b) << c << endl ;
    a = a * b;
    i64 dem = GCD(a, c);
    a /= dem, c /= dem;
    cout << a << " " << c << endl ;
}
