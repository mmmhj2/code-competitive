#include <algorithm>
#include <iostream>
#include <cmath>
using namespace std;
const int MAXN = 10;

int n, a, b;
int hp[MAXN+5];
int ans = 0x7fffffff;

void dfs(int cur, int tans)
{
    if(cur > n)
    {
        ans = min(ans, tans);
        return;
    }
    // Do not cast a spell here if previous one is dead
    if(hp[cur-1] < 0)
        dfs(cur+1, tans);
    // Cast a spell here if previous one is alive
    int ans1(0);
    if(hp[cur-1] >= 0)
    {
        ans1 = hp[cur-1] / b + 1;
        int directdamage = ans1 * a;
        int areadamage = ans1 * b;
        hp[cur-1] -= areadamage;
        hp[cur] -= directdamage;
        hp[cur+1] -= areadamage;

        dfs(cur+1, tans + ans1);

        hp[cur-1] += areadamage;
        hp[cur] += directdamage;
        hp[cur+1] += areadamage;
    }
    // Cast a spell if current target is alive and takes more hit to kill it
    int ans2(hp[cur] / a + 1);
    if(hp[cur] >= 0 && ans2 > ans1)
    {
        // Enumerate the number of hits
        for(int i = ans1+1; i <= ans2; i++)
        {
            int directdamage = i * a;
            int areadamage = i * b;

            hp[cur-1] -= areadamage;
            hp[cur] -= directdamage;
            hp[cur+1] -= areadamage;

            dfs(cur+1, tans + i);

            hp[cur-1] += areadamage;
            hp[cur] += directdamage;
            hp[cur+1] += areadamage;
        }
    }
    return ;
}

int main()
{
    cin >> n >> a >> b;
    for(int i = 1; i <= n; i++)
        cin >> hp[i];

    int tmpsum = 0;
    while(hp[1] >= 0)
        hp[1] -= b, hp[2] -= a  , hp[3] -= b  , tmpsum++;
    while(hp[n] >= 0)
        hp[n] -= b, hp[n-1] -= a, hp[n-2] -= b, tmpsum++;
    //cerr << tmpsum << endl;

    dfs(2, 0);

    cout << ans + tmpsum << endl;

}
