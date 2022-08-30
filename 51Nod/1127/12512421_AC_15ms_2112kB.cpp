#include <iostream>
#include <string>
#include <set>
using namespace std;

string str;
int vist[50];

int main()
{
    int ans = 0x7fffffff;
    cin >> str ;
    int len = str.length();

    int s = 0, e = 0, num = 0;

    for(e = 0; e < len; e ++)
    {
        if(vist[str[e]-'A'] == 0)
            num ++;
        vist[str[e]-'A']++;
        while(vist[str[s]-'A'] > 1)
            vist[str[s++]-'A']--;
        if(num == 26)
            ans = min(ans, e-s+1);
    }
    if(ans > len)
        cout << "No Solution" << endl;
    else
        cout << ans << endl;
}
