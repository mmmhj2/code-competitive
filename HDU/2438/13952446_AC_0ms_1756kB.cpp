#include <iostream>
#include <iomanip>
#include <cmath>
using namespace std;

const double PI = acos(-1.0);
const double EPS = 1e-8;
double x, y, l, w;
double getY(double alpha)
{
    return (l * sin(alpha) + w / cos(alpha) - x) / tan(alpha);
}

int main()
{
    while(cin >> x >> y >> l >> w)
    {
        double L = 0, R = PI / 2.0;
        double mid1, mid2;
        while(R - L > EPS)
        {
            double delta = (R - L) / 3;
            mid1 = L + delta;
            mid2 = R - delta;
            if(getY(mid1) > getY(mid2))
                R = mid2;
            else
                L = mid1;
        }
        if(getY(L) < y)
            cout << "yes" << endl ;
        else
            cout << "no" << endl ;
    }
    return 0;
}
