#include <iostream>
using namespace std;

int main()
{
    int x, y;
    cin >> x >> y ;
    if(x % y != 0)
        cout << x << endl ;
    else
        cout << -1 << endl ;
    return 0;
}
