#include <iostream>

using namespace std;

int main()
{
    int t;
    while(cin >> t)
    {
        while(t % 2 == 0)
            t /= 2;
        if(t == 1)
            cout << "YES" << endl;
        else
            cout << "NO" << endl;
    }
    return 0;
}
