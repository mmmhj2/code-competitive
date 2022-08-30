#include <algorithm>
#include <iostream>
using namespace std;

int main()
{
    int n, m;
    while(cin >> n >> m)
    {
        int ans = 0;
        for(int i = 1; i <= n; i++)
        {
            int a, b;
            cin >> a >> b ;
            ans ^= (max(a, b) - min(a, b)) - 1;
        }

        if(ans)
            cout << "I WIN!" << endl ;
        else
            cout << "BAD LUCK!" << endl ;
    }
    return 0;
}
