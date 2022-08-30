#include <iostream>
#include <iterator>
#include <vector>
#include <set>
using namespace std;

typedef long long int i64;
const int MAXN = 100;
int n, m;
i64 sum[MAXN];
vector <int> fact;

i64 QuickPow(i64 base, i64 exp)
{
    i64 res = 1;
    while(exp)
    {
        if(exp & 1)
            res *= base;
        base *= base;
        exp >>= 1LL;
    }
    return res;
}

void DFS(i64 cur, i64 lvl, i64 dem)
{
    if(lvl >= fact.size())
        return ;

    dem *= fact[cur];
    sum[lvl] += QuickPow(m / dem, n);

    for(i64 neocur = cur + 1; neocur < fact.size(); neocur++)
        DFS(neocur, lvl+1, dem);
}

void getUniqueFact(i64 x, vector <int> & UniFact)
{
    UniFact.clear();
    for(int i = 2; i * i <= x; i++)
    {
        if(x % i == 0)
        {
            UniFact.push_back(i);
            while(!(x % i))
                x /= i ;
        }
    }
    if(x > 1)
        UniFact.push_back(x);
}

int main()
{
    cin >> n >> m ;
    getUniqueFact(m, fact);

    for(int i = 0; i < fact.size(); i++)
        DFS(i, 0, 1);
    for(int i = 0; i < fact.size(); i++)
        if(!(i & 1))
            sum[i] *= -1 ;

    i64 ans = QuickPow(m, n);
    for(int i = 0; i < fact.size(); i++)
        ans += sum[i];
    cout << ans << endl ;
    return 0;
}
