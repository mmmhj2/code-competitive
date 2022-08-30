#include <iostream>
#include <iomanip>
#include <cmath>
using namespace std;

const double PI = acos(-1.0);
const double EPS = 1e-15;
const double INF = 65536;

const int MAXN = 30;

struct POINT
{
    double x, y;
}p[MAXN+5];

double getLength(double alpha, int n)
{
    double maxX = -INF, maxY = -INF;
    double minX = INF,  minY = INF;
    for(int i = 1; i <= n; i++)
    {
        // x = x*cos(α) - y*sin(α) ; y = x*sin(α) + y*cos(α)
        //double x = p[i].x, y = p[i].y;
        double x = p[i].x * cos(alpha) - p[i].y * sin(alpha);
        double y = p[i].x * sin(alpha) + p[i].y * cos(alpha);
        maxX = max(maxX, x);
        minX = min(minX, x);
        maxY = max(maxY, y);
        minY = min(minY, y);
    }

    return max(maxX - minX, maxY - minY);
}

int main()
{
    int kase;
    cin >> kase ;
    while(kase--)
    {
        int n;
        cin >> n ;
        for(int i = 1; i <= n; i++)
            cin >> p[i].x >> p[i].y ;

        double L = 0, R = PI / 2.0;
        double mid1, mid2;
        while(R - L > EPS)
        {
            double triple = (R - L) / 3.0;
            mid1 = L + triple;
            mid2 = R - triple;

            if(getLength(mid1, n) > getLength(mid2, n))
                L = mid1;
            else
                R = mid2;
        }
        L = getLength(L, n);
        cout << fixed << setprecision(2) << L * L << endl ;
    }
    return 0;
}
