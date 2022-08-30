#include <algorithm>
#include <iostream>
#include <cstring>
#include <vector>
using namespace std;
typedef int mainRet ;
#define int long long
const int MAXK = 15;
int modres[MAXK][MAXK];
int b[MAXK], c[MAXK];
int k;

void multiMatrix(int mat1[MAXK][MAXK], int mat2[MAXK][MAXK], int mod)
{
    int res[MAXK][MAXK] = {{0}};
    for(int i = 1; i <= k; i++)
        for(int j = 1; j <= k; j++)
            for(int k = 1; k <= ::k; k++)
            {
                res[i][j] += (mat1[i][k]) * (mat2[k][j]);
                res[i][j] %= mod;
            }

    memcpy(mat1, res, sizeof res);
}

void fastPow(int exp, int mod)
{
    int res[MAXK][MAXK] = {{0}};
    int base[MAXK][MAXK] = {{0}};
    for(int i = 1; i+1 <= k; i++)
        base[i][i+1] = 1;
    for(int i = 1; i <= k; i++)
        res[i][i] = 1;
    for(int i = 1; i <= k; i++)
        base[k][i] = c[k-i+1];

    while(exp)
    {
        if(exp & 1)
            multiMatrix(res, base, mod);
        multiMatrix(base, base, mod);
        exp >>= 1;
    }
    memcpy(modres, res, sizeof modres);
}

mainRet main()
{
    int kase;
    cin >> kase;
    while(kase--)
    {
        cin >> k;
        for(int i = 1; i <= k; i++)
            cin >> b[i];
        for(int i = 1; i <= k; i++)
            cin >> c[i];
        int exp;
        cin >> exp;
        if(exp <= k)
            cout << b[exp] << endl ;
        else
        {
            fastPow(exp-k, 1000000000LL);
            int res = 0;

            for(int i = 1; i <= k; i++)
            {
                res += modres[k][i] * b[i] ;
                res %= 1000000000LL;
            }

            cout << res << endl ;
        }

    }
}
