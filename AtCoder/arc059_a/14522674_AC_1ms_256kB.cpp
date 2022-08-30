#include <iostream>
using namespace std;

const int MAXN = 100 + 10;
int a[MAXN];
long long ans = 0x7fffffff;
int n, MIN = 0x7fffffff, MAX = 0x80000000;

int main()
{
    cin >> n ;
    for(int i = 1; i <= n; i++)
        cin >> a[i] , MIN = min(a[i], MIN), MAX = max(a[i], MAX);

    for(int i = MIN; i <= MAX; i++)
    {
        long long tmp = 0;
        for(int k = 1; k <= n; k++)
            tmp += (a[k] - i) * (a[k] - i);
        ans = min(tmp, ans);
    }
    cout << ans << endl ;
}
