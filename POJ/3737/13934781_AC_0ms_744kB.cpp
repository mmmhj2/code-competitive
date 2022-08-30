#include <iostream>
#include <iomanip>
#include <cmath>
using namespace std;

const double PI = acos(-1.0);
const double EPS = 1e-8;

int main()
{
    double s;
    while(cin >> s)
    {
        double v = 0.0, L = 0.0, R = sqrt(s / PI);
        double mid1, mid2;
        while(R - L > EPS)
        {
            mid1 = L + (R - L) / 3;
            mid2 = R - (R - L) / 3;
            double v1 = PI * mid1 * mid1 * sqrt ( pow((s-PI*mid1*mid1)/(PI*mid1),2) - mid1*mid1 ) / 3;
            double v2 = PI * mid2 * mid2 * sqrt ( pow((s-PI*mid2*mid2)/(PI*mid2),2) - mid2*mid2 ) / 3;
            if(v1 > v2)
                v = v1, R = mid2;
            else
                v = v2, L = mid1;
        }

        double r = R;
        double h = sqrt ( pow((s-PI*r*r)/(PI*r),2) - r*r );
        cout << fixed << setprecision(2) << v << endl ;
        cout << fixed << setprecision(2) << h << endl ;
        cout << fixed << setprecision(2) << r << endl ;

    }
    return 0;
}
