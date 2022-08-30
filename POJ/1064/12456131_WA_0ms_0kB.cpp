#include <iostream>
#include <iomanip>
#include <cmath>
#include <cstdio>
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
    scanf("%d%d", &n, &k);
    for(int i = 1; i <= n; i++)
        scanf("%lf", &cable[i]);
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

    printf("%.2lf\n", floor(lb*100) / 100.0);
}
