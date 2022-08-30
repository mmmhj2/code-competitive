#include <iostream>
#include <string>
#include <stack>
using namespace std;

int ans;
char tp;
stack <char> stk;
string str;

inline int abs(int x)
{
    if(x > 0)
        return x;
    return -x;
}

int main()
{
    cin >> str ;

    for(string::iterator itr = str.begin(); itr != str.end() && ans >= 0; itr++)
    {
        switch(*itr)
        {
        case '<':
        case '{':
        case '[':
        case '(':
            stk.push(*itr);
            break;
        case '>':
        case '}':
        case ']':
        case ')':
            if(stk.empty())
            {
                ans = -1;
                break;
            }

            tp = stk.top();
            stk.pop();

            if(*itr == ')' && tp != '(')
                ans++;
            else if(*itr != ')' && tp != (*itr)-2)
                ans++;

            break;
        }
    }

    if(ans < 0)
        cout << "Impossible" << endl ;
    else
        cout << ans << endl ;

    return 0;
}
