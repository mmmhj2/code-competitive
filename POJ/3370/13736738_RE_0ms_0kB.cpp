#include <iostream>
#include <cstring>
using namespace std;

const int MAXN = 100000;

int n, m;
int pos[MAXN+5];
int sum[MAXN+5];
int val[MAXN+5];

int main()
{
    while(cin >> m >> n)
    {
        memset(pos, 0xFF, sizeof pos);
        memset(sum, 0x00, sizeof sum);
        memset(val, 0x00, sizeof val);
        if((!n) && (!m))
            break;
        pos[0] = 0;
        for(int i = 1; i <= n; i++)
        {
            cin >> val[i];
            sum[i] = sum[i-1] + val[i];
            sum[i] %= m ;
            if(pos[sum[i]] >= 0)
            {
                for(int k = pos[sum[i]] + 1; k <= i; k++)
                    if(k == pos[sum[i]] + 1)
                        cout << k ;
                    else
                        cout << " " << k ;
                cout << endl ;
                cin.sync(); cout << flush ;
                break;
            }
            pos[sum[i]] = i;
        }

    }
    return 0;
}
