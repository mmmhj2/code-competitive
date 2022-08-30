#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

const int MAXN = 200 + 5;
const int INF = 0x7FFFFFFF;
const int MOD = 1e9 + 7;

int N, slen, ans;
int dp[MAXN][MAXN][MAXN][2];
int len[MAXN][2];
string str;

int calc(const string & a)
{
    int l = a.length();
    for(int i = l; i > 0; i--)
        if(str.substr(0, i) == a.substr(l - i, i))
            return i;
    return 0;
}

int main()
{
    cin >> N >> str;
    slen = str.length();

    len[0][(str[0] == ')')] = 1;

    string prefix;
    for(int i = 0; i < slen; i++)
    {
        prefix += str[i];
        prefix.push_back('(');
        len[i+1][0] = calc(prefix);
        prefix.pop_back();
        prefix.push_back(')');
        len[i+1][1] = calc(prefix);
        prefix.pop_back();
    }

    ****dp = 1;

    for(int i = 0; i < (N << 2); i++)
    {
        for(int j = 0; j <= N; j++)
        {
            for(int pos = 0; pos <= slen; ++pos)
            {
                for(int f = 0; f <= 1; f++)
                {
                    if(!dp[i][j][pos][f])
                        continue;
                    int & t1 = dp[i+1][j+1][len[pos][0]][f | (len[pos][0] == slen)];
                    if(j + 1 <= N)
                        t1 = (t1 + dp[i][j][pos][f] + MOD) % MOD ;
                    int & t2 = dp[i+1][j-1][len[pos][1]][f | (len[pos][1] == slen)];
                    if(j > 0)
                        t2 = (t2 + dp[i][j][pos][f] + MOD) % MOD ;
                }
            }
        }
    }

    for(int i = 0; i <= slen; i++)
        ans = (ans + dp[2 * N][0][i][1] + MOD) % MOD ;

    cout << ans << endl ;

    return 0;
}

