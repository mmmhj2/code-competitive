#include <algorithm>
#include <iostream>
#include <iomanip>
#include <complex>
#include <cfloat>
using namespace std;

typedef int64_t i64;
typedef uint64_t u64;
typedef complex <double> pt;

constexpr double EPS = 1e-9;
int W;
pt PT[6];

bool cmp(const pt & p1,const pt & p2)
{
    return make_pair(p1.real(), p1.imag()) < make_pair(p2.real(), p2.imag());
}

double FeasibilityTest(pt p1, pt p2)
{
    // norm(x + iy) = x*x + y*y, which is the square of the length of a vector (x, y)
    if(norm(p1) < W * W)        // Edge p1 is shorter than the given width
    {
        p2 /= p1 / abs(p1);
        if(p2.imag() > -EPS && p2.real() > -EPS && p2.real() < W + EPS) // Edge p2 doesn't stretch outside
            return p2.imag();
        return DBL_MAX;
    }
    else
    {
        // Rotate the triangle to fit in
        double h = sqrt(norm(p1) - W * W);
        double a1 = atan(h / W);
        double a2 = arg(p1);

        // Rotate the given edge
        p1 = polar(abs(p1), a1);
        p2 *= polar(1.0, a1 - a2);

        if(p2.imag() > -EPS && p2.real() > -EPS && p2.real() < W + EPS)
            return max(p1.imag(), p2.imag());
        return DBL_MAX;
    }
}

void CalcAns(double & ans)
{
    ans = DBL_MAX;
    do
    {
        //cerr << PT[1] << " " << PT[2] << " " << PT[3] << " " << ans << endl ;
        ans = min(ans, FeasibilityTest(PT[2] - PT[1], PT[3] - PT[1]));
    }
    while(next_permutation(PT+1, PT+4, cmp));
}

int main()
{
    ios::sync_with_stdio(false), cin.tie(nullptr);

    int T;
    cin >> T ;
    while(T--)
    {
        double ans1, ans2;
        int x1, y1, x2, y2, x3, y3;

        cin >> x1 >> y1 >> x2 >> y2 >> x3 >> y3 >> W;
        //cerr << x1 << y1 << x2 << y2 << x3 << y3 << endl ;
        PT[1] = pt(x1, y1), PT[2] = pt(x2, y2), PT[3] = pt(x3, y3);
        //cerr << PT[1] << PT[2] << PT[3] << endl ;

        sort(PT+1, PT+4, cmp);
        CalcAns(ans1);

        // Flip the triangle and try again
        for(int i = 1; i <= 3; i++)
            PT[i] = conj(PT[i]);
        sort(PT+1, PT+4, cmp);
        CalcAns(ans2);

        ans1 = min(ans1, ans2);
        if(ans1 >= DBL_MAX)
            cout << "impossible" << endl ;
        else
            cout << fixed << setprecision(7) << ans1 << endl ;
    }
    return 0;
}
