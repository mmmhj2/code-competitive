#include <iostream>
#include <cstring>
using namespace std;

const int MAXN = 2000 + 5;
int Matrix[MAXN][MAXN];
int stk[MAXN];
int L[MAXN], R[MAXN];
int m, n;

int getMaxSpace(int f)
{
    //memset(stk, 0x00, sizeof stk);
    int top = 0;
    for(int i = 0; i < n; i++)
    {
        while(top && Matrix[f][stk[top-1]] >= Matrix[f][i])
            top--;
        if(!top)
            L[i] = 0;
        else
            L[i] = stk[top-1] + 1;
        stk[top++] = i;
    }
    top = 0;
    //memset(stk, 0x00, sizeof stk);
    for(int i = n-1; i >= 0; i--)
    {
        while(top && Matrix[f][stk[top-1]] >= Matrix[f][i])
            top--;
        if(!top)
            R[i] = n;
        else
            R[i] = stk[top-1];
        stk[top++] = i;
    }

    int ans = 0;
    for(int i = 0; i <= n; i++)
        ans = max(ans, Matrix[f][i] * (R[i] - L[i]));
    return ans;
}

int main()
{
    while(~scanf("%d%d", &m, &n))
    {
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

        int ans = 0;
        for(int i = 0; i < m; i++)
            ans = max(ans, getMaxSpace(i));
        //cout << ans << endl ;
        printf("%d\n", ans) ;
    }
}
