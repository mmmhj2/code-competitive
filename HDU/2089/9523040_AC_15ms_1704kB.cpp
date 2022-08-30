#include<iostream>
#include<cstring>
using namespace std;

int n, m;
int f[10][15];
int digit[10];

int divide(int x)
{
    memset(digit, 0x00, sizeof(digit));
    int cnt  = 0;
    while(x >= 10)
    {
        digit[++cnt] = x % 10;
        x = x/10;
    }
    digit[++cnt] = x;
    return cnt;
}

namespace my_func
{
int count(int len)
{
    int ans = 0;
//    cout << "Length" << len << endl;
    for(int i = len; i >= 1; i--)
    {
        for(int j = 0; j < digit[i]; j++)
        {
            if(j != 4 && !(j == 2 && digit[i+1] == 6))
            {
                ans += f[i][j];
            }
        }
        if(digit[i] == 4 || (digit[i] == 2 && digit[i+1] == 6) )
            break;
    }
    return ans;
}
}

int main(int argc, char* argv[])
{
    f[0][0] = 1;
    for(int i = 1; i <= 7; i++)
    {
        for(int j = 0; j <= 9; j++)
        {
            for(int k = 0; k <= 9; k++)
            {
                if(j != 4 && !(j == 6 && k == 2))
                {
                    f[i][j] += f[i-1][k];
                    //cout << i << j << k << f[i][j] << endl;
                }
            }
        }
    }
    while(cin >> n >> m)
    {
        if(n == 0 && m == 0)    break;
//      cout << n << m;
        int len = divide(n);
        int cnt1 = my_func::count(len);
//        cout << digit[1] << digit[2] << digit[3] << digit[4] << endl;

        len = divide(m+1);
        int cnt2 = my_func::count(len);
//        cout << digit[1] << digit[2] << digit[3] << digit[4] << endl;
        cout << cnt2-cnt1 << endl;
    }
}
