#include <algorithm>
#include <iostream>
#include <cstring>
#include <vector>
using namespace std;
typedef int mainRet ;
#define int long long
const int uniform[3][3] = {{0, 0}, {1, 0}, {0, 1}};
int modres[3][3];

void multiMatrix(int mat1[3][3], int mat2[3][3], int mod)
{
    int res[3][3] = {{0, 0, 0}};
    for(int i = 1; i <= 2; i++)
        for(int j = 1; j <= 2; j++)
            for(int k = 1; k <= 2; k++)
            {
                res[i][j] += (mat1[i][k]) * (mat2[k][j]);
                res[i][j] %= mod;
            }

    memcpy(mat1, res, sizeof res);
}

void fastPow(int exp, int mod)
{
    int res[3][3] = {{0,0,0},{0,1,0},{0,0,1}};
    int base[3][3] = {{0,0,0},{0,0,1},{0,1,1}};

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
    int n;
    cin >> n;
    fastPow(n+1, 19999997);
    //int firstMat[3][3] = {{0,0,0},{0,1,1},{0,0,0}};
    //multiMatrix(modres, firstMat, 19999997);

    cout << modres[1][2] << endl ;
}
