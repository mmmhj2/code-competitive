#include <functional>
#include <algorithm>
#include <iostream>
#include <iomanip>
#include <cstring>
#include <map>
using namespace std;

typedef long long i64;
constexpr int MAXN = 100000 + 20 ;

class Stock
{
    typedef function<void(int, int)> CALLBACKFUNC ;
    i64 tot, accumlated_cst;
    map <int, int> s;
public:
    Stock()
    {
        tot = 0, accumlated_cst = 0;
    }

    int erase(int num, CALLBACKFUNC fn)
    {
        while(!s.empty() && num)
        {
            if(num >= s.begin()->second)
            {
                fn(s.begin()->second, s.begin()->first + accumlated_cst);
                num -= s.begin()->second;
                tot -= s.begin()->second;
                s.erase(s.begin());
            }
            else
            {
                fn(num, s.begin()->first + accumlated_cst);
                tot -= num;
                s.begin()->second -= num;
                num = 0;
            }
        }
        return num;
    }

    void discard(int sz)
    {
        while(tot > sz)
        {
            int res = tot - s.rbegin()->second;
            if(res < sz)
                s.rbegin()->second -= tot - sz,
                                      tot = sz;
            else
                tot = res,
                s.erase(--s.end());
        }
    }

    void push(int sz, int cost)
    {
        s[cost - accumlated_cst] += sz;
        tot += sz;
    }

    void accumulate(int delta)
    {
        accumlated_cst += delta;
    }
};

int K;

int c[MAXN], d[MAXN], m[MAXN], p[MAXN];
int e[MAXN], R[MAXN], E[MAXN];

int main()
{
    Stock * stock;
    ios::sync_with_stdio(false), cin.tie(nullptr);

    int T;
    cin >> T ;

    while(T--)
    {
        i64 ans;
        int minRaw;

        ans = 0;
        minRaw = 0x7FFFFFFF;
        stock = new Stock;

        cin >> K ;

        for(int i = 1; i <= K; i++)
            cin >> c[i] >> d[i] >> m[i] >> p[i] ;
        for(int i = 1; i < K; i++)
            cin >> e[i] >> R[i] >> E[i];
        e[K] = R[K] = E[K] = 0;

        for(int i = 1; i <= K; i++)
        {
            minRaw = min(minRaw, c[i]);
            stock->push(p[i], minRaw + m[i]);

            if(stock->erase(d[i], [&ans] (int sz, int cost) -> void {ans += 1LL * cost * sz;}) > 0)
            {
                ans = -1;
                break;
            }

            stock->discard(e[i]);
            minRaw += R[i];
            stock->accumulate(E[i]);
        }

        cout << ans << endl ;

        delete stock;
    }
}