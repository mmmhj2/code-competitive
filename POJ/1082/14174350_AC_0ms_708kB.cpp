#include <iostream>
using namespace std;

int main()
{
    int kase;
    cin >> kase ;
    while(kase--)
    {
        int y, m, d;
        cin >> y >> m >> d ;

        if(!((m + d) & 1))
            cout << "YES" << endl ;
        else if (d == 30)
        {
            if(m == 9 || m == 11)
                cout << "YES" << endl ;
        }
        else
            cout << "NO" << endl ;
    }
    return 0;
}
