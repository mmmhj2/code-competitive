#include <iostream>
#include <deque>
using namespace std;
const int MAXN = 100000;
typedef long long i64;
int n, f;
//int num[MAXN + 5];
i64 sum[MAXN + 5];
i64 dq[MAXN+5];
double ans;

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cin >> n >> f ;
    for(int i = 1; i <= n; i++)
        cin >> sum[i], sum[i] += sum[i-1];
    int tail = 0, head = 0;
    for(int i = f; i <= n; i++)
    {
        int now = i - f ;
        while(head + 1 < tail)
        {
            i64 dy1 = sum[dq[tail-1]] - sum[dq[tail-2]];
            i64 dy2 = sum[now] - sum[dq[tail-1]];
            i64 dx1 = (dq[tail-1]) - (dq[tail-2]);
            i64 dx2 = now - dq[tail-1];
            if(dy1 * dx2 > dy2 * dx1)
                tail--;
            else
                break;
        }
        dq[tail++] = now;
        while(head + 1 < tail)
        {
            i64 y1 = sum[dq[head]], \
                y2 = sum[dq[head+1]], \
                y3 = sum[i];
            i64 x1 = dq[head], \
                x2 = dq[head+1], \
                x3 = i;
            if((y3-y1) * (x3-x2) < (y3-y2) * (x3-x1))
                head++;
            else
                break;
        }
        double tmp = 1.00 * (sum[i] - sum[dq[head]]) / (i-dq[head]);
        ans = max(ans, tmp);
    }
    cout << (int)(ans * 1000) << endl ;
}
