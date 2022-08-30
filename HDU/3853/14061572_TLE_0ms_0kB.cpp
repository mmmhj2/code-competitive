#include <iostream>
#include <iomanip>
#include <vector>
using namespace std;
const int MAXN = 1000;
const int EngCost = 2;
const double EPS = 1e-5;

double loop[MAXN+5][MAXN+5][4];
double DP[MAXN+5][MAXN+5];

int main()
{
    int R, C;
    ios::sync_with_stdio(false);
    cin.tie(0);
    while(cin >> R >> C)
    {
        for(int i = 1; i <= R; i++)
            for(int j = 1; j <= C; j++)
                for(int k = 1; k <= 3; k++)
                    cin >> loop[i][j][k] ;

        double expDow, expSid;
        for(int i = R; i > 0; i--)
        {
            for(int j = C; j > 0; j--)
            {
                if(i == R && j == C)             // Just for looking NEAT
                    continue;
                if(loop[i][j][0] + EPS > 1)
                    continue;
                expSid = loop[i][j][1] * DP[i][j+1];
                expDow = loop[i][j][2] * DP[i+1][j];
                DP[i][j] = (expSid + expDow + EngCost) / (loop[i][j][1] + loop[i][j][2]);
            }
        }
        cout << fixed << setprecision(3) << DP[1][1] << endl ;
    }
}