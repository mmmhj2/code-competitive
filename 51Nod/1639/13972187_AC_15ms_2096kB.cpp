#include <iostream>
#include <iomanip>
using namespace std;

int main()
{
    int n;
    double ans = 1 ;
    cin >> n ;
    for(int i = 1; i < n; i++)
        ans *= 1.0 * (i*2) / (i*2+1);
    cout << fixed << setprecision(6) << ans << endl ;
}
