#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
using namespace std;

int main()
{
    int kase, n, ans, t;
    cin >> kase ;
    while(kase--)
    {
        vector <int> vec;
        ans = 0;
        cin >> n ;

        vec.push_back(0);
        for(int i = 1; i <= n; i++)
        {
            cin >> t ;
            vec.push_back(t);
        }

        sort(vec.begin(), vec.end());
        for(int i = n; i > 0; i -= 2)
            ans ^= vec[i] - vec[i-1] - 1;

        if(ans)
            cout << "Georgia will win" << endl;
        else
            cout << "Bob will win" << endl ;
    }
}
