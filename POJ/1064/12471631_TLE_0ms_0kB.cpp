#include <iostream>
#include <iomanip>
#include <cmath>
#include <cstdio>
using namespace std;

const double EPS = 0.00001;
const int MAXN = 10000;


double cable[MAXN+5];
int n, k;

bool Check(double length)
{
    int ans = 0;
    for(int i = 1; i <= n; i++)
    {
        ans += (int)(cable[i]/length);
    }
    return ans >= k;
}

void BinarySearch();

int main()
{
    ios::sync_with_stdio(false);

    cin >> n >> k;
    for(int i = 1; i <= n; i++)
        cin >> cable[i];

    BinarySearch();
    return 0;
}

void BinarySearch()
{
    double lb = 0, rb = 100010;
    while(rb-lb > EPS)
    {
        double mid = (lb+rb)/2;

        if(Check(mid)) lb = mid;
        else rb = mid;
    }
    cout << fixed << setprecision(2) ;
    cout << floor(rb*100) / 100 << endl ;
}
