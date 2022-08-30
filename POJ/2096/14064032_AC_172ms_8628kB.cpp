#include <iostream>
#include <cstdio>
#include <cstring>
#include <iomanip>
#include <vector>
using namespace std;
const int MAXN = 1000;
double DP[MAXN+5][MAXN+5];

int main()
{
    int n, s;
    cin >> n >> s;

    DP[n][s] = 0;
    for(int i = n; i >= 0; i--)
    {
        for(int j = s; j >= 0; j--)
        {
            if(i == n && j == s)
                continue;
            DP[i][j] = (i*(s-j)*DP[i][j+1]+(n-i)*j*DP[i+1][j]+(n-i)*(s-j)*DP[i+1][j+1]+n*s)/(n*s-i*j);
        }
    }
    cout << fixed << setprecision(4) << DP[0][0] << endl ;
}
