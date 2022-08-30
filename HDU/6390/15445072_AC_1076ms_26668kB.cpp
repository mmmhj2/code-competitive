#include <iostream>
#include <cstring>
#include <vector>
using namespace std;

const int MAXN = 1e6 + 10;
using i64 = long long;

bool NotPrime[MAXN];
vector <int> prime;

int phi[MAXN], mu[MAXN];
void linearSieve()
{
    mu[1] = 1;
    phi[1] = 1;
    for (int i = 2; i < MAXN; i++)
    {
        if(!NotPrime[i])
            prime.push_back(i), phi[i] = i - 1, mu[i] = -1;

        for(auto itr = prime.begin(); itr != prime.end(); ++itr)
        {
            i64 j = 1LL * i * (*itr);
            if(j >= MAXN)
                break;

            NotPrime[j] = true;

            if(i % (*itr) == 0)
            {
                phi[j] = phi[i] * (*itr);
                mu[j] = 0;
                break;
            }
            phi[j] = phi[i] * (*itr - 1);
            mu[j] = -mu[i];
        }
    }
}

i64 ExGCD(i64 a, i64 b, i64 &x, i64 &y)
{
    if(b == 0)
        return (x = 1, y = 0, a);
    if(a == 0)
        return (x = 0, y = 1, b);

    i64 ret = ExGCD(b, a%b, y, x);
    y -= (a / b) * x;
    return ret;
}

i64 getInversion(i64 a, i64 mod)
{
    i64 x, y;
    ExGCD(a, mod, x, y);
    x %= mod ;

    while(x < 0)
        x += mod;
    //cerr << "Calculating : " << a << " " << mod << " " << x << endl ;
    return x;
}

i64 F[MAXN], f[MAXN];
void RunTransform(int m, int n, int mod)
{
    int MIN = min(m, n);
    memset(F, 0x00, sizeof F);
    memset(f, 0x00, sizeof f);
    for(int i = 1; i <= MIN; i++)
        F[i] = 1LL * (m / i) * (n / i);

    for(int i = 1; i <= MIN; i++)
        for(int j = i; j <= MIN; j += i)
            f[i] += 1LL * mu[j / i] * F[j];

    for(int i = 1; i <= MIN; i++)
        f[i] %= mod;
}

int solve(int m, int n, int mod)
{
    RunTransform(m, n, mod);
    int MIN = min(m, n);
    i64 ans = 0;

    for(int i = 1; i <= MIN; i++)
        ans = (ans + 1LL * i * getInversion(phi[i], mod) % mod * f[i]) % mod;

    while(ans < 0)
        ans += mod;
    return ans;
}

int main()
{
    linearSieve();
    //for(int i = 1; i < 20; i++)
    //    cerr << i << " " << mu[i] << " " << phi[i] << endl ;
    int T ;
    scanf("%d", &T);
    while(T--)
    {
        int m, n, p;
        //cin >> m >> n >> p;
        //cout << solve(m, n, p) << endl ;
        scanf("%d%d%d", &m, &n, &p);
        printf("%d\n", solve(m, n, p));
    }

    return 0;
}
