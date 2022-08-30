#include <algorithm>
#include <iterator>
#include <iostream>
#include <iomanip>
#include <cstring>
#include <string>
#include <vector>
#include <cmath>

using namespace std;

const int MAXN = 1000 + 5;
const double INF = 1e7;
const double EPS = 1e-5;

struct Village
{
    int x, y, h;
};

int N;
double EucliDist[MAXN][MAXN];
double Dist[MAXN];
bool vist[MAXN];
Village VilPos[MAXN];

inline int subtractAbs(int x, int y)
{
    if(x > y)
        return x - y;
    return y - x;
}

inline double getVal(int i, int j, double delta)
{
    return subtractAbs(VilPos[i].h, VilPos[j].h) - delta * EucliDist[i][j] ;
}

void CalcDist()
{
    memset(EucliDist, 0x00, sizeof EucliDist);
    int x1, x2, y1, y2;
    double tmpDist;

    for(int i = 1; i <= N; i++)
    {
        for(int j = 1; j < i; j++)
        {
            x1 = VilPos[i].x, y1 = VilPos[i].y;
            x2 = VilPos[j].x, y2 = VilPos[j].y;

            tmpDist = (x1-x2)*(x1-x2) + (y1-y2)*(y1-y2);
            EucliDist[i][j] = EucliDist[j][i] = sqrt(tmpDist);
        }
    }
}

double Prim(double delta, int src = 1)
{
    double sum = 0;
    for(int i = 1; i <= N; i++)
        Dist[i] = INF, vist[i] = false;
    Dist[src] = 0;

    for(int i = 1; i <= N; i++)
    {
        int mnMark, mn = INF;
        for(int j = 1; j <= N; j++)
            if(!vist[j])
                if(Dist[j] < mn)
                    mn = Dist[j],
                    mnMark = j;
        sum += Dist[mnMark];
        vist[mnMark] = true;

        for(int j = 1; j <= N; j++)
            if(!vist[j])
                Dist[j] = min(Dist[j], getVal(mnMark, j, delta));
    }

    return sum;
}

double BinarySearch()
{
    double L = 0, R = INF;

    while(L + EPS < R)
    {
        double MID = (L + R) / 2 ;
        if(Prim(MID) < 0)
            R = MID;
        else
            L = MID;
    }
    return L;
}

int main()
{
    while(cin >> N)
    {
        if(!N)
            break;
        for(int i = 1; i <= N; i++)
            cin >> VilPos[i].x >> VilPos[i].y >> VilPos[i].h;
        CalcDist();

        cout << fixed << setprecision(3) << BinarySearch() << endl ;
    }
    return 0;
}
