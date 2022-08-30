#include <algorithm>
#include <iostream>
#include <cstring>
#include <vector>
using namespace std;

const int MAXM = 100000 + 5;
const int MAXN = 10000 + 5;
bool DP[MAXM][2];
//vector <int> card;
int card[MAXN];
int n, m;
/*
void dpProc(int val)
{
    for(int i = m; i > val; i--)
        for(int k = 0; k <= 1; k++)
            DP[i][k] = DP[i - val][!k];
    DP[val][1] = true;
}
*/

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    while(cin >> n >> m)
    {
        if(n == 0 && m == 0)
            break ;

        for(int i = 0; i < n; i++)
            cin >> card[i];
        sort(&card[0], &card[n]);
        memset(DP, 0x00, sizeof DP);
        DP[card[0]][1] = true;

        for(int i = 1; i < n; i++)
        {
            for(int j = m; j > card[i]; j--)
                for(int k = 0; k < 2; k++)
                    if(DP[j - card[i]][k])
                        DP[j][!k] = true;
            DP[card[i]][1] = true;
        }

        int cnt = 0;
        for(int i = 1; i <= m; i++)
            if(DP[i][1] && !DP[i][0])
                cnt++;
        cout << cnt << endl ;
    }
    return 0;
}
