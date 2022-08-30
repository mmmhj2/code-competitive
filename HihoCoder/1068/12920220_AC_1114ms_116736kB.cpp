#include <cmath>
#include <iostream>
#include <algorithm>
using namespace std;

const int MAXN = 1000000;

int SparseTable[MAXN+5][25];
//int Data[MAXN];
int n;

void PreCalc()
{
    for(int k = 1; k < 25; k++)
    {
        if((1 << k) > n)
            break;
        for(int i = 1; i <= n; i++)
        {
            if(i + (1 << k) - 1 <= n)
            {
                int _2pow = (1 << (k-1));
                SparseTable[i][k] = min(SparseTable[i][k-1], SparseTable[i+_2pow][k-1]);
            }
        }
    }
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    cin >> n;
    for(int i = 1; i <= n; i++)
        cin >> SparseTable[i][0];
    PreCalc();
    int Q, l, r, len, ans;
    cin >> Q;
    while(Q--)
    {
        cin >> l >> r;
        len = r-l+1;
        int _2exp = int(log(len) / log(2.0));
        int _2pow = (1 << _2exp);
        ans = min(SparseTable[l][_2exp], SparseTable[r-_2pow+1][_2exp]);
        cout << ans << endl ;
    }
    return 0;
}
