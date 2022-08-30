#include <iostream>

using namespace std;

int getSG(int n)
{
    if(n == 0)
        return 0;
    switch(n % 4)
    {
    case 1:
    case 2:
        return n;
    case 3:
        return n+1;
    case 0:
        return n-1;
    }
}

int main()
{
    int n, ans = 0;
    cin >> n ;
    for(int i = 1; i <= n; i++)
    {
        int t;
        cin >> t;
        ans ^= getSG(t);
    }
    if(ans)
        cout << "Alice" << endl ;
    else
        cout << "Bob" << endl ;
}

