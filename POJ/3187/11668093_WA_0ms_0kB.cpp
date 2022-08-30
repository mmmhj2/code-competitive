#include <iostream>
#include <algorithm>
using namespace std;

const int MAXN = 10;

int com[MAXN+3][MAXN+3], n, t, ans[MAXN+2];
bool vist[MAXN];
bool flag = false;

int initCom()
{
    for(int i = 0; i < MAXN; i++)
    {
        com[i][0] = com[i][i] = 1;
    }
    for(int i = 2; i < MAXN; i++)
        for(int j = 1; j < i; j++)
        {
            com[i][j] = com[i-1][j] + com[i-1][j-1];
        }
    return 1;
}

int DFS(int, int = 0);
void printans()
{
    for(int i = 0 ; i < n-1; i++)
        cout << ans[i] << " ";
    cout << ans[n-1] << endl;
}

int main()
{
    initCom();
    /*
    for(int i = 0; i <= MAXN; i++)
    {
        for(int j = 0; j <= MAXN; j++)
        {
            cout << com[i][j] << " ";
        }
        cout << endl;
    }
    */
    cin >> n >> t;
    DFS(0);
    return 0;
}

int DFS(int stp, int sum)
{
    if(flag || sum > t)
        return -1;
    if(stp == n && sum == t)
    {
        flag = true;
        printans();
        return 1;
    }
    for(int i = 1; i <= n; i++)
    {
        if(vist[i]) continue;
        vist[i] = true;
        ans[stp] = i;
        DFS(stp+1, sum + i*com[n-1][stp]);
        vist[i] = false;
    }
    return 0;
}
