#include <iostream>
using namespace std;

typedef int64_t i64;
typedef uint64_t u64;

constexpr int MAXN = 2e5 + 10;
constexpr int MAXN_STRICT = 200000;
constexpr int MOD = 998244353;

i64 fact[MAXN], inv[MAXN], invFact[MAXN];

void init()
{
    fact[0] = 1, inv[1] = 1, invFact[0] = 1;
    for(int i = 1; i <= MAXN_STRICT; i++)
        fact[i] = fact[i-1] * i % MOD ;
    for(int i = 2; i <= MAXN_STRICT; i++)
        inv[i] = (MOD - MOD / i) * inv[MOD % i] % MOD;
    for(int i = 1; i <= MAXN_STRICT; i++)
        invFact[i] = invFact[i-1] * inv[i] % MOD;
}

i64 getC(i64 n, i64 m)
{
    // n! / (m! * (n-m)!)
    return fact[n] * invFact[m] % MOD * invFact[n - m] % MOD ;
}

i64 F[1000000 + 5];
int main()
{
    ios::sync_with_stdio(false), cin.tie(nullptr);
    init();

    int T;
    cin >> T ;
    while(T--)
    {
        int N, M, K;
        cin >> N >> M >> K ;

        for(int p = 0; p <= M; p++)
            if(K - N * p < 0)
                F[p] = 0;
            else
                F[p] = getC(M, p) * getC(K - N * p + M - 1, M - 1) % MOD;
        for(int i = M-1; i >= 0; i--)
            F[i] = (F[i] - F[i+1] + MOD) % MOD ;
        cout << F[0] << endl ;
    }
    return 0;
}
