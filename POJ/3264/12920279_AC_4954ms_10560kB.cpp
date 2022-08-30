#include <cmath>
#include <iostream>
#include <algorithm>
using namespace std;

const int MAXN = 50000;

int SparseTableMin[MAXN+5][25];
int SparseTableMax[MAXN+5][25];
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
                SparseTableMin[i][k] = min(SparseTableMin[i][k-1], SparseTableMin[i+_2pow][k-1]);
                SparseTableMax[i][k] = max(SparseTableMax[i][k-1], SparseTableMax[i+_2pow][k-1]);
            }
        }
    }
}

int main()
{
    int Q, l, r, len;//, ans;
    ios::sync_with_stdio(false);
    cin.tie(0);

    cin >> n >> Q;
    for(int i = 1; i <= n; i++)
    {
        int t;
        cin >> t;
        SparseTableMax[i][0] = SparseTableMin[i][0] = t;
    }

    PreCalc();

    while(Q--)
    {
        cin >> l >> r;
        len = r-l+1;
        int _2exp = int(log(len) / log(2.0));
        int _2pow = (1 << _2exp);
        int _min = min(SparseTableMin[l][_2exp], SparseTableMin[r-_2pow+1][_2exp]);
        int _max = max(SparseTableMax[l][_2exp], SparseTableMax[r-_2pow+1][_2exp]);
        //ans = min(SparseTable[l][_2exp], SparseTable[r-_2pow+1][_2exp]);
        cout << _max - _min << endl ;
    }
    return 0;
}
