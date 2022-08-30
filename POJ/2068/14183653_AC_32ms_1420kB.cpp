#include <iostream>
#include <cstring>
using namespace std;

const int MAX_PLAYER = 20;
const int MAX_TAKE   = 16;
const int MAX_PILE   = 8192;

short int DP[MAX_PLAYER+5][MAX_PILE+5];
int take[MAX_PLAYER+5];

int n, pile;

int solve(int player, int left)
{
    short int & cur = DP[player][left];

    int nextPlayer = player + 1 ;
    if(nextPlayer > n * 2)  nextPlayer = 1;

    if(cur >= 0)
        return cur;
    if(!left)
        return (cur = 1);
    cur = 0;

    for(int i = 1; i <= take[player]; i++)
        if(i > left)
            break;
        else
        {
            cur = !solve(nextPlayer, left - i);
            if(cur)
                break;
        }

    return cur;
}

int main()
{
    ios::sync_with_stdio(false);
    while(cin >> n && n)
    {
        memset(DP, 0xff, sizeof DP);
        cin >> pile;
        for(int i = 1; i <= 2 * n; i++)
            cin >> take[i] ;

        cout << solve(1, pile) << endl ;
    }
    return 0;
}
