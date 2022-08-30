#include <iostream>
#include <vector>
using namespace std;
const int MAXN = 50 + 5;
const int MAXM = MAXN * MAXN;
const int BASE = MAXM;
const int MAXL = BASE * 2;
typedef long long i64;

int N, A;
int contrib[MAXN];
i64 DP[MAXN][MAXL];

int main()
{
    int t;
    cin >> N >> A ;
    for(int i = 1; i <= N; i++)
        cin >> t ,
        contrib[i] = t-A;

    DP[0][BASE] = 1;
    for(int i = 0; i <= N; i++)
    {
        for(int j = 0; j < MAXL; j++)
        {
            if(DP[i][j])
            {
                DP[i+1][j + contrib[i+1]] += DP[i][j];
                DP[i+1][j] += DP[i][j] ;
            }
        }
    }

    cout << DP[N][BASE]-1 << endl ;
}
