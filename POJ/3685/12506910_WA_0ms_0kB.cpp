#include <iostream>
using namespace std;
typedef long long i64;
const i64 MAXN = 50000;
const i64 COEFF = 100000;

int kase, n, m;

i64 f(int i, int j)
{
    return i*i + COEFF*i + j*j - COEFF*j + i*j;
}
i64 BinarySearch_Outer();
i64 BinarySearch_Inner(i64);

int main()
{
    cin >> kase;

    while(kase--)
    {
        cin >> n >> m;

        cout << BinarySearch_Outer() << endl;
    }
}

i64 BinarySearch_Outer()
{
    i64 lb = -COEFF * n ;
    i64 rb = 3 * n * n + 2 * COEFF * n;

    while(lb + 1 < rb)
    {
        i64 mid = (lb+rb) >> 1;

        if(BinarySearch_Inner(mid))
            lb = mid;
        else
            rb = mid;
    }
    return lb ;
}

i64 BinarySearch_Inner(i64 x)
{
    i64 cnt = 0;
    for(int j = 1; j <= n; j++)
    {
        int lb = 0, rb = n+1;
        while(lb+1 < rb)
        {
            int mid = (lb+rb) >> 1;
            if(f(mid, j) < x)
                lb = mid;
            else
                rb = mid;
        }
        cnt += lb ;
    }

    return cnt < m;
}
