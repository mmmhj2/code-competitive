#include <iostream>
#include <stack>
using namespace std;

const int MAXN = 2000 + 5;
int Matrix[MAXN][MAXN];
int L[MAXN], R[MAXN];
int m, n;

int getMaxSpace(int f)
{
    stack <int> stL, stR;

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

    int ans = 0;
    for(int i = 0; i <= n; i++)
        ans = max(ans, Matrix[f][i] * (R[i] - L[i]));
    return ans;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    while(cin >> m >> n)
    {
        for(int i = 0; i < m; i++)
            for (int j = 0; j < n; j++)
                cin >> Matrix[i][j];
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
        cout << ans << endl ;
    }
}
