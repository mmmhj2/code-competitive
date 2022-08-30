#include <iostream>
#include <string>
#include <cctype>
using namespace std;
string str;
int main()
{
    int cnt = 0;
    cin >> str;

    for(int i = 0; i < str.length(); i++)
    {
        if('0' <= str[i] && str[i] <= '9')
        {
            if((str[i]-'0') % 2 == 1)
            {
                cnt++;
            }

        }
        else
        {
            if(str[i] == 'a' || str[i] == 'e' || str[i] == 'i' || str[i] == 'o' || str[i] == 'u')
                cnt++;
        }
    }
    cout << cnt << endl;
}
