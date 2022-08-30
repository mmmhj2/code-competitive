#include <iostream>
using namespace std;
const int MAXN = 100000;
typedef long long int i64;

int n;
int a[MAXN+5];

i64 ans;
i64 count1, count2;

int main()
{
    cin >> n;
    for(int i = 1; i <= n; i++)
        cin >> a[i];

    for(int i = n; i >= 1; i--)
    {
        switch(a[i])
        {
        case 1:
            ans += count1 + n - i;
            count1++;
            break;
        case 2:
            ans += count1 + count2;
            count2++;
            break;
        default:
            ans += count1;
        }
    }
    cout << ans << endl ;
}
