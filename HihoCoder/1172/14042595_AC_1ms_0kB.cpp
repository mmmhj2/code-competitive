#include <algorithm>
#include <iostream>
#include <string>
using namespace std;

int main()
{
    string str;
    int ans;
    cin >> ans >> str;
    ans = 0;
    for(int i = 0; i < str.length(); i++)
        if(str[i] == 'H')
            ans ^= i+1;
    if(ans)
        cout << "Alice" << endl ;
    else
        cout << "Bob" << endl ;
}
