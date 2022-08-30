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
                probSum[i] += prob[j];
    }
}

int main()
{
    while(cin >> n)
    {
        double probNothing = 1;
        for(int i = 0; i < n; i++)
            cin >> prob[i], probNothing -= prob[i];
        init();

        for(int i = (1 << n)-2; i >= 0; i--)
        {
            double curProb = 1 - (probSum[i] + probNothing);
            double curExpt = 0;
            for(int j = 0; j < n; j++)
                if(!((i << j) & i))
                    curExpt += prob[j] * dp[i | (1 << j)];
            dp[i] = (curExpt + 1) / curProb;
        }
        cout << fixed << setprecision(6) << dp[0] << endl ;
    }
}
