#include <iostream>
#include <cstdio>
#include <stack>
using namespace std;

typedef long long i64;
const int MAXN = 100000 + 5;
i64 Matrix[3][MAXN];
i64 L[MAXN], R[MAXN];
int m, n;

i64 getMaxSpace(int f)
{
    stack <i64> stL, stR;

    for(int i = 0; i < n; i++)
    {
        if(stL.size() && Matrix[f][stL.top()] >= Matrix[f][i])
            stL.pop();
        if(stL.empty())
            L[i] = 0;
        else
            L[i] = stL.top() + 1;
        stL.push(i);
    }

    for(int i = n-1; i >= 0; i--)
    {
        if(stR.size() && Matrix[f][stR.top()] >= Matrix[f][i])
            stR.pop();
        if(stR.empty())
            R[i] = n;
        else
            R[i] = stR.top();
        stR.push(i);
    }

    i64 ans = 0;
    for(int i = 0; i <= n; i++)
        ans = max(ans, Matrix[f][i] * (R[i] - L[i]));
    return ans;
}

int main()
{
    while(/*~scanf("%d%d", &m, &n)*/~scanf("%d", &n))
    {
        m = 1;
        if(n == 0)
            break;
        for(int i = 0; i < m; i++)
            for (int j = 0; j < n; j++)
                //cin >> Matrix[i][j];
                scanf("%d", &Matrix[i][j]);
        for(int i = 1; i < m; i++)
            for(int j = 0; j < m; j++)
                if(Matrix[i][j]) Matrix[i][j] += Matrix[i-1][j];
/*
        for(int i = 0; i < m; i++)
        {
            for (int j = 0; j < n; j++)
                cerr << Matrix[i][j];
            cerr << endl ;
        }
*/

        i64 ans = 0;
        for(int i = 0; i < m; i++)
            ans = max(ans, getMaxSpace(i));
        //cout << ans << endl ;
        cout << ans << endl ;
    }
}
