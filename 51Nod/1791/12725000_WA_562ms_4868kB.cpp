#include <cstring>
#include <string>
#include <iostream>
#include <stack>
using namespace std;
const int MAXN = 1100000;

int sum[MAXN+10];
//stack <int> matching;

int main()
{
    int kase;
    cin >> kase;
    while(kase--)
    {
        int ans = 0;
        int t;
        string str; int len;
        cin >> str; len = str.length();

        /*while(!matching.empty())
            matching.pop();*/
        stack <int> matching;

        for(int i = 0; i < len; i++)
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
        for(int i = 0; i < len; i++)
            ans += sum[i], sum[i] = 0;
        cout << ans << endl ;
    }
}
