#include <iostream>
#include <cstring>
using namespace std;

const int MAXN = 5000;

int dir[MAXN+10];
int filp[MAXN+10];

int n;

int checkAns(int k);

int main()
{
    cin >> n;

    for(int i = 1; i <= n; i++)
    {
        char t;
        cin >> t ;
        dir[i] = (t=='B');
    }

    int ans = 0x7fffffffl;
    int stp = 0x7fffffffl;
    for(int i = 1; i <= n; i++)
    {
        int t = checkAns(i);
        if(t < 0)
            continue;
        //ans = min(ans, t);
        if(stp > t)
        {
            ans = i;
            stp = t;
        }
    }
    cout << ans << " " << stp << endl;
}

int checkAns(int k)
{
    int sum = 0, ans = 0;
    memset(filp, 0x00, sizeof filp);

    for(int i = 1; i+k-1 <= n; i++)
    {
        if((dir[i] + sum) & 1)
            filp[i] = 1, ans++;
        sum += filp[i];
        if(i-k+1 >= 1)
            sum -= filp[i-k+1];
    }

    for(int i = n-k+2; i <= n; i++)
    {
        if(dir[i]+sum & 1)
            return -1;
        if(i-k+1 >= 1)
            sum -= filp[i-k+1];
    }
    return ans ;
}