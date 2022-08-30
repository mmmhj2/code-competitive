#include <functional>
#include <algorithm>
#include <iostream>
#include <cstring>
#include <string>
using namespace std;
typedef long long i64;
typedef unsigned long long ui64;
constexpr size_t MAXN = 5.0e+6 + 20;
constexpr size_t BASE = 131;

string str;
i64 ans;
int ansArr[MAXN];
//hash <string> hashfunc;

int main()
{
    cin >> str ;
    int len = str.length();

    ansArr[0] = ans = 1;
    ui64 ha1(str[0]) ,ha2(str[0]) , power = 1;
    for(int i = 1; i < len; i++)
    {
        ha1 = ha1 * BASE + (str[i]);
        power *= BASE;
        ha2 = (str[i]) * power + ha2;

        cerr << ha1 << " " << ha2 << endl ;
        if(ha1 == ha2)
        {
            ansArr[i] = ansArr[(i-1) / 2] + 1;
            ans += ansArr[i];
        }
    }

    cout << ans << endl ;

    return 0;
}
