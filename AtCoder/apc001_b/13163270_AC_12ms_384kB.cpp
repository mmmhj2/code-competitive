#include <iostream>
#include <cmath>
using namespace std;
const int MAXN = 10005;
int a[MAXN], b[MAXN];

int main()
{
    int n;
    long long int diff1 = 0, diff2 = 0;

    cin >> n;

    for(int i = 1; i <= n; i++)
        cin >> a[i] ;
    for(int i = 1; i <= n; i++)
        cin >> b[i] ;

    for(int i = 1; i <= n; i++)
    {
        if(a[i] >= b[i])
        {
            diff1 += a[i] - b[i] ;
        }
        else
        {
            //int t = b[i] - a[i];
            //if(t & 1)
            //    t -= 1;
            diff2 += (b[i] - a[i]) / 2 * 2;
        }
    }

    if(diff2 / 2 >= diff1)
        cout << "Yes" << endl ;
    else
        cout << "No" << endl ;

    return 0;
}
