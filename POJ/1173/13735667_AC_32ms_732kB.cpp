#include <iostream>
#include <iterator>
#include <cstring>
using namespace std;

const int MAXN = 33 ;
int n, k, m, s;
int DP[MAXN+5][MAXN+5];
char input[MAXN+5];
int comp[MAXN+5];

void getDP();
void compress();
int calcAns();

int main()
{

    cin >> n >> k >> m ;
    getDP();
    cout << DP[n][k] << endl ;

    cin >> s ;
    while(s--)
    {
        cin >> input ;
        compress();
        cout << calcAns() << endl ;
        //copy(&comp[0], &comp[10], ostream_iterator<int> (cerr, " "));
        //cerr << endl ;
    }
}

void getDP()
{
    DP[0][0] = 1;
    for(int j = 1; j <= k; j++)
        for(int i = 1; i <= n; i++)
        {
            DP[i][j] = DP[i-1][j] + DP[i-1][j-1];
            if(i - m >= 1)
                DP[i][j] -= DP[i-m-1][j-1];
        }

}

void compress()
{
    int cnt = 0, comcnt = 0;
    char fir;
    for(int i = 0; i < n;)
    {
        cnt = 0;
        fir = input[i];
        do
            cnt++;
        while(input[++i] == fir);
        comp[comcnt++] = cnt;
    }
}

int calcAns()
{
    int cnt = 0, pending = n;
    for(int i = 0; i < k-1; i++)
    {
        if(i & 1)           // White bars
        {
            for(int j = m; j > comp[i]; j--)
                if(pending >= j)
                    cnt += DP[pending-j][k-i-1];
        }
        else                // Black bars
        {
            for(int j = 1; j < comp[i]; j++)
                if(pending >= j)
                    cnt += DP[pending-j][k-i-1];
        }

        pending -= comp[i];
    }
    return cnt;
}
