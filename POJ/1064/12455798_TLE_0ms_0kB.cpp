#include <iostream>
#include <iomanip>
#include <cmath>
using namespace std;

const double EPS = 0.001;
const int MAXN = 10000;


double cable[MAXN+5];
int n, k;

bool Check(double expectedlength)
{
    int ans = 0;
    for(int i = 1; i <= n; i++)
    {
        ans += floor(cable[i]/expectedlength);
    }
    return ans >= k;
}

void BinarySearch();

int main()
{
    cin >> n >> k;
    for(int i = 1; i <= n; i++)
        cin >> cable[i];
    BinarySearch();
    return 0;
}

void BinarySearch()
{
    double lb = 0, rb = 0x7fffffff;

    while(rb-lb > EPS)
    {
        double mid = (lb+rb)/2;

        if(Check(mid)) lb = mid;
        else rb = mid;
    }

    cout << fixed << setprecision(2) << floor(rb*100) / 100.0 << endl;
}
