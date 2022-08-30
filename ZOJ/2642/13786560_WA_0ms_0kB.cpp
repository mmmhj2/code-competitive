#include <iostream>
#include <stack>
using namespace std;

typedef long long i64;
const int MAXN = 100000;

int n;
int num[MAXN+5], stk[MAXN+5];
i64 sum[MAXN+5], ans = -1;
int L[MAXN+5], ansL, ansR;

int main()
{
    int top = 0;
    cin >> n ;
    for(int i = 1; i <= n; i++)
    {
        cin >> num[i];
        sum[i] = sum[i-1] + num[i];
    }
    num[++n] = -1;

    for(int i = 1; i < n; i++)
    {
        if(!top || num[i] > num[stk[top-1]])
        {
            stk[top++] = i;
            L[i] = i;
            continue;
        }
        if(num[i] == num[stk[top-1]])
            continue;
        while(top >= 1 && num[i] < num[stk[top-1]])
        {
            top--;
            i64 tmpans = 1LL * num[stk[top]] * (sum[i-1] - sum[L[stk[top]]-1]);
            if(tmpans > ans)
            {
                ans = tmpans;
                ansL = L[stk[top]];
                ansR = i-1;
            }
        }
        L[i] = L[stk[top]];
        stk[top++] = i;
    }
    cout << ans << endl << ansL << " " << ansR << endl ;

    return 0;
}
