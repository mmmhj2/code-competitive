#include <iostream>
#include <stack>
using namespace std;
typedef long long i64;
const int MAXN = 100000;
i64 Height[MAXN+5];
i64 L[MAXN+5], R[MAXN+5];

int main()
{
    ios::sync_with_stdio(false);
    int n;
    while(cin >> n)
    {
        if(!n)
            break;
        for(int i = 0; i < n; i++)
            cin >> Height[i];
        stack <i64> stL, stR;

        for(int i = 0; i < n; i++)
        {
            while(stL.size() && Height[stL.top()] >= Height[i])
                stL.pop();
            if(stL.empty())
                L[i] = 0;
            else
                L[i] = stL.top() + 1;
            stL.push(i);
        }
        for(int i = n-1; i >= 0; i--)
        {
            while(stR.size() && Height[stR.top()] >= Height[i])
                stR.pop();
            if(stR.empty())
                R[i] = n;
            else
                R[i] = stR.top();
            stR.push(i);
        }

        i64 res = 0;
        for(int i = 0; i < n; i++)
            res = max(res, Height[i] * (R[i] - L[i]));
        cout << res << endl ;
    }
    return 0;
}
