#include <algorithm>
#include <iostream>
#include <iomanip>
#include <cstring>
#include <complex>
#include <cfloat>
using namespace std;

#define popCnt(x) __builtin_popcount(x)

using i64 = long long;
using u64 = unsigned i64;
using u32 = unsigned int;

constexpr i64 DIGIT = 1000000000;
constexpr int MAXN = 25;
constexpr int MAXM = 12;
constexpr int MAXM_POWERED = 1 << 12;

i64 dp[MAXN][MAXM_POWERED], fact[MAXN], ans[MAXN];
u32 mp[MAXN];
char MP[MAXN][MAXN];
int cnt[MAXN];
int M, N, K;

void prepare()
{
    fact[0] = 1;
    for(int i = 1; i < MAXN; i++)
        fact[i] = fact[i - 1] * i;
}

void PrintHPMultiplication(i64 x, i64 y)
{
    i64 digit[4] = {0, 0, 0, 0};
    digit[0] = x % DIGIT, digit[1] = x / DIGIT;
    digit[0] *= y, digit[1] *= y;
    digit[1] += digit[0] / DIGIT, digit[0] %= DIGIT;
    digit[2] += digit[1] / DIGIT, digit[1] %= DIGIT;

    int pos = 2;

    while(pos > 0)
    {
        if(digit[pos])
            break;
        pos--;
    }
    cout << digit[pos];

    while(pos)
    {
        pos--;
        cout << setw(9) << setfill('0') << digit[pos];
    }
    cout << endl ;
}

int main()
{
    int T;
    cin >> T ;
    prepare();

    while(T--)
    {
        memset(mp, 0x00, sizeof mp);
        memset(cnt, 0x00, sizeof cnt);
        memset(ans, 0x00, sizeof ans);

        cin >> M >> N >> K ;
        for(int i = 0; i < M; i++)
            cin >> MP[i] ;

        for(int j = 1; j <= N; j++)
            for(int i = 0; i < M; i++)
            {
                mp[j] <<= 1;
                mp[j] |= (MP[i][j - 1] == 'Q');
                if(MP[i][j - 1] == 'Q')
                    cnt[i]++;
            }
        for(u32 finState = 1; finState < (1 << M); finState++)
        {
            dp[0][0] = 1;
            for(int r = 1; r <= N; r++)
            {
                bool flag = false;
                for(u32 mask = finState; true; mask = (mask - 1) & finState)
                {
                    if(dp[r - 1][mask])
                    {
                        if((mp[r] & finState) == mp[r])
                            if(dp[r][mask] += dp[r-1][mask])
                                flag = true;
                        for(u32 diff = (mask ^ finState) & mp[r]; diff; diff &= diff - 1)
                        {
                            u32 lobit = diff & -diff;
                            dp[r][mask | lobit] += dp[r-1][mask];
                            flag = true;
                        }
                        dp[r-1][mask] = 0;
                    }
                    if(!mask)
                        break;
                }
                if(!flag)
                    break;
            }

            ans[popCnt(finState)] += dp[N][finState];

            for(u32 mask = finState; true; mask = (mask - 1) & finState)
            {
                dp[N][mask] = 0;
                if(!mask)
                    break;
            }
        }

        for(int i = 1; i <= K; i++)
            PrintHPMultiplication(ans[i], fact[i]);
    }
}
