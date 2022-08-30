#include <iostream>
#include <cstring>
#include <vector>
#include <queue>
using namespace std;
const int MAXN = 200;

int garden[MAXN+5];
queue <int> q1;
queue <int> q2;

int main()
{
    int t, n, k, tmp;
    cin >> t;
    while(t--)
    {
        int ans = 0;
        while(!q1.empty())
            q1.pop();
        while(!q2.empty())
            q2.pop();

        memset(garden, 0x00 ,sizeof garden);
        cin >> n >> k;
        for(int i = 1; i <= k; i++)
        {
            cin >> tmp;
            garden[tmp] = true;
            q1.push(tmp);
        }
        while(!q1.empty())
        {
            ans++;
            while(!q1.empty())
            {
                int fnt = q1.front();
                q1.pop();
                if((!(fnt-1 <= 0) && (!garden[fnt-1])))
                {
                    q2.push(fnt-1);
                    garden[fnt-1] = true;
                }
                if((!(fnt+1 > n) &&(!garden[fnt+1])))
                {
                    q2.push(fnt+1);
                    garden[fnt+1] = true;
                }

            }
            while(!q2.empty())
            {
                int fnt = q2.front();
                q2.pop();   q1.push(fnt);
            }
        }
        cout << ans << endl;
    }
    return 0;
}
