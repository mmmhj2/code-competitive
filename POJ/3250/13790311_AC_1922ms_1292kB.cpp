#include <iostream>
#include <stack>
using namespace std;
const int MAXN =  80000;
long long ans;
int n;
int Height[MAXN+5];

int main()
{
    stack <int> stk;
    cin >> n ;
    for(int i = 1; i <= n; i++)
    {
        cin >> Height[i] ;
        while(!stk.empty() && stk.top() <= Height[i])
            stk.pop();
        ans += stk.size();
        stk.push(Height[i]);
    }
    cout << ans << endl ;
}
