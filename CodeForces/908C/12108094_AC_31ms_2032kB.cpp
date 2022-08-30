#include <iostream>
#include <algorithm>
#include <iomanip>
#include <cmath>
using namespace std;

const int MAXN = 1000;

int start[MAXN+5];
double finalCoord[MAXN+5];
int radius, n;

int main()
{
    cin >> n >> radius ;
    for(int i = 1; i <= n; i++)
    {
        cin >> start[i];
        double maxcod = 0;
        for(int j = 1; j < i; j++)
        {
            if(abs(start[i]-start[j]) <= 2*radius)
            {
                maxcod = max(maxcod, finalCoord[j]+sqrt(2*radius*2*radius-(start[i]-start[j])*(start[i]-start[j])));
            }
        }
        if(maxcod == 0)
            maxcod = radius;
        finalCoord[i] = maxcod;
    }

    for(int i = 1; i <= n; i++)
    {
        if(i != 1)
            cout << " ";
        cout << fixed << setprecision(10) << finalCoord[i];
    }
}
