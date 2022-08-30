#include <cstring>
#include <string>
#include <iostream>
#include <stack>
using namespace std;
const int MAXN = 1100000;
typedef long long i64;
i64 sum[MAXN+10];
//stack <int> matching;

int main()
{
    i64 kase;
    cin >> kase;
    while(kase--)
    {
        i64 ans = 0, t = 0;
        string str; i64 len;
        cin >> str; len = str.length();

        /*while(!matching.empty())
            matching.pop();*/
        stack <i64> matching;

        for(i64 i = 0; i < len; i++)
        {
            if(str[i] == '(')
            {
                matching.push(i);
            }
            if(str[i] == ')')
            {
                if(matching.empty())
                    continue;
                t = matching.top();
                matching.pop();
                sum[i] = sum[t-1]+1;
            }
        }
        for(i64 i = 0; i < len; i++)
            ans += sum[i], sum[i] = 0;
        cout << ans << endl ;
    }
}
