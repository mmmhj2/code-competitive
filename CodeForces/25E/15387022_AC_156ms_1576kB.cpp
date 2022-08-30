#include <functional>
#include <algorithm>
#include <iostream>
#include <cstring>
#include <string>
#include <cstdio>
using namespace std;
typedef long long i64;
typedef unsigned long long ui64;
typedef ui64 hashVal;
constexpr size_t MAXN = 1e5 + 20;
constexpr size_t BASE = 137;

constexpr int permut[][3] = {{0, 1, 2}, {0, 2, 1}, {1, 0, 2}, {2, 0, 1}, {1, 2, 0}, {2, 1, 0}};
string str[3];

// Max length of common substring after concatenation (s1 + s2)
int getMaxLength(const string & s1, const string & s2)
{
    int ret = 0;
    int l1 = s1.length();
    int len = min(s2.length(), (decltype(s2.length()) (l1)));

    hashVal h1(0), h2(0);
    ui64 power = 1;

    for(int i = 0; i < len; i++)
    {
        h2 = h2 * BASE + s2[i];
        h1 = h1 + s1[l1 - i - 1] * power;
        power *= BASE;

        if(h1 == h2)
            ret = i + 1;
    }
    return ret;
}

// if s2 is a substring of s1
bool isSubstring(const string & s1, const string & s2)
{
    int l1 = s1.length(), l2 = s2.length();
    hashVal h1(0), h2(0);
    ui64 power = 1;
    for(int i = 0; i < l2; i++)
        power *= BASE;

    if(l2 > l1)
        return false;

    for(int i = 0; i < l2; i++)
        h1 = h1 * BASE + s2[i], h2 = h2 * BASE + s1[i];

    if(h1 == h2)
        return true;

    for(int i = 0; i + l2 < l1; i++)
    {
        h2 = h2 * BASE + s1[i + l2] - s1[i] * power;
        if(h1 == h2)
            return true;
    }
    return false;
}

int main()
{
    cin >> str[0] >> str[1] >> str[2];

    int ans = 0x7FFFFFFF;
    for(int i = 0; i < 6; i++)
    {
        string Tstr = str[permut[i][0]];
        int Tlen = Tstr.length();

        for(int j = 1; j <= 2; j++)
        {
            if(isSubstring(Tstr, str[permut[i][j]]))
                continue;

            int comLen = getMaxLength(Tstr, str[permut[i][j]]);
            Tstr += str[permut[i][j]].substr(comLen, str[permut[i][j]].length());
            Tlen = Tstr.length();
        }
        ans = min(ans, Tlen);
    }
    cout << ans << endl ;
    return 0;
}
