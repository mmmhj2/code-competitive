#include <iostream>
#include <algorithm>
using namespace std;

int main()
{
    int n;
    while(cin >> n)
    {
        if(!n)  break;
        cout << ((n > 2) ? "Bob" : "Alice") << endl ;
    }
}
