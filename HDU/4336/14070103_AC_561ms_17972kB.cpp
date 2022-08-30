/*
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
        double probNothing = 1;
        dp[(1<<n)-1] = 0;
        for(int i = 1; i <= n; i++)
            cin >> prob[i], probNothing -= prob[i];
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
        cout << fixed << setprecision(3) << dp[0] << endl ;
    }
}
*/

#include <cstdlib>
#include <cstring>
#include <cstdio>
using namespace std;

int N;

double seq[25], dp[1100000], p[1100000];

void pre()
{
    int LIM = 1 << N;
    for (int i = 0; i < LIM; ++i) {
        p[i] = 0;
        for (int j = 0; j < N; ++j) {
            if ((1 << j) & i) {  // 低位对应编号小的概率
                p[i] += seq[j+1];
            }
        }
    }
}

int main()
{
    int temp;
    double none, tot, myself;
    while (scanf("%d", &N) == 1) {
        dp[(1<<N)-1] = none = 0;
        for (int i = 1; i <= N; ++i) {
            scanf("%lf", &seq[i]);
            none += seq[i];
        }
        none = 1 - none;
        pre();
        for (int i = (1<<N)-2; i >= 0; --i) {
            tot = 0;
            myself = p[i] + none;
            for (int j = 0; j < N; ++j) {
                if (!((1 << j)&i)) {
                    temp = i | (1 << j);
                    tot += seq[j+1] * dp[temp];
                }
            }
            dp[i] = (tot + 1) / (1 - myself);
        }
        printf("%.6lf\n", dp[0]);
    }
    return 0;
}
