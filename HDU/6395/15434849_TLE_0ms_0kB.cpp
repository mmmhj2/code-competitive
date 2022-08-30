#include <iostream>
#include <cstdlib>
#include <cstring>
using namespace std;

using i64 = long long;

const i64 MOD = 1e9 + 7;

struct Matrix
{
    i64 m[3][3];

    Matrix()
    {
        memset(m, 0x00, sizeof m);
    }

    Matrix operator * (const Matrix & x) const
    {
        Matrix ans ;

        for(int k = 0; k < 3; k++)
            for(int i = 0; i < 3; i++)
                for(int j = 0; j < 3; j++)
                    ans.m[i][j] = (ans.m[i][j] + m[i][k] * x.m[k][j] % MOD) % MOD ;

        return ans;
    }
};
Matrix identity, Multiplier;

void PushMatrix(i64 c, i64 d, i64 x)
{
    Multiplier.m[0][0] = 0;
    Multiplier.m[0][1] = 1;
    Multiplier.m[0][2] = 0;
    Multiplier.m[1][0] = c;
    Multiplier.m[1][1] = d;
    Multiplier.m[1][2] = x;
    Multiplier.m[2][0] = 0;
    Multiplier.m[2][1] = 0;
    Multiplier.m[3][2] = 1;
}

Matrix fastPow(Matrix base, i64 exp)
{
    Matrix ans = identity;

    while(exp)
    {
        if(exp & 1)
            ans = ans * base;
        base = base * base;
        exp >>= 1;
    }
    return ans;
}

int main()
{
    Matrix ans;
    i64 A, B, C, D, P, N;

    for(int i = 0; i < 3; i++)
        identity.m[i][i] = 1;

    int T;
    cin >> T ;

    while(T--)
    {
        cin >> A >> B >> C >> D >> P >> N ;

        if(N == 1)
            cout << A << endl ;
        else
        {
            ans.m[0][0] = A, ans.m[1][0] = B, ans.m[2][0] = 1;
            if (P <= N)
            {
                for(i64 i = 3; i <= P; i = P / (P / i) + 1)
                {
                    PushMatrix(C, D, P / i);
                    Multiplier = fastPow(Multiplier, P / (P / i) + 1 - i);
                    ans = Multiplier * ans;
                }
                PushMatrix(C, D, 0);
                Multiplier = fastPow(Multiplier, N - max(2LL, P));
                ans = Multiplier * ans;
            }
            else
            {
                for(i64 i = 3; i <= N; i = P / (P / i) + 1)
                {
                    PushMatrix(C, D, P / i);
                    Multiplier = fastPow(Multiplier, min(N, P / (P / i)) - i - 1);
                    ans = Multiplier * ans;
                }
            }
            cout << ans.m[1][0] << endl ;
        }

    }

    return 0;
}
