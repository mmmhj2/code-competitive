#include <iostream>

using namespace std;

int main()
{
    int m = 0, n = 0;
    while(cin >> n >> m)
    {
        if(n == 0 && m == 0)
            break;
        if((!(n & 1)) || (!(m & 1)))
            cout << "Wonderful!" << endl ;
        else
            cout << "What a pity!" << endl ;
    }
    return 0;
}