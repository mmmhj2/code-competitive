#include <iostream>
#include <vector>
using namespace std;

const int MOD = 1e9+7;
const int MAXN = 5000000 + 5;
typedef long long int i64;
i64 f[MAXN], g[MAXN];
vector <int> PrimeList;
bool NotPrime[MAXN];
int n, m, t, k;

i64 quickPow(i64 base, int exp)
{
    i64 ans = 1;    base %= MOD;
    while(exp)
    {
        if(exp & 1)
            ans = base * ans % MOD;
        exp >>= 1;
        base = base * base % MOD;
    }
    return ans ;
}

void LinearSieve()
{
    f[1] = 1;
    for(int i = 2; i <= 5000000; i++)
    {
        if(!NotPrime[i])
        {
            PrimeList.push_back(i);
            g[PrimeList.size()] = quickPow(i, k);
            f[i] = (g[PrimeList.size()] - 1 + MOD) % MOD;
        }
        for(unsigned j = 0; j < PrimeList.size(); j++)
        {
            i64 tmp = i * PrimeList[j];
            if(tmp > 5000000)
                break;
            NotPrime[tmp] = true;
            if(i % PrimeList[j] == 0)
            {
                f[tmp] = f[i] * g[j+1] % MOD;
                break;
            }
            f[tmp] = f[i] * f[PrimeList[j]] % MOD;
        }
    }
    for(int i = 1; i <= 5000000; i++)
        f[i] = (f[i] + f[i-1]) % MOD;
}

int main()
{
    cin >> t >> k;
    LinearSieve();
    while(t--)
    {
        cin >> n >> m ;
        if(n > m)
            swap(n, m);
        int j = 0;  i64 ans = 0;
        for(int i = 1; i <= n; i = j + 1)
        {
            j = min(min(n/(n/i), m/(m/i)), n);
            ans = (ans + 1LL * (1LL * (n/i) * (m/i) % MOD) * ((f[j] - f[i-1] + MOD) % MOD)) % MOD;
        }
        cout << (ans % MOD + MOD) % MOD << endl ;
    }
}
