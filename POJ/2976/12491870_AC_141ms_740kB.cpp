#include <iostream>
#include <algorithm>
#include <cstring>
#include <iomanip>
using namespace std;
const double EPS = 1e-8;
const int MAXN = 1000;

struct Test
{
    int a, b;
    static double x ;
    static int cmp(const Test & lhs, const Test & rhs)
    {
        return (lhs.a - x * lhs.b) > (rhs.a - x * rhs.b) ;
    }
} test[MAXN+5];
double Test::x = 0;


int n, k;
//int a[MAXN+5], b[MAXN+5];
int tmp[MAXN+5];

bool check(double);
double BinarySearch();

int main()
{
    ios::sync_with_stdio(0);
    while(true)
    {
        memset(test, 0x00, sizeof(test));
        cin >> n >> k ;

        if(n == 0 && k == 0)
            break;

        for(int i = 1; i <= n; i++) cin >> test[i].a;
        for(int i = 1; i <= n; i++) cin >> test[i].b;

        cout << fixed << setprecision(0) << BinarySearch()*100 << endl ;
    }
    return 0;
}

bool check(double score)
{
    Test::x = score;
    sort(test+1, test+n+1, Test::cmp);

    double a = 0, b = 0;

    for(int i = 1; i <= n-k; i++)
        a+=test[i].a, b+=test[i].b;

    return a / b > score ;
}

double BinarySearch()
{
    double lb = 0, rb = 1;

    while(lb + EPS < rb)
    {
        double mid = (lb+rb) / 2;

        if(check(mid))
            lb = mid;
        else
            rb = mid;
    }

    return rb;
}
