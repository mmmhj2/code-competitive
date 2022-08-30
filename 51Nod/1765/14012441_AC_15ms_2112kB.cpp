#include <iostream>
#include <iomanip>
using namespace std;
int main()
{
    double n, m;
    cin >> n >> m ;
    cout << fixed << setprecision(6) << n * (n-1) / (2 * m) << endl ;
    return 0;
}
