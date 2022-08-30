#include <iostream>
#include <algorithm>
#include <utility>
using namespace std;
const int MAXN = 50000;
typedef pair<int, int> pii;

pii seg[MAXN+5];
int n, ans;

int main()
{
    cin >> n;
    for(int i = 1; i <= n; i++)
        cin >> seg[i].first >> seg[i].second;
    sort(&seg[1], &seg[n+1]);
    int prev = seg[1].second;

    for(int i = 2; i <= n; i++)
    {
        if(seg[i].second <= prev)
            ans = max(ans, seg[i].second - seg[i].first);
        else
            ans = max(ans, prev - seg[i].first), \
            prev = seg[i].second;
    }
    cout << ans << endl;
}
