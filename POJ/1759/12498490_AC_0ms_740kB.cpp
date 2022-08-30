#include <cstring>
#include <cstdio>
#include <iostream>
#include <iomanip>
#include <algorithm>
using namespace std;
const int MAXN = 100000;
const double EPS = 1e-8;

int a;  double h1;
double ans ;
bool flag = true;

double BinarySearch();
double check(double median);

int main()
{
    cin >> a >> h1 ;
    BinarySearch();
    //cout <<  << endl ;
    cout << fixed << setprecision(2) << ans << endl ;
}

double BinarySearch()
{
    double lb = 0, rb = h1+50;
    while(lb + EPS < rb)
    {
        double mid = (lb+rb) / 2;
        if(check(mid) >= 0)
            rb = mid;
        else
            lb = mid;
    }
    check(rb);
    return rb;
}

double check(double median)
{
    double minheight = 0x7fffffff;
    double th1 = h1, th2 = median, th3;
    for(int i = 2; i < a; i++)
    {
        th3 = 2.0 * th2 - th1 + 2.0;
        minheight = min(minheight, th3);
        th1 = th2;
        th2 = th3;
    }
    ans = th2;
    return minheight;
}


