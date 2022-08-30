#include <iostream>
#include <cmath>
using namespace std;

int quickpow(int base, int exp)
{
    int ans = 1;
    while(exp >= 1)
    {
        if(exp & 1)
        {
            ans = ((ans % 10) * (base % 10)) % 10;
        }
        base = ((base % 10) * (base % 10)) % 10;
        exp >>= 1;
    }
    return ans;
}

int main()
{
    int n;
    cin >> n ;
    cout << quickpow(n, n) << endl ;
}
