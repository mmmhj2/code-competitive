#include <iostream>
#include <deque>
using namespace std;
const int MAXN = 100000;
typedef long long i64;
int n, f;
//int num[MAXN + 5];
i64 sum[MAXN + 5];
double ans;
typedef deque <i64> :: iterator dqi;
typedef deque <i64> :: reverse_iterator dqri;

int main()
{
    deque <int> dq;
    cin >> n >> f ;
    for(int i = 1; i <= n; i++)
        cin >> sum[i], sum[i] += sum[i-1];
    for(int i = f; i <= n; i++)
    {
        int now = i - f ;
        while(dq.size() > 1)
        {
            i64 dy1 = sum[*dq.rbegin()] - sum[*(dq.rbegin()+1)];
            i64 dy2 = sum[now] - sum[*dq.rbegin()];
            i64 dx1 = (*dq.rbegin()) - (*dq.rbegin()+1);
            i64 dx2 = now - *dq.rbegin();
            if(dy1 * dx2 > dy2 * dx1)
                dq.pop_back();
            else
                break;
        }
        dq.push_back(now);
        while(dq.size() > 1)
        {
            i64 y1 = sum[*dq.begin()], \
                y2 = sum[*(dq.begin()+1)], \
                y3 = sum[i];
            i64 x1 = *dq.begin(), \
                x2 = *(dq.begin()+1), \
                x3 = i;
            if((y3-y1) * (x3-x2) < (y3-y2) * (x3-x1))
                dq.pop_front();
            else
                break;
        }
        double tmp = 1.00 * (sum[i] - sum[*dq.begin()]) / (i-*dq.begin());
        ans = max(ans, tmp);
    }
    cout << ans * 1000 << endl ;
}
