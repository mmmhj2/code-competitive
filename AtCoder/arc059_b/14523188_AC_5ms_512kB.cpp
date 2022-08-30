#include <iostream>
#include <string>
using namespace std;

string str;

int main()
{
    cin >> str ;

    for (string::iterator itr = str.begin() + 1; itr != str.end(); itr++)
    {
        if (*itr == *(itr - 1))
        {
            cout << (int)(itr - str.begin()) << " " << (int)(itr - str.begin()) + 1 << endl ;
            return 0;
        }
    }

    if (str.size() > 2)
        for (string::iterator itr = str.begin() + 2; itr != str.end(); itr++)
        {
            if (*itr == *(itr - 2))
            {
                cout << (int)(itr - str.begin()) - 1 << " " << (int)(itr - str.begin()) + 1 << endl ;
                return 0;
            }
        }
    cout << "-1 -1" << endl ;
    return 0;

}
