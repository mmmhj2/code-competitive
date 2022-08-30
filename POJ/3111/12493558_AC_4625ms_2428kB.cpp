#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

const double EPS = 1e-5;
const int MAXN = 100000;

struct _jewel
{
    int v, w;
    static double x;
    int uid;

    static int cmp(const _jewel & lhs,const _jewel & rhs)
    {
        return (lhs.v - x*lhs.w) > (rhs.v - x*rhs.w);
    }
}jewel[MAXN+5];
double _jewel::x(0.0);
int n, k;
vector <int> ans ;

double BinarySearch();
bool check(double x);

int main()
{
    ios::sync_with_stdio(0);

    cin >> n >> k;

    for(int i = 1; i <= n; i++)
    {
        cin >> jewel[i].v >> jewel[i].w;
        jewel[i].uid = i;
    }

    BinarySearch();
    //cerr << BinarySearch() << endl ;

    for(int i = 0; i < ans.size(); i++)
    {
        if(i != 0)
            cout << " " ;
        cout << ans[i] ;
    }

}

bool check(double x)
{
    _jewel::x = x;
    sort(&jewel[1], &jewel[n+1], _jewel::cmp);

    double sumv = 0, sumw = 0;

    for(int i = 1; i <= k; i++)
        sumv += jewel[i].v, sumw += jewel[i].w;

    return sumv/sumw > x;
}

double BinarySearch()
{
    double lb = 0, rb = 1e8;

    while(lb + EPS < rb)
    {
        double mid = (lb+rb) / 2;

        if(check(mid))
        {
            lb = mid;
        }
        else
        {
            rb = mid;
        }
    }

    check(rb);

    for(int i = 1; i <= k; i++)
        ans.push_back(jewel[i].uid);

    return rb;
}
