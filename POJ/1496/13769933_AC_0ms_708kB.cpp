#include <iostream>
using namespace std;

const int MAXN = 26;

int C[MAXN + 5][MAXN + 5];

void getCombine()
{
    for(int i = 0; i <= MAXN; i++)
        for(int j = 0; j <= i; j++)
            if(!j || i == j)
                C[i][j] = 1;
            else
                C[i][j] = C[i-1][j] + C[i-1][j-1];
    C[0][0] = 0;
}

int main()
{
    int len, ans;
    string str;
    getCombine();
    while(cin >> str)
    {
        ans = 0;
        len = str.length();
        for(int i = 1; i < len; i++)
            if(str[i] <= str[i-1])
                goto END;

        for(int i = 1; i < len; i++)
            ans += C[26][i];
        for(int i = 0; i < len; i++)
        {
            //char ch = (i == 0 ? 'a' : str[i-1]+1);
            for(char ch = (i == 0 ? 'a' : str[i-1]+1); ch < str[i]; ch++)
                ans += C['z'-ch][len-i-1];
        }
        ans ++;

END:
        cout << ans << endl ;
    }
}
