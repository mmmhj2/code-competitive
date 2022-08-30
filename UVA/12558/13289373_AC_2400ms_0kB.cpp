#include <iostream>
#include <cstring>
#include <cstdio>
#include <set>
using namespace std;
const int MAXN = 0x3ffff;
typedef long long int i64;
typedef set <i64> _bannedList;

_bannedList bannedList;
i64 ans[MAXN], curans[MAXN];
bool found; int maxDepth;

i64 GCD(i64 a, i64 b)
{
    if(b == 0)
        return a;
    return GCD(b, a%b);
}
inline i64 getDem(i64 a, i64 b)
{
    return b/a+1;
}


bool betterSolution(int num)
{
    for(int i = num; i >= 0; i--)
        if(ans[i] != curans[i])
            return ans[i] == -1 || curans[i] < ans[i];
    return false;
}

void DFS(int depth, i64 last, i64 a, i64 b)
{
    if(depth == maxDepth)
    {
        if(b % a)
            return;
        if(bannedList.find(b / a) != bannedList.end())
            return;
        curans[depth] = b / a;
        if(betterSolution(depth))
            memcpy(ans, curans, sizeof curans);
        found = true;
        return;
    }
    last = max(last, getDem(a, b));
    for(int k = last; ; k++)
    {
        if(a * k >= b * (maxDepth - depth + 1))
            break;
        if(bannedList.find(k) != bannedList.end())
            continue;

        curans[depth] = k ;
        i64 t1 = a * k - b;
        i64 t2 = b * k;
        i64 gcd = GCD(t1, t2);
        t1 /= gcd, t2 /= gcd;
        DFS(depth+1, k+1, t1, t2);
    }
    return;
}


int main()
{
    int t, kase = 0;
    cin >> t ;
    while(t--)
    {
        bannedList.clear();
        found = false;
        i64 a, b, n, tmp;
        cin >> a >> b >> n;

        while(n--)
            cin >> tmp ,bannedList.insert(tmp);

        for(maxDepth = 0; !found; maxDepth++)
        {
            memset(ans, 0xff, sizeof ans);
            DFS(0, getDem(a, b), a, b);
            if(found)
                break;
        }

        cout << "Case " << ++kase << ": " << a << "/" << b << "=" ;
        for(int i = 0; i <= maxDepth ; i++)
        {
            if(i)
                cout << "+";
            cout << "1/" << ans[i] ;
        }
        cout << endl ;
    }
}

