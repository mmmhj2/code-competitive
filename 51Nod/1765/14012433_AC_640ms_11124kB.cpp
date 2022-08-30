#include <iostream>
#include <iomanip>
#include <vector>
using namespace std;

vector <int> vec;

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    int t;
    double n, m;
    cin >> n >> m ;
    for(int i = 1; i <= m; i++)
        cin >> t, vec.push_back(t);
    cout << fixed << setprecision(6) << n * (n-1) / (2 * m) << endl ;
    return 0;
}
