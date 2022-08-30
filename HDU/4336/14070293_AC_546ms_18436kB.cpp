#include <iostream>
#include <cstdio>
#include <cstring>
#include <iomanip>
#include <vector>
using namespace std;
const int MAXN = 20;
const int MAXM = 1050000;
double dp[MAXM+5], probSum[MAXM+5], prob[MAXN+5];

int n;

void init()
{
    for(int i = 0; i < (1 << n); i++)
    {
        probSum[i] = 0;
        for(int j = 0; j < n; j++)
            if(i & (1 << j))
                probSum[i] += prob[j+1];
    }
}

int main()
{
    while(cin >> n)
    {
        double probNothing = 0;
        dp[(1<<n)-1] = 0;
        for(int i = 1; i <= n; i++)
            cin >> prob[i], probNothing += prob[i];
        probNothing = 1 - probNothing;
        init();

        for(int i = (1 << n)-2; i >= 0; i--)
        {
            double curProb = 1 - (probSum[i] + probNothing);
            double curExpt = 0;
            for(int j = 0; j < n; j++)
                if(!((1 << j) & i))
                    curExpt += prob[j+1] * dp[i | (1 << j)];
            dp[i] = (curExpt + 1) / curProb;
        }
        cout << fixed << setprecision(6) << dp[0] << endl ;
    }
}
